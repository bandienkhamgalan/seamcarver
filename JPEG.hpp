#pragma once
#include <jpeglib.h>
#include "RGBAImage.hpp"

namespace IO {
	std::string jpeg_color_space_to_str(J_COLOR_SPACE jpeg_color_space);
	RGBAImage read_jpeg(std::string filename);
	void write_jpeg(RGBAImage& image, std::string filename);
}
