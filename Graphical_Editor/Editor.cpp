#include "Editor.h"
#include <set>
#include <cmath>

Editor::Editor() {
    pixelsAroundOffset[0][0] = 1; pixelsAroundOffset[0][1] = 0; //Right
    pixelsAroundOffset[1][0] = 1; pixelsAroundOffset[1][1] = -1; //Top right
    pixelsAroundOffset[2][0] = 1; pixelsAroundOffset[2][1] = 1; //Bottom right

    pixelsAroundOffset[3][0] = 0; pixelsAroundOffset[3][1] = -1; //Top
    pixelsAroundOffset[4][0] = 0; pixelsAroundOffset[4][1] = 1; //Bottom

    pixelsAroundOffset[5][0] = -1; pixelsAroundOffset[5][1] = 0; //left
    pixelsAroundOffset[6][0] = -1; pixelsAroundOffset[6][1] = -1; //top left
    pixelsAroundOffset[7][0] = -1; pixelsAroundOffset[7][1] = 1; //bottom left

    isFlooding = false;
}

Editor::~Editor() {

}

//Promt and Store valid commands, remove the 'X X' command afterwards since this is also stored althouth not needed later in the program
//The only purpose of the 'X X' command is to tell the program to stop the prompting session
void Editor::promptCommands() {
    std::string currentComamnd;

    do {
        std::getline(std::cin, currentComamnd);
        commands.push_back(currentComamnd);
    } while (isCommandValid(currentComamnd) && (currentComamnd[0] != 'x' || currentComamnd[0] != 'X'));
    commands.pop_back(); //Remove the 'X' command
}

//Checks if the command is acceptible by the prorgame
bool Editor::isCommandValid(std::string& command) {
    if (
        command[0] == 'I' ||
        command[0] == 'C' ||
        command[0] == 'L' ||
        command[0] == 'V' ||
        command[0] == 'H' ||
        command[0] == 'K' ||
        command[0] == 'C' ||
        command[0] == 'F' ||
        command[0] == 'S') {
        return true;
    }
    return false;
}

//This reads all commands in the commands vector and performs some type conversion based on the command (eg If the command is 
//draw a rectangle, it will convert and record some parts of the command string into numbers and convert and record another part as the color), then it calls the draw 
//function with these parameters)
void Editor::runCommands() {
    int x, y, x1, x2, y1, y2, rows, columns, column, row, row1, column1, row2, column2;//Not all of these commands are used in any one function call
    char color;
    for (std::string& command : commands) {
        switch (command[0]) {
        case 'I':
            x = atoi(&std::string(command, 2, 1)[0]);
            y = atoi(&std::string(command, 4, 1)[0]);
            createNewImage(x, y);
            break;
        case 'C':
            clearCurrentImage();
            break;
        case 'L':
            x = atoi(&std::string(command, 2, 1)[0]);
            y = atoi(&std::string(command, 4, 1)[0]);
            color = command[command.length() - 1];
            colorPixel(x, y, color);
            break;
        case 'V':
            column = atoi(&std::string(command, 2, 1)[0]);
            row1 = atoi(&std::string(command, 4, 1)[0]);
            row2 = atoi(&std::string(command, 6, 1)[0]);
            color = command[command.length() - 1];
            drawVerticalLine(column, row1, row2, color);
            break;
        case 'H':
            row = atoi(&std::string(command, 2, 1)[0]);
            column1 = atoi(&std::string(command, 4, 1)[0]);
            column2 = atoi(&std::string(command, 6, 1)[0]);
            color = command[command.length() - 1];
            drawHorizontalLine(row, column1, column2, color);
            break;
        case 'K':
            x1 = atoi(&std::string(command, 2, 1)[0]);
            y1 = atoi(&std::string(command, 4, 1)[0]);
            x2 = atoi(&std::string(command, 6, 1)[0]);
            y2 = atoi(&std::string(command, 8, 1)[0]);
            color = command[command.length() - 1];
            drawFilledRectangle(x1, y1, x2, y2, color);
            break;
        case 'F':
            x = atoi(&std::string(command, 2, 1)[0]);
            y = atoi(&std::string(command, 4, 1)[0]);
            color = command[command.length() - 1];
            oldColor = currentImage.getPixelRef(x, y);
            fillRegion(x, y, color);
            break;
        case 'S':
            saveImageAsAndDisplay(std::string(command, 2, command.length() - 2));
            break;
        default:
            break;
        }
    }
}

void Editor::createNewImage(const int x, const int y) {
    images.emplace_back(Image(x, y));
    currentImage = images[images.size() - 1];
}

void Editor::clearCurrentImage() {
    auto& imageData = currentImage.getcurrentImage();
    for (auto& line : imageData) {
        for (char& c : line) {
            c = ' ';
        }
    }
}

//Color a single pixel
void Editor::colorPixel(const int x, const int y, const char color) {
    currentImage(x, y) = color;
}

void Editor::drawVerticalLine(const int column, const int startRow, const int endRow, const char color) {
    auto& imageData = currentImage.getcurrentImage();
    for (int i = startRow; i <= endRow; i++) {
        currentImage.setPixelColor(column, i, color);
    }
}

void Editor::drawHorizontalLine(const int row, const int startColumn, const int endColumn, const char color) {
    auto& imageData = currentImage.getcurrentImage();
    for (int i = startColumn; i <= endColumn; i++) {
        currentImage.setPixelColor(i, row, color);
    }
}

void Editor::drawFilledRectangle(const int x1, const int y1, const int x2, const int y2, const char color) {
    for (int i = x1; i <= x2; i++) {
        for (int e = y1; e <= y2; e++) {
            currentImage(i, e) = color;
        }
    }
}

