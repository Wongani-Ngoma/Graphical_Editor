#pragma once
#include <vector>
#include <string>

class Image {

public:
    Image();
    Image(const int rows, const int columns);
    ~Image();
    void setPixelColor(const int x, const int y, const char color);
    char getPixelRef(const int x, const int y);
    int getSize()const;
    std::vector<std::vector<char>>& getcurrentImage();
    std::vector<char>& operator[](int x);
    char& operator()(int row, int col);

private:
    std::string name;
    std::vector<std::vector<char>> image;

};