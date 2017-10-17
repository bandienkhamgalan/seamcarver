#include <iostream>
#include <fstream>
#include "CLSeamCarver.hpp"

using namespace std;

void assert_throw(bool condition, string message) {
	if(!condition) {
		throw runtime_error(message);
	}
}

template<typename T>
void setKernelArgsInternal(int index, cl::Kernel& kernel, T const& arg) {
	assert_throw(kernel.setArg(index, arg) == CL_SUCCESS, "Could not pass in argument " + to_string(index) + " to " + kernel.getInfo<CL_KERNEL_FUNCTION_NAME>() + "kernel");
}

template<typename T, typename... Args>
void setKernelArgsInternal(int index, cl::Kernel& kernel, T const& arg, Args... args) {
	setKernelArgsInternal(index, kernel, arg);
	setKernelArgsInternal(index + 1, kernel, args...);
}

template<typename... Args>
void setKernelArgs(cl::Kernel& kernel, Args... args) {
	setKernelArgsInternal(0, kernel, args...);
}

template<typename... Args>
cl::Buffer Buffer(Args... args) {
	cl_int err;
	cl::Buffer buffer(args..., NULL, &err);
	assert_throw(err == CL_SUCCESS, "Failed to construct buffer");
	return buffer;
}

CLSeamCarver::CLSeamCarver(cl::Context context, cl::Device device, cl::Buffer imageBuffer, int width, int height)
	: context(context), device(device), program(constructProgram()), queue(constructCommandQueue()),
	rowPitch(width), height(height), width(width),
	
	prewittFilterBuffer(Buffer(context, CL_MEM_READ_ONLY, sizeof(cl_int) * 3 * 3)),
	imageBuffer(imageBuffer),
	gradientMagnitudesBuffer(Buffer(context, CL_MEM_READ_WRITE, sizeof(cl_float) * 4 * width * height /* float4 array */)),
	parentBuffer(Buffer(context, CL_MEM_READ_WRITE, sizeof(cl_int) * width * height)),
	minimumCostColumnBuffer(Buffer(context, CL_MEM_READ_WRITE, sizeof(cl_int))),
	pathBuffer(Buffer(context, CL_MEM_READ_WRITE, sizeof(cl_int) * height)),
	
	gradientMagnitudesKernel(constructKernel("gradient_magnitudes")),
	seamCarveKernel(constructKernel("seam_carve")),
	extractSeamPathKernel(constructKernel("extract_seam_path")),
	removeSeamKernel(constructKernel("remove_seam"))
{
	cl_int err;
	err = queue.enqueueWriteBuffer(prewittFilterBuffer, CL_FALSE, 0, prewittFilterBuffer.getInfo<CL_MEM_SIZE>(), prewittFilter.data());
	assert_throw(err == CL_SUCCESS, "Failed to write filter queue");

	setKernelArgs(gradientMagnitudesKernel, imageBuffer, rowPitch, height, width, prewittFilterBuffer, cl::Local(sizeof(cl_float) * 18 * 18 * 4), gradientMagnitudesBuffer);
	setKernelArgs(seamCarveKernel, gradientMagnitudesBuffer, rowPitch, height, width, cl::Local(sizeof(cl_float) * width), cl::Local(sizeof(cl_float) * width), parentBuffer, minimumCostColumnBuffer);
	setKernelArgs(extractSeamPathKernel, parentBuffer, rowPitch, height, width, minimumCostColumnBuffer, pathBuffer);
	setKernelArgs(removeSeamKernel, imageBuffer, rowPitch, height, width, pathBuffer);
}

