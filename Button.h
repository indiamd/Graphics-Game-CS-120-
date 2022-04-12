//
// Created by India Davis on 4/12/22.
//

#ifndef M4OEP_LARGE_IDAVIS1_BUTTON_H
#define M4OEP_LARGE_IDAVIS1_BUTTON_H


#include "Quad.h"
#include <string>

class Button : public Quad {
private:
    std::string label;
    color originalFill, hoverFill, pressFill;

public:
    Button(color fill, point center, unsigned int width, unsigned int height, std::string label);
    /* Uses OpenGL to draw the box with the label on top */
    virtual void draw() const override;

    /* Returns true if the coordinate is inside the box */
    bool isOverlapping(int x, int y) const;

    bool isOverlappingBtn(Button &btn) const;

    /* Change color of the Button when the user is hovering over it */
    void hover();

    /* Change color of the Button when the user is clicking on it */
    void pressDown();

    /* Change the color back when the user is not clicking/hovering */
    void release();

    //gets random starting coordinates for buttons
    point getRandCoord();
};



#endif //M4OEP_LARGE_IDAVIS1_BUTTON_H
