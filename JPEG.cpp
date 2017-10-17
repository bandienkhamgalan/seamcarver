#include <iostream>
#include <stdio.h>
#include <errno.h>
#include "JPEG.hpp"

namespace IO {
	using namespace std;

	string jpeg_color_space_to_str(J_COLOR_SPACE jpeg_color_space) {
		switch(jpeg_color_space) {
			case JCS_GRAYSCALE:
				return "Grayscale";
			case JCS_RGB:
				return "RGB";
			case JCS_CMYK:
				return "CMYK";
			case JCS_BG_RGB:
				return "Big Gamut RGB";
			case JCS_YCbCr:
				return "Y/Cb/Cr";
			default:
				return "Unknown (" + to_string(jpeg_color_space) + ")";
		}
	}

	void write_jpeg(RGBAImage& image, string filename) {
		struct jpeg_compress_struct imageInfo;
		struct jpeg_error_mgr errorManager;
		imageInfo.err = jpeg_std_error(&errorManager);
		jpeg_create_compress(&imageInfo);

		FILE* imageFile;
		if((imageFile = fopen(filename.c_str(), "wb")) == NULL) {
			cerr << "fopen() failed with error: " << strerror(errno) << endl;
			exit(-1);
		}
		jpeg_stdio_dest(&imageInfo, imageFile);

		imageInfo.image_width = image.width;
		imageInfo.image_height = image.height;
		imageInfo.input_components = 3;
		imageInfo.in_color_space = JCS_RGB;
		jpeg_set_defaults(&imageInfo);
		jpeg_start_compress(&imageInfo, TRUE);

		int length = imageInfo.image_width * imageInfo.image_height * imageInfo.input_components;
		JSAMPLE* buffer = new JSAMPLE[length];
		auto* data = image.GetData().data(); 
		for(int i = 0 ; i < imageInfo.image_width * imageInfo.image_height ; ++i) {
			memcpy(buffer + i * 3, data + i, 3);
		}

		for(int row = 0 ; row < image.height ; ++row) {
			JSAMPLE* temp = buffer + row * imageInfo.input_components * imageInfo.image_width;
			jpeg_write_scanlines(&imageInfo, &temp, 1);
		}
		
		delete[] buffer;

		jpeg_finish_compress(&imageInfo);
		jpeg_destroy_compress(&imageInfo);
		fclose(imageFile);
	}

	RGBAImage read_jpeg(string filename) {
		struct jpeg_decompress_struct imageInfo;
		struct jpeg_error_mgr errorManager;
		imageInfo.err = jpeg_std_error(&errorManager);
		jpeg_create_decompress(&imageInfo);

		FILE* imageFile;
		if((imageFile = fopen(filename.c_str(), "rb")) == NULL) {
			cerr << "fopen() failed with error: " << strerror(errno) << endl;
			exit(-1);
		}
		jpeg_stdio_src(&imageInfo, imageFile);
		jpeg_read_header(&imageInfo, TRUE);
		imageInfo.out_color_space = JCS_RGB;
		jpeg_start_decompress(&imageInfo);

		int length = imageInfo.output_width * imageInfo.output_height * imageInfo.output_components;
		JSAMPLE* buffer = new JSAMPLE[length];
		while (imageInfo.output_scanline < imageInfo.output_height) {
			int row = imageInfo.output_scanline;
			JSAMPLE* temp = buffer + row * imageInfo.output_components * imageInfo.output_width;
			jpeg_read_scanlines(&imageInfo, &temp, 1);
		}
		jpeg_finish_decompress(&imageInfo);
		jpeg_destroy_decompress(&imageInfo);
		fclose(imageFile);

		int convertedLength = imageInfo.output_width * imageInfo.output_height;
		auto converted = new RGBAImage::RGBAPixel[convertedLength];
		for(int i = 0 ; i < convertedLength ; ++i) {
			memcpy(converted + i, buffer + i * 3, 3);
			converted[i].alpha = 255;
		}
		delete[] buffer;
		vector<RGBAImage::RGBAPixel> imageData((RGBAImage::RGBAPixel*)converted, (RGBAImage::RGBAPixel*)(converted + convertedLength));
		delete[] converted;

		return RGBAImage(move(imageData), imageInfo.output_width, imageInfo.output_height);
	}
}