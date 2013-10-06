#ifndef MICRO_RPG_H
#define MICRO_RPG_H

#define MRPG_DEBUG


#ifdef MRPG_OS_WINDOWS
#include <windows.h>
inline void usleep(int n ) { Sleep(n/1000); }
#else
#include <unistd.h>
#endif

#ifdef MRPG_DEBUG
#include <stdio.h>
#endif

#include <stdlib.h>
#include <string.h>



#include <GL/gl.h>

#ifdef MRPG_OS_WINDOWS
#include "GL/wglext.h"
#else
//#include "GL/glxext.h"
#include <GL/glx.h>
#include <X11/X.h>
#include <X11/keysym.h>
#endif
#include "GL/glext.h"

#define MRPG_GL_VERSION 21


#endif//MICRO_RPG_H
