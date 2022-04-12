//
// Created by India Davis on 4/12/22.
//

#include "graphics.h"
#include <iostream>
#include <time.h>
#include <vector>
#include "Button.h"
#include "Circle.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

GLdouble width, height;
int wd;
enum Screen{start, play, win, lose};
Screen screen = start;
//create on-screen objects
Button startBtn = Button({.5, .7, 1}, {250,250}, 100, 50, "Start");
Button mousey = Button({.5, .5, .5}, {rand() % 495 + 5, rand() % 495 + 5}, 10, 10, "");
Button cheese = Button({1, .7, 0}, {rand() % 495 + 5, rand() % 495 + 5}, 10, 10, "");
vector<Quad> borders;
vector<Button> traps;
vector<Quad> confetti;


void init() {
    width = 500;
    height = 500;
    srand(time(0));
    initMouse();
    initCheese();
    initTraps();
    initBorders();
    initConfetti();
}

void initConfetti(){
    for (int i = 0; i < 150; ++i) {
        int color = rand() % 4 + 1;
        double r,g,b;
        if (color == 1){
            r = 1;
            g = 0;
            b = 0;
        }
        else if (color == 2){
            r = 0;
            g = 1;
            b = 0;
        }
        else if (color == 3){
            r = 0;
            g = 0;
            b = 1;
        }
        else {
            r = 1;
            g = 1;
            b = 0;
        }
        confetti.push_back(Quad({r, g, b}, {rand() % int(width), -(rand() % int(height))}, rand() % 5 + 1, rand() % 5 + 1));
    }
};

void initMouse(){
    mousey.getRandCoord();
}

void initCheese(){
    cheese.getRandCoord();
}

void initTraps(){
    for (int i=0; i < 30; i++){
        traps.push_back(Button({1, 0, 0}, {rand() % 490 + 10, rand() % 495 + 5}, 20, 10, "X"));
    }
}

void initBorders(){
    borders.push_back(Quad({0,0,0}, {10,-10}, 500, 500));
    borders.push_back(Quad({0,0,0}, {510,10}, 500, 500));
    borders.push_back(Quad({0,0,0}, {490,510}, 500, 500));
    borders.push_back(Quad({0,0,0}, {-10,490}, 500, 500));

}

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Black and opaque
}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
    // tell OpenGL to use the whole window for drawing
    glViewport(0, 0, width*2, height*2);

    // do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f);

    glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer with current clearing color

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    /*
     * Draw here
     */

    if (screen == start){
        startBtn.draw();
    }

    else if (screen == play){
        mousey.draw();
        cheese.draw();
        /*for (int i=0; i<traps.size(); i++){
            for (int j=0; j<i; j++)
            while (traps[i].isOverlappingBtn(traps[j])){
                traps[i].move(-10, -5);
            }
        }*/

        for (Button &t : traps){
            t.draw();
            while (t.isOverlappingBtn(mousey) || t.isOverlappingBtn(cheese)){
                t.move(10, 10);
            }
        }

        for (Quad &b : borders){
            b.draw();
        }
    }

    else if (screen == lose){
        string label = "You got stuck in a trap!";
        glRasterPos2i(width/2-label.length(), height/2-label.length());
        for (const char &letter : label) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, letter);
        }
    }
    else if (screen == win){
        string label = "You win!";
        glRasterPos2i(width/2-label.length(), height/2-label.length());
        for (const char &letter : label) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, letter);
        }
        for (Quad &c : confetti) {
            c.draw();
        }
    }


    glFlush();  // Render now
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y) {
    // escape
    if (key == 27) {
        glutDestroyWindow(wd);
        exit(0);
    }


    glutPostRedisplay();
}

void kbdS(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_DOWN:
            if (borders[2].getTopY()<=500) {
                for (int i=0; i < borders.size(); i++){
                    borders[i].move(0,5);
                }
            }
            break;
        case GLUT_KEY_LEFT:
            if (borders[2].getLeftX()>=0){
                for (int i=0; i < borders.size(); i++){
                    borders[i].move(-5,0);
                }
            }
            break;

        case GLUT_KEY_RIGHT:
            if (borders[0].getRightX()<=500){
                for (int i=0; i < borders.size(); i++){
                    borders[i].move(5,0);
                }
            }
            break;


        case GLUT_KEY_UP:
            if (borders[0].getBottomY()>=0) {
                for (int i=0; i < borders.size(); i++){
                    borders[i].move(0,-5);
                }
            }
            break;
    }

    glutPostRedisplay();
}

void cursor(int x, int y) {

    glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {
    if (screen == start) {
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && startBtn.isOverlapping(x + 0, y + 0)) {
            startBtn.pressDown();
            screen = play;
        } else {
            startBtn.release();
        }
        glutPostRedisplay();
    }

    else  if (screen == play) {
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mousey.isOverlapping(x + 0, y + 0)) {
            mousey.pressDown();
            screen = win;
        }
        else{
            mousey.release();
        }

        for (int i=0; i<traps.size(); i++) {
            if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && traps[i].isOverlapping(x + 0, y + 0)) {
                traps[i].pressDown();
                screen = lose;
            }
            else{
                traps[i].release();
            }
        }

        glutPostRedisplay();

    }
}

void timer(int dummy) {
    for (Quad &c : confetti) {
                c.move(0,5);
                if (c.getTopY() > height) {
                    c.move(rand() % int(width), -c.getHeight());
                }
            }
    glutPostRedisplay();
    glutTimerFunc(30, timer, dummy);
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
    init();

    glutInit(&argc, argv);          // Initialize GLUT

    glutInitDisplayMode(GLUT_RGBA);

    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(100, 200); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    wd = glutCreateWindow("Mouse and Cheese" /* title */ );

    // Register callback handler for window re-paint event
    glutDisplayFunc(display);

    // Our own OpenGL initialization
    initGL();

    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);

    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);

    // handles mouse movement
    glutPassiveMotionFunc(cursor);

    // handles mouse click
    glutMouseFunc(mouse);

    // handles timer
    glutTimerFunc(0, timer, 0);

    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}
