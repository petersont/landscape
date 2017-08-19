
#include "environment.h"

#include "util.h"
#include "math3d.h"
#include "matrix.h"


using namespace std;
using namespace lib3d;


void display();
void reshape(int w, int h);
void idle();
void motion(int x, int y);
void button( int b, int state, int x, int y );
void keyboard(unsigned char inkey, int x, int y);

Environment* gE = NULL;


Vector2d Environment::pointScreenLoc(double x, double y, double z) const
{
    Matrix X(4,1);

    double dx[]={x,y,z,1};
    X.set(dx);

    X = projection*modelView*X;
    X/= X.entries[0][3];

    return Vector2d(0.5*windowWidth*(X.entries[0][0]+1),
                    0.5*windowHeight*(X.entries[0][1]+1));
}

Vector2d Environment::pointScreenLoc(const Vector3d& V) const
{
    return pointScreenLoc(V.x, V.y, V.z);
}


Vector2d Environment::flip(int x, int y) const
{
    Vector2d C( x,windowHeight-y );
    return C;
}


bool Environment::clickNearPoint(const Vector2d& C,
                                 const Vector3d& P,
                                 double tol) const
{
    return (pointScreenLoc(P.x, P.y, P.z) - C).mag() < tol;
}


Vector3d Environment::clickPoint(const Vector2d& C,
                                 const Vector3d& sight,
                                 double k) const
{
    Matrix M(projection*modelView);

    double xp = 2.0*C.x/windowWidth - 1.0;
    double yp = 2.0*C.y/windowHeight - 1.0;

    double** m = M.entries;
    Matrix3d  A(m[0][0]-xp*m[0][3], m[1][0]-xp*m[1][3], m[2][0]-xp*m[2][3],
                m[0][1]-yp*m[0][3], m[1][1]-yp*m[1][3], m[2][1]-yp*m[2][3],
                sight.x, sight.y, sight.z );

    Vector3d B(xp*m[3][3] - m[3][0], yp*m[3][3] - m[3][1], k);
    return (A.inverse())*B;
}


void Environment::invalidate()
{
    valid = false;
    glutPostRedisplay();
}


Environment::Environment() {tare();}
Environment::~Environment() {}


void Environment::tare()
{
    /*
    These angles describe the current camera position, the 3space
    coordinates of the camera should always be accessed using the accessor
    function cameraLoc
    */
    cameraTheta=0;
    cameraPhi=0;
    cameraRadius=0;

    /*
    firstX, firstY, firstTheta and firstPhi are member variables for use by the
    click-drag mechanism to move the camera, but even if the camera is not
    moving (i.e. if mouseLoc returns true), firstX and firstY still get set
    */
    firstX=0;
    firstY=0;
    firstTheta=0;
    firstPhi=0;
}


void Environment::init()
{
    valid = true;
    panOn = false;
    frameRateOn = false;
    animate = false;

    modelView.setSize(4,4);
    projection.setSize(4,4);

    cameraRadius = 80;
    cameraTheta = PI / 3.0;
    cameraPhi = PI / 6;
}

Vector3d Environment::cameraLoc() const
{
    return cameraLookAtLoc+
        cameraRadius*Vector3d(cos(cameraTheta)*cos(cameraPhi),
                              sin(cameraTheta)*cos(cameraPhi),
                              sin(cameraPhi));
}

void Environment::lookAt(const Vector3d& V)
{
    cameraLookAtLoc = V;
}

Vector3d Environment::lookAtLoc() const
{
    return cameraLookAtLoc;
}

void Environment::updateTransformationMatrices()
{
    double mm[16];
    glGetDoublev(GL_MODELVIEW_MATRIX, mm);
    double pm[16];
    glGetDoublev(GL_PROJECTION_MATRIX, pm);

    modelView.set(mm);
    modelView = modelView.transpose();
    projection.set(pm);
    projection = projection.transpose();
}


void Environment::display()
{
    double before, after;

    if(!valid || animate)
    {
        before = doubleTime();
        compute();
        after = doubleTime();
        computeTime = after-before;

        valid = true;
    }

    before = doubleTime();

    glEnable(GL_DEPTH_TEST);

    //sets the modelview and projection matrix (clipping planes)
    baseMatrices();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    Vector3d cLoc(cameraLoc());
    Vector3d lLoc(lookAtLoc());
    gluLookAt( cLoc.x, cLoc.y, cLoc.z,  lLoc.x, lLoc.y, lLoc.z,  0,0,1 );
    updateTransformationMatrices();

    draw();

    glPopMatrix();


    /*draw on the screen*/

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
    if(frameRateOn)
        displayFrameRate();

    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glPopMatrix();

    glutSwapBuffers();

    after = doubleTime();

    drawTime = after-before;

    if(animate)
        glutPostRedisplay();
}


void Environment::draw() const
{
    drawAxes();
}


