#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include "micro_rpg.h"

#include "gl_functions.h"

class VertexBuffer
{
	public:

	VertexBuffer();
	~VertexBuffer(){}
    static void EnableAttribs( int count );

	void VertexData( void* data, unsigned int data_size, unsigned int vertex_size );
	void IndexData( void* data, unsigned int data_size );
	void VertexAttrib( int attrib, unsigned int components, GLenum type, bool normalized, unsigned int shift );

	void VertexSubData( void* data, unsigned int data_size, unsigned int shift );
	void IndexSubData( void* data, unsigned int data_size, unsigned int shift );

	void Bind();

	private:

	unsigned int vertex_size;
	GLuint index_vbo, vertex_vbo;

    static bool vertex_attribs_enabled[8];
};


inline void VertexBuffer::Bind()
{
	glBindBuffer( GL_ARRAY_BUFFER, vertex_vbo );
	if( index_vbo != 0xffffffff )
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, index_vbo );
}

inline void VertexBuffer::VertexAttrib( int attrib, unsigned int components, GLenum type, bool normalized, unsigned int shift )
{
    glVertexAttribPointer( attrib, components, type, normalized, vertex_size, (void*) shift );
}

#endif//VERTEX_BUFFER_H
