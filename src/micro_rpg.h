#ifndef MICRO_RPG_H
#define MICRO_RPG_H

#define MRPG_DEBUG

//platform defenition
#define MRPG_OS_GNU_LINUX
//#define MRPG_OS_WIN32
//platform defenition

#ifdef MRPG_OS_WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif


#include <stdlib.h>
#include <stdio.h>


#endif//MICRO_RPG_H
