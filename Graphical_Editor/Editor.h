#pragma once
#include "Image.h"
#include <iostream>
#include <string>
class Editor {

public:
    Editor();
    ~Editor();
    void promptCommands();
    bool isCommandValid(std::string& command);
    void runCommands();

    void createNewImage(const int rows, const int columns);
    void clearCurrentImage();
    void colorPixel(const int row, const int column, const char color);
    void drawVerticalLine(const int column, const int startRow, const int endRow, const char color);
    void drawHorizontalLine(const int row, const int startColumn, const int endColumn, const char color);
    void drawFilledRectangle(const int x1, const int y1, const int x2, const int y2, const char color);
    void fillColumn(int x, int y, const char oldColor, const char color);
    bool diagonalyAdjacentPixelHasOldColor(int x, int y, char oldColor);
    void fillRegion(const int x, const int y, const char newColor);
    struct ChildPos {
        int x;
        int y;
    };
    std::vector<int> pixelMeetsCriteria(const int childX, const int childY, const int parentX, const int parentY, const char oldColor);

    void saveImageAsAndDisplay(const std::string name);

    void setPixelColor(const int row, const int column, const char color);

private:
    std::vector<Image> images;
    Image currentImage;
    std::vector<std::string> commands;
    int pixelsAroundOffset[8][2];
    char oldColor;
    bool isFlooding;

};

