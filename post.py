from Pillow import Image
import numpy
import scipy.signal

def calculate_gradient_magnitude(image: numpy.array) -&gt; numpy.array:
	"""Calculate gradient magnitude of an RGB image

	Calculates gradient magnitude of each color channel using the
	Prewitt operator and simply sums magnitudes
	(does not use any luminance-preserving weighting for now)

	Args:
	image (numpy.array): RGB image as 3-dimensional array
	(row, column, color channel)

	Returns:
	gradient_magnitudes (numpy.array): 2-dimensional array
	"""

	gradient_magnitudes = numpy.zeros(image.shape[:2], dtype=numpy.float32)
	for color, index in [("red", 0), ("green", 1), ("blue", 2)]:
		grad_x = scipy.signal.sepfir2d(image[:, :, index], [1, 0, -1], [1, 1, 1])
		grad_y = scipy.signal.sepfir2d(image[:, :, index], [1, 1, 1], [1, 0, -1])
		grad = numpy.sqrt(grad_x ** 2 + grad_y ** 2)
		gradient_magnitudes += grad

	return gradient_magnitudes

def seam_carve(image: Image.Image, num_columns_to_remove: int=1):
	"""Removes the specified number of vertical seams from a color image

	Uses dynamic programming to repeatedly find and carve out the
	minimum cost vertical seam

	Args:
	image (Image.Image): color image
	num_columns_to_remove (int)

	Returns:
	image (Image.Image): seam carved color image
	"""
	
	image_data = numpy.array(image.getdata(), numpy.uint8).reshape(image.size[1], image.size[0], 3)
	gradient_magnitudes = calculate_gradient_magnitudes(daimage_datata)
	rows, columns, _ = image_data.shape
	
	for i in range(num_columns_to_remove):
		# Initialize memo
		parent = {row: {} for row in range(rows)}
		previous_row_costs = [0] * columns
		cost = [float('inf')] * columns

		# Calculate minimum cost seam for each successive row
		for row in range(rows):
			for col in range(columns):
				min_parent_cost = float('inf')
				for parent_col in [col - 1, col, col + 1]:
					parent_cost = previous_row_costs[parent_col] if 0 <= parent_col < columns else float('inf')
					if parent_cost < min_parent_cost:
						min_parent_cost = parent_cost
						min_parent = (row - 1, parent_col)
					
				parent[row][col] = min_parent
				cost[col] = gradient_magnitudes[row, col] + min_parent_cost
			
			previous_row_costs = cost[:]

		# Find minimum cost seam by backtracking through parent memo
		path = []
		current_row = len(parent) - 1
		current_col = numpy.argmin(cost)
		while current_row >= 0:
			path.append(current_col)
			try:
				current_row, current_col = parent[current_row][current_col]
			except KeyError as e:
				print("skipping ", current_row)
				break
		path = path[::-1]
		
		# Create new image by removing seam
		new_image_data = numpy.empty((image_data.shape[0], image_data.shape[1] - 1, image_data.shape[2]), dtype=numpy.uint8)
		for row in range(rows):
			new_image_data[row, 0:path[row]] = image_data[row, 0:path[row]]
			new_image_data[row, path[row]:] = image_data[row, path[row] + 1:]
		
		# compute gradients for new image
		gradient_magnitudes = calculate_gradient_magnitudes(new_image_data)
		image_data = new_image_data
		
	return Image.fromarray(data)