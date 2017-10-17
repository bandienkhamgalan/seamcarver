#pragma once
#include <vector>
#include <stdexcept>
#include <string>

class RGBAImage {
public:
	enum Color {
		Red,
		Green,
		Blue,
		Alpha
	};
	
	struct RGBAPixel {
		RGBAPixel() : red(0), green(0), blue(0), alpha(0) {}
		RGBAPixel(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) : red(red), green(green), blue(blue), alpha(alpha) {}

		uint8_t red;
		uint8_t green;
		uint8_t blue;
		uint8_t alpha;

		uint8_t GetColor(Color color) const;
		operator std::string() const;
	};
	
	//RGBAImage(std::vector<RGBAPixel> const& data, int width, int height);
	RGBAImage(std::vector<RGBAPixel>&& data, int width, int height);

	std::vector<RGBAPixel>& GetData();
	uint8_t operator()(int row, int col, Color color) const;
	RGBAPixel const& operator()(int row, int col) const;

	int const width;
	int const height;

private:
	std::vector<RGBAPixel> data;
};
