#ifndef MAIN_LOOP_H
#define MAIN_LOOP_H
#include "micro_rpg.h"


#include <GL/glx.h>
#include <GL/gl.h>

#ifdef MRPG_OS_WIN32
#else
#include <X11/X.h>
#include <X11/keysym.h>
#endif

class MainLoop
{
public:
    MainLoop();
    ~MainLoop() {}

    void Loop();


private:

	int screen_x, screen_y;

#ifdef MRPG_OS_WIN32
#else
    XEvent               event;
    Display   *dpy;
    Window     win;

#endif
};


#endif//MAIN_LOOP_H
