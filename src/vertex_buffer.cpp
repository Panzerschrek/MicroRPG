#include "vertex_buffer.h"


VertexBuffer::VertexBuffer()
{
	index_vbo= vertex_vbo= 0xffffffff;
}


void VertexBuffer::VertexData( void* data, unsigned int data_size, unsigned int vertex_size )
{
	if( vertex_vbo == 0xffffffff )
		glGenBuffers( 1, &vertex_vbo );
	glBufferData( GL_ARRAY_BUFFER, data_size, data, GL_STATIC_DRAW );
}


void VertexBuffer::IndexData( void* data, unsigned int data_size, GLenum index_type )
{
	if( index_vbo == 0xfffffffff )
		glGenBuffers( 1, &vertex_vbo );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, data_size, data, GL_STATIC_DRAW );
}
