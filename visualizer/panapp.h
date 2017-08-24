
#ifndef _PANAPP_
#define _PANAPP_

#ifdef __APPLE_CC__
#include <glut/glut.h>
#else
#include <GL/glut.h>
#endif

#include "util.h"
#include "math3d.h"
#include "matrix.h"

#include "app.h"

#include <string>

using namespace std;
using namespace lib3d;


class PanApp : public App
{
public:
    PanApp();
    virtual ~PanApp();

public:
    /*  reshape gets called directly by the glut reshape function.*/
    virtual void reshape(int w, int h);

    /*  idle gets called by the glut idle function.*/
    virtual void idle();

    /*  button and motion get called by the like-named glut functions.
        Think twice before overriding if the same job could be done with mouseUp
        mouseDragged mouseDown*/
    virtual void button( int b, int state, int x, int y );
    virtual void motion( int x, int y );

    /*  keyboard gets called directly by the glut function keyboard.
        It should be overridden to handle key events.*/
    virtual void keyboard(unsigned char inkey, int x, int y);

    /*  mouseDown() get's called when the mouse button is first depressed.
        Override mouseDown to implement new mouse click behavior.  Return true
        to stop Environment from interpreting the mouse event and panning the
        camera.*/
    virtual bool mouseDown(const Vector2d& C);

    /*  mouseDragged()*/
    virtual void mouseDragged(const Vector2d& C);
    virtual void mouseUp(const Vector2d& C);

    /*  compute() is called by display() when the valid flag is set false.
        Override compute() to do work to compute what to draw.  Call
        invalidate() to set the valid flag to false, so that compute calls.*/
    virtual void compute();

    /*  display gets called by the glut display function.*/
    virtual void display() const;

    /*  draw is called after a clear and inside a matrix push.  Override draw()
        to add 3d graphics to the scene using ordinary gl calls like
        glVertex3f().*/
    virtual void draw() const;


private:
    /*  window height and width updated in the reshape function*/
    double windowHeight;
    double windowWidth;

    /*  The point where the camera is aimed and about which the camera rotates.
        Set using the accessort lookAt().*/
    Vector3d cameraLookAtLoc;

    /*  firstX, firstY, firstTheta and firstPhi are member variables for use by
        the click-drag mechanism to move the camera, but even if the camera is
        not moving (i.e. if mouseLoc returns true), firstX and firstY still
        get set.*/
    int firstX;
    int firstY;
    double firstTheta;
    double firstPhi;

    /*  panOn is a variable for use by the click-drag mechanism for moving the
        camera.  When the flag gets set in button, the subsequent mouse-drag and
        mouse-up events are interpreted to pan the camera.*/
    bool panOn;

    /*  tare sets some things to zero*/
    void tare();

    /*  updateTransformationMatrices sets modelView and projection to the result
        of opengl calls that retrieve those matrices from the graphics card.
        This function gets called by display.*/
    void updateTransformationMatrices();

protected:

    /*  These angles describe the current camera position, the 3-space
        coordinates of the camera should be accessed using the accessor
        function cameraLoc().*/
    double cameraTheta;
    double cameraPhi;
    double cameraRadius;

    /*  drawOnScreen is called with a different matrix on the stack from draw.
        It's for drawing in 2d in pixel coordinates on the screen, like for a
        ui or something*/
    virtual void drawOnScreen() const;

    /*  drawAxes is a hopefully helpful utility function to draw the x, y and z
        axes in red green blue respectively.*/
    void drawAxes() const;

    /*    cameraLoc returns the current camera location in 3-space*/
    Vector3d cameraLoc() const;
    Vector3d lookAtLoc() const;

    /*  lookAt sets the camera's lookAt point*/
    void lookAt(const Vector3d& V);

    /*  flip reports the screen location of the point given coordinates of the
        form that gl button etc reports them (button is annoying in that way)*/
    Vector2d flip(int x, int y) const;

    /*  clickNearPoint returns whether the click point C is within distance tol
        of the point P on the screen.  This is helpful for iterating through a
        list of items which the user can click on and for each one, checking if
        the mouse location is close enough to be a hit*/
    bool clickNearPoint(const Vector2d& C, const Vector3d& P, double tol) const;

    /*  pointLoc gives screen coordinates for a 3d point*/
    Vector2d pointLoc(double x, double y, double z) const;

public:
    /*  init initializes all member variables that need it.
        The function init MUST be called before anything else.*/
    virtual void init();

    /*  Call this to start the glut machine.*/
    void mainLoop();
};


#endif
