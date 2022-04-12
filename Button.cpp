//
// Created by India Davis on 4/12/22.
//

#include "Button.h"
#include "graphics.h"
using namespace std;

Button::Button(color fill, point center, unsigned int width, unsigned int height, std::string label) : Quad(fill, center, width, height) {
    this->label = label;
    originalFill = fill;
    hoverFill = {fill.red + 0.5, fill.green + 0.5, fill.blue + 0.5};
    pressFill = {fill.red - 0.5, fill.green - 0.5, fill.blue - 0.5};
}


void Button::draw() const {
    Quad::draw();
    glColor3f(0, 0, 0);
    glRasterPos2i(center.x - (4 * label.length()), center.y + 7);
    for (const char &letter : label) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
    }
}

/* Returns true if the coordinate is inside the box */
bool Button::isOverlapping(int x, int y) const {
    // DONE: Implement
    if (x<getLeftX() || x>getRightX() || y<getTopY() || y>getBottomY()){
        return false;
    }
    else{
        return true;
    }
}

bool Button::isOverlappingBtn(Button &btn) const {
    // DONE: Implement
    if (getRightX()< btn.getLeftX() || getLeftX()> btn.getRightX() || getTopY()>btn.getBottomY() || getBottomY() > btn.getBottomY()){
        return false;
    }
    else{
        return true;
    }
}

/* Change color of the box when the user is hovering over it */
void Button::hover() {
    setColor(hoverFill);
}

/* Change color of the box when the user is clicking on it */
void Button::pressDown() {
    setColor(pressFill);
}

/* Change the color back when the user is not clicking/hovering */
void Button::release() {
    setColor(originalFill);
}

void Button::getRandCoord() {
    srand (time(NULL));
    int rand1 = rand() % 495 + 5;
    int rand2 = rand() % 495 + 5;
    center= {rand1, rand2};
}