//This is used by the fillRegion method, it fills the column that (x, y) is in
void Editor::fillColumn(int x, int y, const char oldColor, const char newColor) {
    int startPosX = x;
    int startPosY = y;
    //Fill (x, y) itself
    currentImage(x, y) = newColor;
    //Start filling up from (x, y)
    while (startPosY - 1 > 0) {
        if (currentImage.getPixelRef(x, startPosY - 1) == oldColor) {
            currentImage.setPixelColor(x, startPosY - 1, newColor);
            startPosY--;
        }
        else {
            if (diagonalyAdjacentPixelHasOldColor(startPosX - 1, startPosY, oldColor)) fillRegion(startPosX - 1, startPosY, newColor);
            if (diagonalyAdjacentPixelHasOldColor(startPosX + 1, startPosY, oldColor)) fillRegion(startPosX + 1, startPosY, newColor);
            break;
        }
    }
    //Reset startPos to original position so that we can start scanning down
    startPosX = x;
    startPosY = y;
    //Start filling down from (x, y)
    while (startPosY + 1 > 0) {
        if (currentImage.getPixelRef(x, startPosY + 1) == oldColor) {
            currentImage.setPixelColor(x, startPosY + 1, newColor);
            startPosY++;
        }
        else {
            if (diagonalyAdjacentPixelHasOldColor(startPosX - 1, startPosY, oldColor)) fillRegion(startPosX - 1, startPosY, newColor);
            if (diagonalyAdjacentPixelHasOldColor(startPosX + 1, startPosY, oldColor)) fillRegion(startPosX + 1, startPosY, newColor);
            break;
        }
    }
}

bool Editor::diagonalyAdjacentPixelHasOldColor(int x, int y, char oldColor) {
    if ((x > 0 && x < currentImage.getcurrentImage()[0].size()) &&
        (y > 0 && y < currentImage.getcurrentImage().size())) {
        if (currentImage.getPixelRef(x, y) == oldColor) {
            return true;
        }
    }
    return false;
}
//Here lies the most inefficient flood-fill of all time
void Editor::fillRegion(const int x, const int y, const char newColor) {
    auto& imageData = currentImage.getcurrentImage();

    if (newColor == oldColor) return;

    currentImage(x, y) = newColor;
    std::vector<std::vector<int>> pixelsAround;

    for (int* pixelAroundOffset : pixelsAroundOffset) { //For every pixel around coordinate in pixelsAround

        std::vector<int> temp = pixelMeetsCriteria(x + pixelAroundOffset[0], y + pixelAroundOffset[1], x, y, oldColor);

        if (temp.size() != 0) {

            pixelsAround.push_back(temp);
            currentImage(temp[0], temp[1]) = newColor;
        }
        else {
        }

    }
    for (std::vector<int> pix : pixelsAround) {
        fillRegion(pix[0], pix[1], newColor);
    }

}
std::vector<int> Editor::pixelMeetsCriteria(const int childX, const int childY, const int parentX, const int parentY, const char oldColor) {
    auto& imageData = currentImage.getcurrentImage();
    std::vector<int> childPix;
    childPix.push_back(childX);
    childPix.push_back(childY);

    if (((childX < 1) || (childY < 1)) || ((childY > currentImage.getSize()) || (childX > currentImage[0].size()))) {
        childPix.pop_back();
        childPix.pop_back();
        return childPix;
    }
    if (currentImage(childX, childY) != oldColor) {
        childPix.pop_back();
        childPix.pop_back();
        return childPix;
    }
    if (childX == parentX + -1 && childY == parentY + -1) { //the child pixel was on the Top left
        if (currentImage(childX + 1, childY) == oldColor || currentImage(childX, childY + 1) == oldColor) { //Is not blocked
            return childPix;
        }
    }

    if (childX == parentX + 1 && childY == parentY - 1) { //Top right
        if (currentImage(childX - 1, childY) == oldColor || currentImage(childX, childY + 1) == oldColor) {
            return childPix;
        }
    }
    if (childX == parentX + 1 && childY == parentY + 1) { //Bottom right
        if ((currentImage(childX - 1, childY) == oldColor) || (currentImage(childX, childY - 1) == oldColor)) {
            return childPix;
        }
    }
    if (childX == parentX - 1 && childY == parentY + 1) { //Bottom left
        if (currentImage(childX + 1, childY) == oldColor || currentImage(childX, childY - 1) == oldColor) {
            return childPix;
        }
    }
    if ((childX == parentX + 1) && (childY == parentY)) { //Right
        return childPix;
    }
    if (childX == parentX - 1 && childY == parentY) {//Left
        return childPix;
    }
    if (childX == parentX && childY == parentY + 1) {//Bottom
        return childPix;
    }
    if (childX == parentX && childY == parentY - 1) {//Top
        return childPix;
    }
    childPix.pop_back();
    childPix.pop_back();
    return childPix;
}

//Just displays the image name and the image contents 
void Editor::saveImageAsAndDisplay(const std::string name) {
    std::cout << "\n" << name << ".bmp\n";
    auto& imageData = currentImage.getcurrentImage();

    std::cout << "|";
    for (int i = 0; i < imageData[0].size(); i++) {
        std::cout << "-";
    }
    std::cout << "|\n";
    for (auto& line : imageData) {
        std::cout << "|";
        for (char& c : line) {
            std::cout << c;
        }
        std::cout << "|\n";
    }
    std::cout << "|";
    for (int i = 0; i < imageData[0].size(); i++) {
        std::cout << "-";
    }
    std::cout << "|\n";
}