void CLSeamCarver::carve(int columns) {
	for(int i = 0 ; i < columns ; ++i) {
		cl_int err;

		cl::NDRange workgroupSize(16, 16);
		cl::NDRange globalSize(height + (16 - (height % 16)), width + (16 - (width % 16)));
		assert_throw(gradientMagnitudesKernel.setArg(3, width) == CL_SUCCESS, "failed to update imageWidth for gradient_magnitudes kernel");
		err = queue.enqueueNDRangeKernel(gradientMagnitudesKernel, cl::NullRange, globalSize, workgroupSize);
		assert_throw(err == CL_SUCCESS, "failed to queue execution of gradient_magnitudes kernel: " + to_string(err));
		
		assert_throw(seamCarveKernel.setArg(3, width) == CL_SUCCESS, "failed to update imageWidth for seam_carve kernel");
		err = queue.enqueueNDRangeKernel(seamCarveKernel, cl::NullRange, cl::NDRange(256), cl::NDRange(256));
		assert_throw(err == CL_SUCCESS, "failed to queue execution of seam_carve kernel: " + to_string(err));
		
		assert_throw(extractSeamPathKernel.setArg(3, width) == CL_SUCCESS, "failed to update imageWidth for extract_seam_path kernel");
		err = queue.enqueueNDRangeKernel(extractSeamPathKernel, cl::NullRange, cl::NDRange(1), cl::NDRange(1));
		assert_throw(err == CL_SUCCESS, "failed to queue execution of extract_seam_path kernel: " + to_string(err));
		
		cl::Event event;
		assert_throw(removeSeamKernel.setArg(3, width) == CL_SUCCESS, "failed to update imageWidth for remove_seam kernel");
		err = queue.enqueueNDRangeKernel(removeSeamKernel, cl::NullRange, cl::NDRange(256), cl::NDRange(256), NULL, &event);
		assert_throw(err == CL_SUCCESS, "failed to queue execution of removeSeamKernel kernel: " + to_string(err));

		event.wait();

		--width;
	}
}

vector<cl_uchar> CLSeamCarver::GetImageData() const {
	auto buffer = new cl_uchar[rowPitch * height * 4];
	cl_int err = queue.enqueueReadBuffer(imageBuffer, CL_TRUE, 0, imageBuffer.getInfo<CL_MEM_SIZE>(), buffer);
	assert_throw(err == CL_SUCCESS, "failed to read imageBuffer");
	auto croppedBuffer = new cl_uchar[width * height * 4];
	for(int row = 0 ; row < height ; ++row) {
		memcpy(croppedBuffer + row * width * 4, buffer + row * rowPitch * 4, width * 4);
	}
	delete[] buffer;
	auto data = vector<cl_uchar>(croppedBuffer, croppedBuffer + width * height * 4);
	delete[] croppedBuffer;
	return data;
}

cl::Program CLSeamCarver::constructProgram() const {
	ifstream ifs("seam_carve.cl");
	filebuf* pbuf = ifs.rdbuf();
	size_t size = pbuf->pubseekoff(0,ifs.end,ifs.in);
	pbuf->pubseekpos(0,ifs.in);
	char* buffer = new char[size];
	pbuf->sgetn(buffer, size);
	ifs.close();
	string source(buffer);
	delete[] buffer;

	cl_int err;
	cl::Program::Program program(context, source, true, &err);
	if(err == CL_BUILD_PROGRAM_FAILURE) {
		string log;
		program.getBuildInfo(device, CL_PROGRAM_BUILD_LOG, &log);
		cerr << "Build program failed: " << endl;
		cerr << log;
		exit(-1);
	}
	assert_throw(err == CL_SUCCESS, "Failed to create cl::Program");

	return program;
}

cl::CommandQueue CLSeamCarver::constructCommandQueue() const {
	cl_int err;
	cl::CommandQueue queue(context, device, 0, &err);
	assert_throw(err == CL_SUCCESS, "Failed to create command queue");
	return queue;
}

cl::Kernel CLSeamCarver::constructKernel(string name) const {
	cl_int err;
	cl::Kernel kernel(program, name.c_str(), &err);
	assert_throw(err == CL_SUCCESS, "Failed to construct " + name + " kernel");
	return kernel;
}