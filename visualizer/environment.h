
#ifndef _ENVIRONMENT_
#define _ENVIRONMENT_

#ifdef __APPLE_CC__
#include <glut/glut.h>
#else
#include <GL/glut.h>
#endif

#include "util.h"
#include "math3d.h"
#include "matrix.h"
#include <string>

using namespace std;
using namespace lib3d;


class Environment {
    friend void fdisplay();
    friend void freshape(int w, int h);
    friend void fbutton( int b, int state, int x, int y );
    friend void fidle();
    friend void fkeyboard(unsigned char inkey, int x, int y);
    friend void fmotion(int x, int y);

public:
    Environment();
    ~Environment();

private:
    /*  window height and width updated in the reshape function*/
    double windowHeight;
    double windowWidth;

    /*  The modelView and projection matrices are retrieved from the graphics
        card at the opportune moment.*/
    Matrix modelView;
    Matrix projection;

    /*  The point where the camera is aimed and about which the camera rotates.
        Set using the accessort lookAt().*/
    Vector3d cameraLookAtLoc;

    /*    firstX, firstY, firstTheta and firstPhi are member variables for use by
        the click-drag mechanism to move the camera, but even if the camera is
        not moving (i.e. if mouseLoc returns true), firstX and firstY still
        get set.*/
    int firstX;
    int firstY;
    double firstTheta;
    double firstPhi;

    /*  valid is a flag that should get set using the function invalidate() when
        the scene needs to recompute.*/
    bool valid;

    /*  computeTime and drawTime are for the framerate display*/
    double computeTime;
    double drawTime;

    /*    panOn is a variable for use by the click-drag mechanism for moving the
        camera.  When the flag gets set in button, the subsequent mouse-drag and
        mouse-up events are interpreted to pan the camera.*/
    bool panOn;

    /*  tare sets some things to zero*/
    void tare();

    /* helper function that sets the modelview and projection matrices to
       something reasonable*/
    void baseMatrices();

    /*    display gets called by the glut display function.*/
    void display();

    /*    updateTransformationMatrices sets modelView and projection to the result
        of opengl calls that retrieve those matrices from the graphics card.
        This function gets called by display.*/
    void updateTransformationMatrices();

protected:

    /*    These angles describe the current camera position, the 3-space
        coordinates of the camera should be accessed using the accessor
        function cameraLoc().*/
    double cameraTheta;
    double cameraPhi;
    double cameraRadius;

    /*    If true, calls compute over and over valid or not.*/
    bool animate;

    /*  flag determines whether the framerate gets displayed*/
    bool frameRateOn;

    /*  reshape gets called directly by the glut reshape function.*/
    virtual void reshape(int w, int h);

    /*    idle gets called by the glut idle function.*/
    virtual void idle();

    /*    button and motion get called by the like-named glut functions.
        Think twice before overriding if the same job could be done with mouseUp
        mouseDragged mouseDown*/
    virtual void button( int b, int state, int x, int y );
    virtual void motion( int x, int y );

    /*    keyboard gets called directly by the glut function keyboard.
        It should be overridden to handle key events.*/
    virtual void keyboard(unsigned char inkey, int x, int y);

    /*    mouseDown() get's called when the mouse button is first depressed.
        Override mouseDown to implement new mouse click behavior.  Return true
        to stop Environment from interpreting the mouse event and panning the
        camera.*/
    virtual bool mouseDown(const Vector2d& C);

    /*  mouseDragged()*/
    virtual void mouseDragged(const Vector2d& C);
    virtual void mouseUp(const Vector2d& C);

    /*    compute() is called by display() when the valid flag is set false.
        Override compute() to do work to compute what to draw.  Call
        invalidate() to set the valid flag to false, so that compute calls.*/
    virtual void compute();

    /*    draw is called after a clear and inside a matrix push.  Override draw()
        to add 3d graphics to the scene using ordinary gl calls like
        glVertex3f().*/
    virtual void draw() const;

    /*  drawOnScreen is called with a different matrix on the stack from draw.
        It's for drawing in 2d in pixel coordinates on the screen, like for a
        ui or something*/
    virtual void drawOnScreen() const;

    /*    drawAxes is a hopefully helpful utility function to draw the x, y and z
        axes in red green blue respectively.*/
    void drawAxes() const;

    /*    cameraLoc returns the current camera location in 3-space*/
    Vector3d cameraLoc() const;
    Vector3d lookAtLoc() const;

    /*    lookAt sets the camera's lookAt point*/
    void lookAt(const Vector3d& V);

    /*    pointScreenLoc reports the screen locaction of a given 3d point*/
    Vector2d pointScreenLoc(double x, double y, double z) const;
    Vector2d pointScreenLoc(const Vector3d& V) const;

    /*    flip reports the screen location of the point given coordinates of the
        form that gl button etc reports them (button is annoying in that way)*/
    Vector2d flip(int x, int y) const;

    /*    clickPoint returns the three space point that is getting clicked on
        through the screen location C and whose dot product with sight is k*/
    Vector3d clickPoint(const Vector2d& C,
                        const Vector3d& sight,
                        double k) const;

    /*  clickNearPoint returns whether the click point C is within distance tol
        of the point P on the screen.  This is helpful for iterating through a
        list of items which the user can click on and for each one, checking if
        the mouse location is close enough to be a hit*/
    bool clickNearPoint(const Vector2d& C, const Vector3d& P, double tol) const;

    /*  pointLoc gives screen coordinates for a 3d point*/
    Vector2d pointLoc(double x, double y, double z) const;

    /*  sets the valid flag to false to indicate that the scene should recompute
        (not redraw, recompute)*/
    void invalidate();

    /*  gets called by initGlut.  Override to turn things on and off, or set the
        clear color or whathaveyou*/
    virtual void glEnables();

    /*    for the framerate counter*/
    void displayFrameRate() const;
    string frameRateString() const;

    /*    little utility functions for drawing some stuff*/
    void wireframeCube(const Vector3d& P, double r) const;
    void wireframeOctahedron(const Vector3d& P, double r) const;

public:
    /*    init initializes all member variables that need it.
        The function init MUST be called before anything else.*/
    virtual void init();

    /*  initGlut Initilaizes glut.  Sets up the gl context, sets flags etc.
        Must be called before the mainLoop.*/
    void initGlut(int argc, char** args,
                  const char* windowName="",
                  int windowSizeX=640,
                  int windowSizeY=480);

    /*  Call this to start the glut machine.*/
    void mainLoop();
};


#endif
