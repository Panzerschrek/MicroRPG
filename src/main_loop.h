#ifndef MAIN_LOOP_H
#define MAIN_LOOP_H
#include "micro_rpg.h"


#include <GL/gl.h>

#ifdef MRPG_OS_WIN32
#include "GL/wglext.h"
#else
//#include "GL/glxext.h"
#include <GL/glx.h>
#include <X11/X.h>
#include <X11/keysym.h>
#endif

#include "GL/glext.h"


class MainLoop
{
public:
    MainLoop();
    ~MainLoop() {}

    void Loop();


private:

	void InitOGL();
	void SetupOGLState();
	void Draw();

	int screen_x, screen_y;

#ifdef MRPG_OS_WIN32

	HWND hwnd;
	HDC hdc;
	HGLRC hrc;
	WNDCLASSEX window_class;

	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

#else
    XEvent     event;
    Display   *dpy;
    Window     win;

#endif

	static MainLoop* current_main_loop;
};


#endif//MAIN_LOOP_H
