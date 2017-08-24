
#ifndef _PANAPP_
#define _PANAPP_

#include "opengl.h"
#include "util.h"
#include "math3d.h"

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
    /*  resize gets called directly by the glut reshape function.*/
    virtual void resize(int w, int h);

    /*  idle gets called by the glut idle function.*/
    virtual void idle();

    /*  callbacks for keyboard button presses.*/
    virtual void keyDown(unsigned char inkey);

    /*  mouseDown() get's called when the mouse button is first depressed.
        Override mouseDown to implement new mouse click behavior.  Return true
        to stop Environment from interpreting the mouse event and panning the
        camera.*/
    virtual void mouseDown(double x, double y);

    /*  mouseDragged()*/
    virtual void mouseDragged(double x, double y);
    virtual void mouseUp(double x, double y);

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

public:
    virtual void init();
};


#endif
