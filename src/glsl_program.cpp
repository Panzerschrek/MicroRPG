#include "glsl_program.h"
#include "gl_functions.h"

GLSLProgram::GLSLProgram()
{
    attrib_count= uniform_count = 0;
}

void GLSLProgram::FindUniform( const char* uniform )
{
    uniforms[ uniform_count++] =
        glGetUniformLocation( program_id, uniform );
}

void GLSLProgram::SetAttribLocation( const char* attrib_name, unsigned int attrib )
{
    strcpy( attrib_names[ attrib_count ], attrib_name );
    attribs[ attrib_count ]= attrib;
    attrib_count++;
}


void GLSLProgram::Create( const char* vertex_shader, const char* fragment_shader )
{
    const char* str[2]= { vertex_shader, 0 };
    int len[2]= { strlen( vertex_shader ), 0 };

    v_shader= glCreateShader( GL_VERTEX_SHADER );
    glShaderSource( v_shader, 1, str, len);
    glCompileShader( v_shader );
#ifdef MRPG_DEBUG
    int compile_status;
    len[0]= 1024;
    char build_log[1024];

    glGetShaderiv( v_shader, GL_COMPILE_STATUS, &compile_status );
    if( !compile_status )
    {
        glGetShaderInfoLog( v_shader, 1023, len, build_log );
        printf( "vertex shader error:\n\n%s\nerrors:\n%s\n", vertex_shader, build_log );
    }
#endif

    str[0]= fragment_shader;
    len[0]= strlen( fragment_shader );

    f_shader= glCreateShader( GL_FRAGMENT_SHADER );
    glShaderSource( f_shader, 1, str, len);
    glCompileShader( f_shader );
    #ifdef MRPG_DEBUG
      glGetShaderiv( f_shader, GL_COMPILE_STATUS, &compile_status );
    if( !compile_status )
    {
        glGetShaderInfoLog( f_shader, 1023, len, build_log );
        printf( "fragment shader error:\n\n%s\nerrors:\n%s\n", fragment_shader, build_log );
    }
    #endif

    program_id= glCreateProgram();

    glAttachShader( program_id, v_shader );
    glAttachShader( program_id, f_shader );

    for( unsigned int i= 0; i< attrib_count; i++ )
        glBindAttribLocation( program_id, attribs[i], attrib_names[i] );

    glLinkProgram( program_id );

#ifdef MRPG_DEBUG
    glGetProgramiv( program_id, GL_LINK_STATUS, &compile_status );

    if( ! compile_status )
    {
        len[0]= 1024;
        glGetProgramInfoLog( program_id, 1023, len, build_log );
        printf( "shader link error:\n %s\n", build_log );
    }
#endif
}


void GLSLProgram::UniformI	( unsigned int uniform_id, int i )
{
    glUniform1i( uniforms[ uniform_id ], i );
}

void GLSLProgram::UniformMat4( unsigned int uniform_id, float* mat )
{
    glUniformMatrix4fv( uniforms[ uniform_id ], 1, GL_FALSE, mat );
}

void GLSLProgram::UniformVec3( unsigned int uniform_id, float* v )
{
    glUniform3f( uniforms[ uniform_id ], v[0], v[1], v[2] );
}

void GLSLProgram::UniformFloat(unsigned int uniform_id, float f )
{
    glUniform1f( uniforms[ uniform_id ], f );
}

