#pragma once
#include <string>
#include <array>
#include <tuple>
#include "cl.hpp"

class CLSeamCarver {
public:
	CLSeamCarver(cl::Context context, cl::Device device, cl::Buffer imageBuffer, int width, int height);
	/* Saves data in image buffer to specified buffer in row-major format.
	   Caller is responsible for making sure that buffer is large enough to contain image. 
	   Required size in bytes in width * height * 4 (call GetImageSize() to get width and height)  */
	void GetImageData(cl_uchar* buffer) const;
	void carve(int columns);
	/* Returns current dimensions of image in buffer as (width, height) tuple */
	std::tuple<int, int> GetImageSize() const;

private:
	cl::Program constructProgram() const;
	cl::CommandQueue constructCommandQueue() const;
	cl::Kernel constructKernel(std::string name) const;

	cl::Context context;
	cl::Device device;
	cl::Program program;
	cl::CommandQueue queue;
	
	int rowPitch;
	int height;
	int width;

	std::array<cl_int, 9> prewittFilter = {{ -1, 0, 1,
											 -1, 0, 1,
											 -1, 0, 1 }};

	cl::Buffer prewittFilterBuffer;
	cl::Buffer imageBuffer;
	cl::Buffer gradientMagnitudesBuffer;
	cl::Buffer parentBuffer;
	cl::Buffer minimumCostColumnBuffer;
	cl::Buffer pathBuffer;

	cl::Kernel gradientMagnitudesKernel;
	cl::Kernel seamCarveKernel;
	cl::Kernel extractSeamPathKernel;
	cl::Kernel removeSeamKernel;
};
