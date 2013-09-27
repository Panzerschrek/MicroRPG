#ifndef RENDERER_H
#define RENDERER_H


#include "player.h"
#include "level.h"

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


class Renderer
{
	public:
	Renderer( Level* l, Player* p );
	~Renderer(){}

	void Draw();

	private:
	Player* player;
	Level* level;


};

#endif//RENDERER_H
