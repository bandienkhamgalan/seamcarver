#define filter(i, j) filter[j + i * filterWidth]
#define image(row, column) image[clamp(column, 0, columns - 1) + rowPitch * clamp(row, 0, rows - 1)]
#define output(row, column) output[column + rowPitch * (row)]
#define region(row, column) region[column + 1 + (get_local_size(1) + 2) * (row + 1)]

__kernel void gradient_magnitudes(
        __global uchar4 const *image, 
        __const int rowPitch,
        __const int rows, __const int columns,
        __constant int const *filter,
        __local float4 *region, __global float4 *output)
{
    int row = get_global_id(0);
    int column = get_global_id(1);
    int local_row = get_local_id(0);
    int local_column = get_local_id(1);
    
    // Copy region to local memory
    if(row <= rows && column <= columns) {
        region(local_row, local_column) = convert_float4(image(row, column));

        // Let work units on boundary of work group copy extra boundary pixels
        if(local_row == 0) {
            region(local_row - 1, local_column) = convert_float4(image(row - 1, column));
            if(local_column == 0) {
                region(local_row - 1, local_column - 1) = convert_float4(image(row - 1, column - 1));
            } else if(local_column == (int)get_local_size(1) - 1) {
                region(local_row - 1, local_column + 1) = convert_float4(image(row - 1, column + 1));
            }
        } else if(local_row == (int)get_local_size(0) - 1) {
            region(local_row + 1, local_column) = convert_float4(image(row + 1, column));
            if(local_column == 0) {
                region(local_row + 1, local_column - 1) = convert_float4(image(row + 1, column - 1));
            } else if(local_column == (int)get_local_size(1) - 1) {
                region(local_row + 1, local_column + 1) = convert_float4(image(row + 1, column + 1));
            }
        }
        
        if(local_column == 0) {
            region(local_row, local_column - 1) = convert_float4(image(row, column - 1));
        } else if(local_column == (int)get_local_size(1) - 1) {
            region(local_row, local_column + 1) = convert_float4(image(row, column + 1));
        }  
    }
    
    // Synchronize work items and ensure visibility of local memory
    barrier(CLK_LOCAL_MEM_FENCE);
    
    // Convolve filter in both directions against region stored in local memory
    if(row < rows && column < columns) {
        float4 grad_x = 0.0;
        float4 grad_y = 0.0;
        int filterWidth = 3;
        int offset = filterWidth >> 1;
        for(int i = 0 ; i < filterWidth ; ++i) {
            for(int j = 0 ; j < filterWidth ; ++j) {
                grad_x += filter(i, j) * region(local_row + i - offset, local_column + j - offset);
                grad_y += filter(j, i) * region(local_row + i - offset, local_column + j - offset);
            }
        }

        output(row, column) = sqrt(grad_x * grad_x + grad_y * grad_y);
    }
}

#define imageGradient(row, column) imageGradient[column + rowPitch * (row)]
#define parent(row, column) parent[column + rowPitch * (row)]

__kernel void seam_carve(
        __global const float4 *imageGradient, __const int rowPitch,
        __const int rows, __const int columns,
        __local float *previousCost, __local float *cost,
        __global int *parent, global int *minimumCostColumn)
{
    // Initialize previousCost to zero
    int lid = get_local_id(0);
    int columns_per_thread = ceil((float)columns / get_local_size(0));
    int offset = lid * columns_per_thread;
    for(int i = 0 ; i < columns_per_thread ; ++i) {
        int column = offset + i;
        if(column < columns) {
            previousCost[column] = 0.0;
        }
    }
    barrier(CLK_LOCAL_MEM_FENCE);
    
    // Calculate minimum cost seams for each successive row
    for(int row = 0 ; row < rows ; ++row) {
        for(int i = 0 ; i < columns_per_thread ; ++i) {
            int column = offset + i;
            if(column < columns) {
                int minimumParent = -1;
                float minimumParentCost = INFINITY;
                if(column - 1 >= 0 && previousCost[column - 1] < minimumParentCost) {
                    minimumParentCost = previousCost[column - 1];
                    minimumParent = column - 1;
                }
                if(previousCost[column] < minimumParentCost) {
                    minimumParentCost = previousCost[column];
                    minimumParent = column;
                }
                if(column + 1 < columns && previousCost[column + 1] < minimumParentCost) {
                    minimumParentCost = previousCost[column + 1];
                    minimumParent = column + 1;
                }
                
                cost[column] = minimumParentCost + dot(1.0, imageGradient(row, column));
                parent(row, column) = minimumParent;
            }
        }
        __local float* temp = cost;
        cost = previousCost;
        previousCost = temp;
        barrier(CLK_LOCAL_MEM_FENCE);
    }
    
    /* Perform a parallel reduction to find the minimum cost pixel of the last row */
    
    // Prepare for reduction
    __local float* lastRowCost = previousCost;
    __local int* minimumIndices = (__local int*)cost;
    float minimum = INFINITY;
    int minimumIndex = -1;
    for(int i = 0 ; i < columns_per_thread ; ++i) {
        int column = offset + i;
        if(column < columns && lastRowCost[column] < minimum) {
            minimum = lastRowCost[column];
            minimumIndex = column;
        }
    }
    barrier(CLK_LOCAL_MEM_FENCE);
    lastRowCost[lid] = minimum;
    minimumIndices[lid] = minimumIndex;
    barrier(CLK_LOCAL_MEM_FENCE);

    // Perform a commutative reduction
    for(size_t stride = 1 ; stride < get_local_size(0) ; stride <<= 1) {
        int mask = (stride << 1) - 1;
        if((lid & mask) == 0) {
            if(lastRowCost[lid] > lastRowCost[lid + stride]) {
                lastRowCost[lid] = lastRowCost[lid + stride];
                minimumIndices[lid] = minimumIndices[lid + stride];
            }
        }
        barrier(CLK_LOCAL_MEM_FENCE);
    }

    // Let first thread write result of reduction to global memory 
    if(lid == 0) {
        *minimumCostColumn = minimumIndices[0];
    }
}

__kernel void extract_seam_path(__global int const *parent, __const int rowPitch,
                                __const int rows, __const int columns,
                                __global int const *lastRowMinimumCostColumn, __global int *path)
{
    int currentColumn = *lastRowMinimumCostColumn;
    for(int row = rows - 1 ; row >= 0 ; --row) {
        path[row] = currentColumn;
        currentColumn = parent(row, currentColumn);
    }
}

__kernel void remove_seam(__global uchar4 *image, __const int rowPitch,
                          __const int rows, __const int columns,
                          __global int const *path)
{
    int lid = get_local_id(0);
    int columns_per_thread = ceil((float)columns / get_local_size(0));
    int offset = lid * columns_per_thread;
    for(int row = 0 ; row < rows ; ++row) {
        uchar4 onePixelBeyondLast = image(row, offset + columns_per_thread);
        barrier(CLK_LOCAL_MEM_FENCE);

        for(int i = 0 ; i < columns_per_thread - 1 ; ++i) {
            int column = offset + i;
            if(column >= path[row]) {
                image(row, column) = image(row, column + 1);
            }
        }

        int lastIndex = offset + columns_per_thread - 1;
        if(lastIndex >= path[row]) {
            image(row, lastIndex) = onePixelBeyondLast;
        }

        barrier(CLK_LOCAL_MEM_FENCE);
    }
}
