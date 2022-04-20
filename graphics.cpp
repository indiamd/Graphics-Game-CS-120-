//
// Created by India Davis on 4/12/22.
//

#include "graphics.h"
#include <iostream>
#include <time.h>
#include <vector>
#include "Button.h"
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
vector<Quad> borders;
vector<Button> traps;
vector<Quad> confetti;
vector<Button> mousey;
vector<Button> cheese;
vector<Quad> background;
int foundMouse =0;
int foundCheese=0;
float timeCount = 0.00;


void init() {
    width = 500;
    height = 500;
    srand(time(0));
    initMouse();
    initCheese();
    initTraps();
    initBorders();
    initConfetti();
    initBackground();
}

void initBackground(){
    int cent = 24;
    for (int i=0; i< 10; i++){
        background.push_back(Quad({.5, .32, .22}, {cent, 250}, 48, 500));
        background.push_back(Quad({.34, .2, .12}, {cent+25, 250}, 4, 500));
        cent += 50;
    }
}

void initConfetti(){
    for (int i = 0; i <300; ++i) {
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
    Button mouseyCenter= Button({.5, .5, .5}, {rand() % 495 + 5, rand() % 495 + 5}, 20, 18, "");
    mouseyCenter.getRandCoord();
    Button mouseyCenter2= Button({.5, .5, .5}, {mouseyCenter.getCenterX()-10, mouseyCenter.getCenterY()+2}, 15, 15, "");
    Button mouseyCenter3= Button({.5, .5, .5}, {mouseyCenter.getCenterX()+7, mouseyCenter.getCenterY()+2}, 15, 15, "");
    Button mouseyHead= Button({.5, .5, .5}, {mouseyCenter.getCenterX()-17, mouseyCenter.getCenterY()+2}, 8, 8, "");
    Button mouseyTail= Button({.5, .5, .5}, {mouseyCenter.getCenterX()+16, mouseyCenter.getCenterY()+4}, 10, 2, "");
    Button mouseyTail2= Button({.5, .5, .5}, {mouseyTail.getRightX(), mouseyTail.getCenterY()-5}, 2, 10, "");
    Button mouseyNose= Button({0, 0, 0}, {mouseyHead.getCenterX()-6, mouseyHead.getCenterY()}, 4, 4, "");
    Button mouseyEye= Button({1, 1, 1}, {mouseyHead.getCenterX()+3, mouseyHead.getCenterY()-2}, 4, 4, "");
    Button mouseyEye2= Button({0, 0, 0}, {mouseyEye.getCenterX(), mouseyEye.getCenterY()}, 3, 3, "");
    Button mouseyEar= Button({.5, .5, .5}, {mouseyCenter.getCenterX()-10, mouseyCenter.getCenterY()-8}, 8, 8, "");
    mousey.push_back(mouseyCenter);
    mousey.push_back(mouseyCenter2);
    mousey.push_back(mouseyCenter3);
    mousey.push_back(mouseyHead);
    mousey.push_back(mouseyTail);
    mousey.push_back(mouseyTail2);
    mousey.push_back(mouseyNose);
    mousey.push_back(mouseyEye);
    mousey.push_back(mouseyEye2);
    mousey.push_back(mouseyEar);

}

void initCheese(){
    Button cheeseCenter = Button({1, .7, 0}, {rand() % 495 + 5, rand() % 495 + 5}, 20, 20, "");
    cheeseCenter.getRandCoord2();
    Button cheeseHole1 = Button({1, 1, 1}, {cheeseCenter.getCenterX()-3, cheeseCenter.getCenterY()-3}, 5, 5, "");
    Button cheeseHole2 = Button({1, 1, 1}, {cheeseCenter.getCenterX()+9, cheeseCenter.getCenterY()-2}, 4, 4, "");
    Button cheeseHole3 = Button({1, 1, 1}, {cheeseCenter.getCenterX()+2, cheeseCenter.getCenterY()+5}, 6, 6, "");
    cheese.push_back(cheeseCenter);
    cheese.push_back(cheeseHole1);
    cheese.push_back(cheeseHole2);
    cheese.push_back(cheeseHole3);
}

void initTraps(){
    for (int i=0; i < 50; i++){
        traps.push_back(Button({1, 0, 0}, {rand() % 490 + 10, rand() % 495 + 5}, 20, 10, ""));
    }
}

void initBorders(){
    borders.push_back(Quad({0,0,0}, {30,-30}, 500, 500));
    borders.push_back(Quad({0,0,0}, {530,30}, 500, 500));
    borders.push_back(Quad({0,0,0}, {470,530}, 500, 500));
    borders.push_back(Quad({0,0,0}, {-30,470}, 500, 500));
    borders.push_back(Quad({.35,.35,.35}, {330,250}, 44, 14));
    borders.push_back(Quad({.2,.2,.2}, {330,250}, 44, 2));
    borders.push_back(Quad({.2,.2,.2}, {330,245}, 44, 2));
    borders.push_back(Quad({.2,.2,.2}, {330,255}, 44, 2));
    borders.push_back(Quad({.35,.35,.35}, {315,250}, 17, 19));
    borders.push_back(Quad({.1,.1,.1}, {330,250}, 8, 6));

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
        for (Quad &b : background){
            b.draw();
        }

        if (foundMouse == 0){
            for (Button &m : mousey)
            m.draw();
        }
        if (foundCheese == 0){
            for (Button &c : cheese){
                c.draw();
            }
        }
        if (foundCheese > 0 && foundMouse >> 0) {
            screen = win;
        }

        for (Button &t : traps){
            t.draw();
            /*for (Button &T : traps){
                while (t.isOverlappingBtn(t)){
                    t.move(-10, -5);
                }
            }*/
            while (t.isOverlappingBtn(mousey[0])  || t.isOverlappingBtn(cheese[0])){
                t.move(20, 20);
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
        glRasterPos2i(width/2-label.length()*3, height/2-label.length());
        for (const char &letter : label) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, letter);
        }
        string label2 = "Score: " + to_string(timeCount) + " seconds";
        glRasterPos2i(width/2-label.length()*3, height/2-label.length()*3+ 30);
        for (const char &letter : label2) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, letter);
        }
        for (Quad &c : confetti) {
            c.draw();
            if (c.getTopY() == 500){
                c.move(0,-500);
            }
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
            if (borders[2].getTopY()<=495) {
                for (int i=0; i < borders.size(); i++){
                    borders[i].move(0,5);
                }
            }
            break;
        case GLUT_KEY_LEFT:
            if (borders[2].getLeftX()>=5){
                for (int i=0; i < borders.size(); i++){
                    borders[i].move(-5,0);
                }
            }
            break;

        case GLUT_KEY_RIGHT:
            if (borders[0].getRightX()<=495){
                for (int i=0; i < borders.size(); i++){
                    borders[i].move(5,0);
                }
            }
            break;


        case GLUT_KEY_UP:
            if (borders[0].getBottomY()>=5) {
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
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && (mousey[0].isOverlapping(x + 0, y + 0) || mousey[1].isOverlapping(x + 0, y + 0) || mousey[2].isOverlapping(x + 0, y + 0))) {
            mousey[0].pressDown();
            foundMouse ++;
        }
        else{
            mousey[0].release();
        }

        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && cheese[0].isOverlapping(x + 0, y + 0)) {
            cheese[0].pressDown();
            foundCheese ++;
        }
        else{
            cheese[0].release();
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
    if (screen == win){
        for (Quad &c : confetti) {
            c.move(0,5);
            if (c.getTopY() > height) {
                c.move(rand() % int(width), -c.getHeight());
            }
        }
    }

        glutPostRedisplay();
        glutTimerFunc(10, timer, dummy);
        if (screen == play) {
            timeCount += .01;
        }

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
