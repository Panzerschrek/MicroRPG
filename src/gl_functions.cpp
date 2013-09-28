#include "gl_functions.h"

PFNGLVERTEXATTRIBPOINTERPROC	glVertexAttribPointer= NULL;
PFNGLGENBUFFERSPROC			glGenBuffers= NULL;
PFNGLBINDBUFFERPROC			glBindBuffer= NULL;
PFNGLBUFFERDATAPROC			glBufferData= NULL;




PFNGLUNIFORM1IPROC			glUniform1i= NULL;
PFNGLUNIFORMMATRIX4FVPROC	glUniformMatrix4fv= NULL;
PFNGLUNIFORMMATRIX3FVPROC	glUniformMatrix3fv= NULL;
PFNGLUNIFORM3FPROC			glUniform3f= NULL;
PFNGLUNIFORM1FPROC          glUniform1f= NULL;

PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation= NULL;
PFNGLBINDATTRIBLOCATIONPROC	glBindAttribLocation= NULL;
PFNGLCREATEPROGRAMPROC		glCreateProgram= NULL;
PFNGLATTACHSHADERPROC		glAttachShader= NULL;
PFNGLLINKPROGRAMPROC		glLinkProgram= NULL;
PFNGLUSEPROGRAMPROC			glUseProgram= NULL;
PFNGLGETPROGRAMIVPROC		glGetProgramiv= NULL;
PFNGLGETPROGRAMINFOLOGPROC	glGetProgramInfoLog= NULL;

PFNGLCREATESHADERPROC		glCreateShader= NULL;
PFNGLSHADERSOURCEPROC		glShaderSource= NULL;
PFNGLCOMPILESHADERPROC		glCompileShader= NULL;
PFNGLGETSHADERIVPROC		glGetShaderiv= NULL;
PFNGLGETSHADERINFOLOGPROC	glGetShaderInfoLog= NULL;

#define MACRO_TO_STR(X) #X
#define MACRO_VALUE_TO_STR(X) MACRO_TO_STR(X)

#define CHECK_FUNC_STATUS(x)\
if( x == NULL )\
{\
    printf( "error, function \"%s\"= %u\n", MACRO_TO_STR(x), (GLuint)x );\
}

/*#ifdef MRPG_OS_WIN32
#define GetProcFunc wglGetProcAddress
#else
#define GetProcFunc glXGetProcAddressARB
#endif

#define GET_PROC_ADDRESS(x)\
GetProcFunc( (const unsigned char*)MACRO_TO_STR(x) )*/


#ifdef MRPG_OS_WINDOWS

#define GET_PROC_ADDRESS(x)\
wglGetProcAddress( MACRO_TO_STR(x) )

#else
#define GET_PROC_ADDRESS(x)\
glXGetProcAddressARB( (const unsigned char*)MACRO_TO_STR(x) )

#endif


void GetGLFunctions()
{
    glVertexAttribPointer= ( PFNGLVERTEXATTRIBPOINTERPROC ) GET_PROC_ADDRESS( glVertexAttribPointer );

    glGenBuffers= (PFNGLGENBUFFERSPROC) GET_PROC_ADDRESS( glGenBuffers );
    glBindBuffer= (PFNGLBINDBUFFERPROC) GET_PROC_ADDRESS( glBindBuffer );
    glBufferData= (PFNGLBUFFERDATAPROC)	GET_PROC_ADDRESS( glBufferData );

    glUniform1i= (PFNGLUNIFORM1IPROC) GET_PROC_ADDRESS(glUniform1i);
    glUniformMatrix4fv= (PFNGLUNIFORMMATRIX4FVPROC)	GET_PROC_ADDRESS(glUniformMatrix4fv);
    glUniformMatrix3fv= (PFNGLUNIFORMMATRIX3FVPROC)	GET_PROC_ADDRESS(glUniformMatrix3fv);
    glUniform3f= (PFNGLUNIFORM3FPROC) GET_PROC_ADDRESS(glUniform3f);
    glUniform1f= (PFNGLUNIFORM1FPROC) GET_PROC_ADDRESS(glUniform1f);

    glGetUniformLocation= (PFNGLGETUNIFORMLOCATIONPROC) GET_PROC_ADDRESS(glGetUniformLocation);
    glBindAttribLocation= (PFNGLBINDATTRIBLOCATIONPROC) GET_PROC_ADDRESS(glBindAttribLocation);
    glCreateProgram= (PFNGLCREATEPROGRAMPROC) GET_PROC_ADDRESS(glCreateProgram);
    glAttachShader= (PFNGLATTACHSHADERPROC)	GET_PROC_ADDRESS(glAttachShader);
    glLinkProgram= (PFNGLLINKPROGRAMPROC)GET_PROC_ADDRESS(glLinkProgram);
    glUseProgram= (PFNGLUSEPROGRAMPROC)	GET_PROC_ADDRESS(glUseProgram);
    glGetProgramiv= (PFNGLGETPROGRAMIVPROC)		GET_PROC_ADDRESS(glGetProgramiv);
	glGetProgramInfoLog= (PFNGLGETPROGRAMINFOLOGPROC)	GET_PROC_ADDRESS(glGetProgramInfoLog);

    glCreateShader= (PFNGLCREATESHADERPROC)GET_PROC_ADDRESS(glCreateShader);
    glShaderSource= (PFNGLSHADERSOURCEPROC)	GET_PROC_ADDRESS(glShaderSource);
    glCompileShader= (PFNGLCOMPILESHADERPROC)GET_PROC_ADDRESS(glCompileShader);
    glGetShaderiv= (PFNGLGETSHADERIVPROC)		GET_PROC_ADDRESS(glGetShaderiv);
	glGetShaderInfoLog= (PFNGLGETSHADERINFOLOGPROC)	GET_PROC_ADDRESS(glGetShaderInfoLog);
}
