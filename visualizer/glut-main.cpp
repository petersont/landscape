#include "graphapp.h"

#ifdef __APPLE_CC__
#include <glut/glut.h>
#else
#include <GL/glut.h>
#endif


void fdisplay();
void freshape(int w, int h);
void fidle();
void fmotion(int x, int y);
void fbutton( int b, int state, int x, int y );
void fkeyboard(unsigned char inkey, int x, int y);

App* gApp = NULL;

void initGlut(
    const char* windowName,
    int windowSizeX,
    int windowSizeY)
{
    int argc = 0;
    char** args = NULL;

    // initilaize glut
    glutInit( &argc, args );
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );

    // bring up a window called "Mesh"
    glutInitWindowSize( windowSizeX, windowSizeY );
    glutCreateWindow( windowName );
}


void mainLoop(App* app)
{
    gApp = app;

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

void fdisplay()
{
    static bool firstTime = true;
    if( firstTime )
    {
        gApp->init();
        firstTime = false;
    }

    gApp->compute();
    gApp->display();
    glutSwapBuffers();
    glutPostRedisplay();
}

void freshape(int w, int h)
{
    gApp->reshape(h,w);
}

void fbutton( int b, int state, int x, int y )
{
    gApp->button(b,state,x,y);
    glutPostRedisplay();
}

void fidle()
{
    gApp->idle();
}

void fkeyboard(unsigned char inkey, int x, int y)
{
    gApp->keyboard(inkey, x, y);
    glutPostRedisplay();
}

void fmotion(int x, int y)
{
    gApp->motion(x,y);
    glutPostRedisplay();
}


int main(int argc, char** args)
{
    if( argc < 2 )
    {
        printf("Takes a filename as an argument.\n");
        return 0;
    }

    GraphApp app(args[1]);

    initGlut("Behold", 640, 480);

    mainLoop(&app);
}

