
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>

#include <SDL.h>

#include <stdlib.h>

#include "graphapp.h"

static bool quitting = false;
static SDL_Window *window = NULL;
static SDL_GLContext gl_context;

const int WIDTH = 640;
const int HEIGHT = 480;

App* gApp = NULL;

void render()
{
    SDL_GL_MakeCurrent(window, gl_context);

    static bool firstTime = true;
    if( firstTime )
    {
        gApp->init();
        gApp->resize(WIDTH, HEIGHT);
        firstTime = false;
    }

    gApp->compute();
    gApp->display();

    SDL_GL_SwapWindow(window);
}

int SDLCALL watch(void *userdata, SDL_Event* event)
{
    if (event->type == SDL_APP_WILLENTERBACKGROUND)
        quitting = true;

    return 1;
}

int main(int argc, char *argv[])
{
    if( argc < 2 )
    {
        printf("Takes a filename as an argument.\n");
        return 0;
    }

    GraphApp app(argv[1]);
    gApp = &app;

    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_EVENTS) != 0)
    {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow(
        "Behold",
        100, 100, 640, 480,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    gl_context = SDL_GL_CreateContext(window);
    SDL_AddEventWatch(watch, NULL);

    bool mouseDown = false;
    while( ! quitting )
    {
        SDL_Event event;
        while( SDL_PollEvent(&event) )
        {
            switch ( event.type )
            {
                case SDL_KEYDOWN:
                    gApp->keyDown(event.key.keysym.sym);
                break;

                case SDL_KEYUP:
                    gApp->keyDown(event.key.keysym.sym);
                break;

                case SDL_MOUSEBUTTONDOWN:
                    {
                        mouseDown = true;

                        int mouseX = event.motion.x;
                        int mouseY = event.motion.y;

                        gApp->mouseDown(mouseX, mouseY);
                    }
                break;

                case SDL_MOUSEMOTION:
                    {
                        if( mouseDown )
                        {
                            int mouseX = event.motion.x;
                            int mouseY = event.motion.y;

                            gApp->mouseDragged(mouseX, mouseY);
                        }
                    }
                break;

                case SDL_MOUSEBUTTONUP:
                    {
                        mouseDown = false;

                        int mouseX = event.motion.x;
                        int mouseY = event.motion.y;

                        gApp->mouseUp(mouseX, mouseY);
                    }
                break;

                case SDL_WINDOWEVENT:
                    switch( event.window.event )
                    {
                        case SDL_WINDOWEVENT_SIZE_CHANGED:
                            gApp->resize(event.window.data1, event.window.data2);
                        break;
                    }
                break;


                case SDL_QUIT:
                    quitting = true;
                break;
            }
        }

        render();
        SDL_Delay(1);
    }

    SDL_DelEventWatch(watch, NULL);
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

