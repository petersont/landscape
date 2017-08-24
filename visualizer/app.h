#ifndef _APP_
#define _APP_

#include "math3d.h"

class App
{
public:
    /*  gets called with opengl context once before any drawing.*/
    virtual void init() {}

    /*  gets called when the window is resized.*/
    virtual void resize(int w, int h) {}

    /*  callbacks for keyboard button presses.*/
    virtual void keyDown(unsigned char inkey) {}
    virtual void keyUp(unsigned char inkey) {}

    /*  mouseDown() get's called when the mouse button is first depressed.
        Override mouseDown to implement new mouse click behavior.  Return true
        to stop Environment from interpreting the mouse event and panning the
        camera.*/
    virtual void mouseDown(double x, double y) {}
    virtual void mouseDragged(double x, double y) {}
    virtual void mouseUp(double x, double y) {}

    /*  compute() is called by display() when the valid flag is set false.
        Override compute() to do work to compute what to draw.  Call
        invalidate() to set the valid flag to false, so that compute calls.*/
    virtual void compute() {}

    /*  display gets called by the glut display function.*/
    virtual void display() const {}

    /*  draw is called after a clear and inside a matrix push.  Override draw()
        to add 3d graphics to the scene using ordinary gl calls like
        glVertex3f().*/
    virtual void draw() const {}
};

#endif
