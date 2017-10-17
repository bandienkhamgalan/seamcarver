#include "RGBAImage.hpp"

using namespace std;

uint8_t RGBAImage::RGBAPixel::GetColor(Color color) const {
	switch(color) {
		case Red:
			return red;
		case Green:
			return green;
		case Blue:
			return blue;
		case Alpha:
			return alpha;
	}
	throw invalid_argument("color out of range");
}

RGBAImage::RGBAPixel::operator string() const {
	return "(" + to_string(static_cast<int>(red)) + ", " +
				 to_string(static_cast<int>(green)) + ", " + 
				 to_string(static_cast<int>(blue)) + ", " +
				 to_string(static_cast<int>(alpha)) + ")";
}

/*
RGBAImage::RGBAImage(vector<RGBAImage::RGBAPixel> const& data, int width, int height); : width(width), height(height), data(data) {
	cout << "in value constructor" << endl;
}*/

RGBAImage::RGBAImage(vector<RGBAImage::RGBAPixel>&& data, int width, int height) : width(width), height(height), data(move(data)) {
	//cout << "in r-value reference constructor" << endl;
}

vector<RGBAImage::RGBAPixel>& RGBAImage::GetData() {
	return data;
}

uint8_t RGBAImage::operator()(int row, int col, Color color) const {
	return operator()(row, col).GetColor(color);
}

RGBAImage::RGBAPixel const& RGBAImage::operator()(int row, int col) const {
	if(row < 0 || row >= height) {
		throw invalid_argument("row out of range");
	}
	if(col < 0 || col >= width) {
		throw invalid_argument("col out of range");
	}

	return data[row * width + col];
}
