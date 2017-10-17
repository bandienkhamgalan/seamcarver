#include <QSurfaceFormat>
#include <QApplication>
#include "MainWindow.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <array>
#include <stdexcept>
#include "cl.hpp"
#include "RGBAImage.hpp"
#include "JPEG.hpp"

using namespace std;

int main(int argc, char **argv) {
	QSurfaceFormat glFormat;
	glFormat.setVersion(3, 2);
	glFormat.setProfile(QSurfaceFormat::CoreProfile);
	QSurfaceFormat::setDefaultFormat(glFormat);

	QApplication a(argc, argv);
    MainWindow w;
    w.show();

	return a.exec();

	/*
	
	if(argc != 3) {
		cout << "Usage: seamcarve <filename.jpg> <number of vertical seams to remove>\n";
		exit(-1);
	}

	RGBAImage image = IO::read_jpeg(argv[1]);
	cout << image.width << "x" << image.height << endl;

	int seams = 0;
	try {
		seams = stoi(argv[2]);
	} catch(invalid_argument const& exc) {
		cout << "Usage: seamcarve <filename.jpg> <number of vertical seams to remove>\nNote that <number of vertical seams to remove> must be a positive integer\n";
		exit(-1);
	}
	
	// Select fastest device (by clock frequency) that supports 16x16 work group
	vector<cl::Device> supportedDevices;

	vector<cl::Platform> platforms;
	if(cl::Platform::get(&platforms) != CL_SUCCESS) {
		cerr << "Failed to get OpenCL platforms. ";
		exit(-1);
	}

	for(auto& platform : platforms) {
		vector<cl::Device> devices;

		if(platform.getDevices(CL_DEVICE_TYPE_ALL, &devices) != CL_SUCCESS) {
			string name;
			platform.getInfo(CL_PLATFORM_NAME, &name);
			cerr << "Failed to get devices for " << name << " platform";
			exit(-1);
		}

		for(auto& device : devices) {
			vector<size_t> maxWorkItemSizes = device.getInfo<CL_DEVICE_MAX_WORK_ITEM_SIZES>();
			cout << device.getInfo<CL_DEVICE_EXTENSIONS>() << endl;
			if(maxWorkItemSizes.size() > 2 && maxWorkItemSizes[0] >= 16 && maxWorkItemSizes[1] >= 16) {
				supportedDevices.push_back(device);
			}
		}
	}

	auto iter = max_element(supportedDevices.cbegin(), supportedDevices.cend(), [](cl::Device const& a, cl::Device const& b)
		{
			cl_uint aFrequency, bFrequency;
			a.getInfo(CL_DEVICE_MAX_CLOCK_FREQUENCY, &aFrequency);
			b.getInfo(CL_DEVICE_MAX_CLOCK_FREQUENCY, &bFrequency);
			return aFrequency < bFrequency;
		});
	cl::Device device = *iter;

	vector<cl::Device> devices(iter, iter + 1);
	cout << "Selected best device from " << supportedDevices.size() << " supported devices:" << endl;
	cout << devices[0].getInfo<CL_DEVICE_NAME>() << endl;

	cl_int err;
	cl::Context context(devices, NULL, NULL, NULL, &err);
	assert_throw(err == CL_SUCCESS, "Failed to create context");

	
	for(int i = 0 ; i < seams ; ++i) {
		cl::NDRange workgroupSize(16, 16);
		cl::NDRange globalSize(image.height + (16 - (image.height % 16)) , image.width + (16 - (image.width % 16)));
		assert_throw(gradientMagnitudesKernel.setArg(3, image.width - i) == CL_SUCCESS, "failed to update imageWidth for gradient_magnitudes kernel");
		err = queue.enqueueNDRangeKernel(gradientMagnitudesKernel, cl::NullRange, globalSize, workgroupSize);
		assert_throw(err == CL_SUCCESS, "failed to queue execution of gradient_magnitudes kernel: " + to_string(err));
		
		assert_throw(seamCarveKernel.setArg(3, image.width - i) == CL_SUCCESS, "failed to update imageWidth for seam_carve kernel");
		err = queue.enqueueNDRangeKernel(seamCarveKernel, cl::NullRange, cl::NDRange(256), cl::NDRange(256));
		assert_throw(err == CL_SUCCESS, "failed to queue execution of seam_carve kernel: " + to_string(err));
		
		assert_throw(extractSeamPathKernel.setArg(3, image.width - i) == CL_SUCCESS, "failed to update imageWidth for extract_seam_path kernel");
		err = queue.enqueueNDRangeKernel(extractSeamPathKernel, cl::NullRange, cl::NDRange(1), cl::NDRange(1));
		assert_throw(err == CL_SUCCESS, "failed to queue execution of extract_seam_path kernel: " + to_string(err));
		
		auto gradientMagnitudes = new cl_float[image.width * image.height * 4];
		err = queue.enqueueReadBuffer(gradientMagnitudesBuffer, CL_TRUE, 0, sizeof(cl_float) * image.width * image.height * 4, gradientMagnitudes);
		assert_throw(err == CL_SUCCESS, "failed to read gradientMagnitudes buffer");
		
		cl::Event event;
		assert_throw(removeSeamKernel.setArg(3, image.width - i) == CL_SUCCESS, "failed to update imageWidth for remove_seam kernel");
		err = queue.enqueueNDRangeKernel(removeSeamKernel, cl::NullRange, cl::NDRange(256), cl::NDRange(256), NULL, &event);
		assert_throw(err == CL_SUCCESS, "failed to queue execution of removeSeamKernel kernel: " + to_string(err));
		event.wait();

		cout << "Removed " << i + 1 << " seams" << endl;
	}
		
	auto imageData = new cl_uchar[image.width * image.height * 4];
	err = queue.enqueueReadBuffer(imageBuffer, CL_TRUE, 0, sizeof(RGBAImage::RGBAPixel) * image.width * image.height, imageData);
	assert_throw(err == CL_SUCCESS, "failed to read outputted image buffer");
	auto imageDataCropped = new RGBAImage::RGBAPixel[(image.width - seams) * image.height];
	for(int row = 0 ; row < image.height ; ++row) {
		memcpy(imageDataCropped + row * (image.width - seams), imageData + (row * image.width * 4), (image.width - seams) * 4);
	}
	delete[] imageData;
	RGBAImage carvedImage(vector<RGBAImage::RGBAPixel>(imageDataCropped, imageDataCropped + (image.width - seams) * image.height), image.width - seams, image.height);
	delete[] imageDataCropped;
	IO::write_jpeg(carvedImage, "carved.jpg");

	return 0; */
}