void Environment::drawAxes() const
{
    glPushAttrib(GL_LIGHTING);
    glDisable(GL_LIGHTING);

    //draw axes
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



void Environment::button( int b, int state, int x, int y )
{
    if( state == 0 ) //button down
    {
        if( !mouseDown(flip(x,y)) )
        {
            firstX = x;
            firstY = y;
            firstTheta = cameraTheta;
            firstPhi = cameraPhi;
            panOn = true;
        }
    }

    if( state == 1 ) //button up
    {
        mouseUp(flip(x,y));
        panOn = false;
    }
}


bool Environment::mouseDown(const Vector2d& C)
{
    return false;
}


void Environment::motion(int x, int y)
{
    if( panOn )
    {
        cameraTheta = firstTheta - 0.01*(x-firstX);
        cameraPhi = firstPhi + 0.01*(y-firstY);

        if(cameraPhi>0.5*PI) cameraPhi = 0.5*PI;
        if(cameraPhi<-0.5*PI) cameraPhi = -0.5*PI;
    }

    mouseDragged(flip(x,y));
}


void Environment::baseMatrices()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(
        40.0, /* field of view in degree */
        windowWidth/windowHeight, /* aspect ratio */
        0.01*cameraRadius, /* Z near */
        100*cameraRadius ); /* Z far */

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); //just in case i guess
}


void Environment::reshape(int h, int w)
{
    windowHeight = h;
    windowWidth = w;

    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    baseMatrices(); //uses windowHeight and windowWidth
}


void Environment::keyboard(unsigned char inkey, int x, int y)
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


void fdisplay() { gE->display(); }
void freshape(int w, int h) { gE->reshape(h,w); }
void fbutton( int b, int state, int x, int y )
    { gE->button(b,state,x,y); glutPostRedisplay(); }
void fidle() { gE->idle(); }
void fkeyboard(unsigned char inkey, int x, int y)
    { gE->keyboard(inkey, x, y); glutPostRedisplay(); }
void fmotion(int x, int y) { gE->motion(x,y); glutPostRedisplay(); }


void Environment::initGlut(int argc,
                           char** args,
                           const char* windowName,
                           int windowSizeX,
                           int windowSizeY)
{
    // initilaize glut
    glutInit( &argc, args );
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );

    // bring up a window called "Mesh"
    glutInitWindowSize( windowSizeX, windowSizeY );
    glutCreateWindow( windowName );

    // call the virtual function in case somebody wants more enables
    glEnables();
}


void Environment::glEnables()
{
    // some default enables etc
    glClearColor(1,1,1,1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
}


void Environment::mainLoop()
{
    gE = this;

    //Install the functions in this file as callbacks
    glutDisplayFunc(fdisplay);
    glutReshapeFunc(freshape);
    glutIdleFunc(fidle);
    glutMotionFunc(fmotion);
    glutMouseFunc(fbutton);
    glutKeyboardFunc(fkeyboard);

    //leave the rest to glut
    glutMainLoop();
}


void Environment::wireframeCube(const Vector3d& P, double r) const
{
    Vector3d cubeVertices[8];
        int counter = 0;

        for(int k=0; k<2; k++) for(int j=0; j<2; j++) for(int i=0; i<2; i++)
            cubeVertices[counter++].set(i-0.5,j-0.5,k-0.5);

    glBegin(GL_LINES);
        for(int i=0; i<8; i++) for(int j=0; j<8; j++)
        {
            double d = (cubeVertices[i]-cubeVertices[j]).mag();
            if( d < 1.1 && d > 0.1 )
            {
                Vector3d Q1,Q2;

                Q1 = P+r*cubeVertices[i];
                Q2 = P+r*cubeVertices[j];
                glVertex3f(Q1.x, Q1.y, Q1.z);
                glVertex3f(Q2.x, Q2.y, Q2.z);
            }
        }
    glEnd();
}


void Environment::wireframeOctahedron(const Vector3d& P, double r) const
{
    double V[6][3] = {{1,0,0}, {-1,0,0}, {0,1,0}, {0,-1,0}, {0,0,1}, {0,0,-1}};
    Vector3d vertices[6];
    for(int i=0; i<6; i++)
        vertices[i].set(V[i][0], V[i][1], V[i][2]);

    glBegin(GL_LINES);
        Vector3d Q1, Q2;
        for(int i=0; i<6; i++) for(int j=0; j<6; j++)
        {
            double d = (vertices[i]-vertices[j]).mag();
            if( d < 1.5 && d > 0.1 )
            {
                Q1 = P+r*vertices[i];
                Q2 = P+r*vertices[j];
                glVertex3f(Q1.x, Q1.y, Q1.z);
                glVertex3f(Q2.x, Q2.y, Q2.z);
            }
        }
    glEnd();
}


void Environment::displayFrameRate() const
{
    glPushMatrix();
    glTranslatef(2,2,0);

    glScalef(.1,.1,.1);
    string frs(frameRateString());

    const char* s = frs.c_str();

    for(int i=0; s[i]; i++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, s[i]);

    glPopMatrix();
}


string Environment::frameRateString() const
{
    char s[255];
    s[0]=0;

    double lcomputeTime = clamp(computeTime, 0, 1000.0);
    double ldrawTime = clamp(drawTime, 0, 1000.0);
    double framerate = clamp(1.0/(computeTime+drawTime), 0, 1000000.0);

    sprintf( s, "CT: %3.3f DT: %3.3f FPS: %3.3f\n",
        lcomputeTime, ldrawTime, framerate );
    return string(s);
}


void Environment::compute() {}
void Environment::idle() {}
void Environment::mouseDragged(const Vector2d& C) {}
void Environment::mouseUp(const Vector2d& C) {}
void Environment::drawOnScreen() const {}
