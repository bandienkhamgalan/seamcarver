#pragma once
#include <string>
#include <array>
#include "cl.hpp"

class CLSeamCarver {
public:
	CLSeamCarver(cl::Context context, cl::Device device, cl::Buffer imageBuffer, int width, int height);
	std::vector<cl_uchar> GetImageData() const;
	void carve(int columns);

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
