#include "vertex_buffer.h"


bool VertexBuffer::vertex_attribs_enabled[8]= {false,false,false,false,false,false,false,false};

void VertexBuffer::EnableAttribs( int count )
{
    int i;
for( i= 0; i< count; i++ )
         glEnableVertexAttribArray(i);
    for( i= count; i<8; i++ )
         glDisableVertexAttribArray(i);
           
    
}

VertexBuffer::VertexBuffer()
{
	index_vbo= vertex_vbo= 0xffffffff;
}


void VertexBuffer::VertexData( void* data, unsigned int data_size, unsigned int vertex_size )
{
	if( vertex_vbo == 0xffffffff )
		glGenBuffers( 1, &vertex_vbo );
    glBindBuffer( GL_ARRAY_BUFFER, vertex_vbo );
	glBufferData( GL_ARRAY_BUFFER, data_size, data, GL_STATIC_DRAW );

    this->vertex_size= vertex_size;
}


void VertexBuffer::IndexData( void* data, unsigned int data_size )
{
	if( index_vbo == 0xfffffffff )
		glGenBuffers( 1, &index_vbo );

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, index_vbo );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, data_size, data, GL_STATIC_DRAW );
}


void VertexBuffer::VertexSubData( void* data, unsigned int data_size, unsigned int shift )
{
    glBindBuffer( GL_ARRAY_BUFFER, vertex_vbo );
    glBufferSubData( GL_ARRAY_BUFFER, shift, data_size, data );
}

void VertexBuffer::IndexSubData( void* data, unsigned int data_size, unsigned int shift )
{
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, index_vbo );
    glBufferSubData( GL_ELEMENT_ARRAY_BUFFER, shift, data_size, data );
}
