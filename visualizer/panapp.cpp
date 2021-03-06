
#include "panapp.h"

#include "util.h"
#include "math3d.h"

using namespace std;
using namespace lib3d;


PanApp::PanApp()
    : cameraTheta(0)
    , cameraPhi(0)
    , cameraRadius(0)
    , firstX(0)
    , firstY(0)
    , firstTheta(0)
    , firstPhi(0)
{
}

PanApp::~PanApp()
{
}

void PanApp::init()
{
    panOn = false;
    cameraRadius = 80;
    cameraTheta = PI / 3.0;
    cameraPhi = PI / 6;

    glClearColor(1, 1, 1, 1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);

    printf("Use +/- to zoom\n");
}

Vector3d PanApp::cameraLoc() const
{
    return cameraLookAtLoc +
        cameraRadius * Vector3d(
            cos(cameraTheta) * cos(cameraPhi),
            sin(cameraTheta) * cos(cameraPhi),
            sin(cameraPhi));
}

void PanApp::lookAt(const Vector3d& V)
{
    cameraLookAtLoc = V;
}

Vector3d PanApp::lookAtLoc() const
{
    return cameraLookAtLoc;
}


void PanApp::display() const
{
    double before, after;

    before = doubleTime();

    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(
        40.0, /* field of view in degree */
        windowWidth / windowHeight, /* aspect ratio */
        0.01 * cameraRadius, /* Z near */
        100 * cameraRadius ); /* Z far */

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); //just in case i guess

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    Vector3d cLoc(cameraLoc());
    Vector3d lLoc(lookAtLoc());
    gluLookAt( cLoc.x, cLoc.y, cLoc.z,  lLoc.x, lLoc.y, lLoc.z,  0,0,1 );

    draw();

    glPopMatrix();

    glDisable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, windowWidth, 0.0, windowHeight);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    drawOnScreen();

    glColor3f(0.5,0.5,0.5);

    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glPopMatrix();
}


void PanApp::draw() const
{
    drawAxes();
}


void PanApp::drawAxes() const
{
    glPushAttrib(GL_LIGHTING);
    glDisable(GL_LIGHTING);

    glBegin(GL_LINES);
    double r = 10;
    glColor3f(1,0,0);
    glVertex3f(-r,0,0);
    glVertex3f( r,0,0);
    glColor3f(0,1,0);
    glVertex3f(0,-r,0);
    glVertex3f(0, r,0);
    glColor3f(0,0,1);
    glVertex3f(0,0,-r);
    glVertex3f(0,0, r);
    glEnd();

    glPopAttrib();
}


void PanApp::resize(int w, int h)
{
    windowHeight = h;
    windowWidth = w;

    glViewport(0, 0, (GLsizei)w, (GLsizei)h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(
        40.0, /* field of view in degree */
        windowWidth / windowHeight, /* aspect ratio */
        0.01 * cameraRadius, /* Z near */
        100 * cameraRadius ); /* Z far */

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); //just in case i guess
}


void PanApp::keyDown(unsigned char inkey)
{
    switch(inkey)
    {
        case '+':
        case '=':
            cameraRadius *= 0.9;
        break;

        case '_':
        case '-':
            cameraRadius /= 0.9;
        break;

        default:
        break;
    }
}

void PanApp::compute()
{
}

void PanApp::idle()
{
}

void PanApp::mouseDown(double x, double y)
{
    firstX = x;
    firstY = y;
    firstTheta = cameraTheta;
    firstPhi = cameraPhi;
    panOn = true;
}

void PanApp::mouseDragged(double x, double y)
{
    cameraTheta = firstTheta - 0.01*(x-firstX);
    cameraPhi = firstPhi + 0.01*(y-firstY);

    if(cameraPhi>0.5*PI) cameraPhi = 0.5*PI;
    if(cameraPhi<-0.5*PI) cameraPhi = -0.5*PI;
}

void PanApp::mouseUp(double x, double y)
{
    panOn = false;
}

void PanApp::drawOnScreen() const
{
}

