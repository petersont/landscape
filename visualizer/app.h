#ifndef _APP_
#define _APP_

class App
{
public:
    /*  reshape gets called directly by the glut reshape function.*/
    virtual void reshape(int w, int h) {}

    /*  idle gets called by the glut idle function.*/
    virtual void idle() {}

    /*  button and motion get called by the like-named glut functions.
        Think twice before overriding if the same job could be done with mouseUp
        mouseDragged mouseDown*/
    virtual void button( int b, int state, int x, int y ) {}
    virtual void motion( int x, int y ) {}

    /*  keyboard gets called directly by the glut function keyboard.
        It should be overridden to handle key events.*/
    virtual void keyboard(unsigned char inkey, int x, int y) {}

    /*  mouseDown() get's called when the mouse button is first depressed.
        Override mouseDown to implement new mouse click behavior.  Return true
        to stop Environment from interpreting the mouse event and panning the
        camera.*/
    virtual bool mouseDown(const lib3d::Vector2d& C) {return false;}
    virtual void mouseDragged(const lib3d::Vector2d& C) {}
    virtual void mouseUp(const lib3d::Vector2d& C) {}

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
