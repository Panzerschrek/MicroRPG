#ifndef MICRO_RPG_H
#define MICRO_RPG_H



#define MRPG_DEBUG

//platform defenition
#define MRPG_OS_GNU_LINUX
//#define MRPG_OS_WIN32
//platform defenition




#ifdef MRPG_OS_WIN32
#include <windows.h>
inline void usleep(int n ) { Sleep(n/1000); }
#else
#include <unistd.h>
#endif


#ifdef MRPG_DEBUG
#include <stdlib.h>
#include <stdio.h>
#endif


#endif//MICRO_RPG_H
