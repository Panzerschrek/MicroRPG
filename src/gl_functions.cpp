#include "gl_functions.h"

PFNGLVERTEXATTRIBPOINTERPROC	glVertexAttribPointer= NULL;
PFNGLGENBUFFERSPROC			glGenBuffers= NULL;
PFNGLBINDBUFFERPROC			glBindBuffer= NULL;
PFNGLBUFFERDATAPROC			glBufferData= NULL;


#define MACRO_TO_STR(X) #X
#define MACRO_VALUE_TO_STR(X) MACRO_TO_STR(X)

#define CHECK_FUNC_STATUS(x)\
if( x == NULL )\
{\
    printf( "error, function \"%s\"= %u\n", MACRO_TO_STR(x), (GLuint)x );\
}

#ifdef MRPG_OS_WIN32
#define GetProcFunc wglGetProcAddress
#else
#define GetProcFunc glXGetProcAddressARB
#endif

#define GET_PROC_ADDRESS(x)\
GetProcFunc( (const unsigned char*)MACRO_TO_STR(x));


void GetGLFunctions()
{
	glVertexAttribPointer= ( PFNGLVERTEXATTRIBPOINTERPROC ) GET_PROC_ADDRESS( glVertexAttribPointer );

	glGenBuffers= (PFNGLGENBUFFERSPROC) GET_PROC_ADDRESS( glGenBuffers );
	glBindBuffer= (PFNGLBINDBUFFERPROC) GET_PROC_ADDRESS( glBindBuffer );
	glBufferData= (PFNGLBUFFERDATAPROC)	GET_PROC_ADDRESS( glBufferData );
}
