#include "Image.h"
#include <iostream>

Image::Image()
{
}

Image::Image(const int columns, const int rows) {
    image = std::vector<std::vector<char>>(rows, std::vector<char>(columns));
    for (auto& line : image) {
        for (char& c : line) {
            c = ' ';
        }
    }
}

Image::~Image()
{
}

std::vector<char>& Image::operator[](int col) {
    return image[col];
}

char& Image::operator()(int col, int row) {
    return image[row - 1][col - 1];
}
char Image::getPixelRef(const int col, const int row)
{
    return image[row - 1][col - 1];
}

void Image::setPixelColor(const int x, const int y, const char color) {
    image[y - 1][x - 1] = color;
}

int Image::getSize() const {
    return image.size();
}
std::vector<std::vector<char>>& Image::getcurrentImage() {
    return image;
}
