#ifndef MAIN_LOOP_H
#define MAIN_LOOP_H
#include "micro_rpg.h"
#include "renderer.h"
#include "player.h"
#include "level.h"


class MainLoop
{
public:
    MainLoop( Renderer* r, Level* l, Player* p );
    ~MainLoop() {}

    void Loop();


private:

	void InitOGL();
	void SetupOGLState();

	int screen_x, screen_y;


	Player* player;
	Renderer* renderer;
	Level* level;

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
