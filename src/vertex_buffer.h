#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include "micro_rpg.h"

#include "gl_functions.h"

class VertexBuffer
{
	public:

	VertexBuffer();
	~VertexBuffer(){}

	void VertexData( void* data, unsigned int data_size, unsigned int vertex_size );
	void IndexData( void* data, unsigned int data_size, GLenum index_type );
	void VertexAttrib( int attrib, unsigned int components, bool normalise, unsigned int shift );

	void VertexSubData( void* data, unsigned int data_size, unsigned int shift );
	void IndexSubData( void* data, unsigned int data_size, unsigned int shift );

	void Bind();

	private:

	unsigned int vertex_size;
	GLuint index_vbo, vertex_vbo;
};


inline void VertexBuffer::Bind()
{
	glBindBuffer( GL_ARRAY_BUFFER, vertex_vbo );
	if( index_vbo != 0xffffffff )
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, index_vbo );
}
#endif//VERTEX_BUFFER_H