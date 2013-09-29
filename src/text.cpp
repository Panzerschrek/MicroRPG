#include "../other/font_data.c"
#include "text.h"


#define FONT_BITMAP_WIDTH 768
#define FONT_BITMAP_HEIGHT 18

#define LETTER_WIDTH 8
#define LETTER_HEIGHT 18

void Text::CreateTexture()
{
	unsigned char* uncompressed_font= new unsigned char[ FONT_BITMAP_WIDTH * FONT_BITMAP_HEIGHT ];

    static unsigned char bits[]= { 128, 64, 32, 16, 8, 4, 2, 1 };
	for( unsigned int i= 0; i< FONT_BITMAP_WIDTH * FONT_BITMAP_HEIGHT / 8; i++ )
		for( unsigned int j= 0; j< 8; j++ )
					uncompressed_font[ i*8 + j ]= ( ( font_data[i] & bits[j] ) == 0 ) ? 0 : 255;



	glGenTextures( 1, &font_texture_id );

	glBindTexture( GL_TEXTURE_2D, font_texture_id );

	glTexParameteri( GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE );
	glTexImage2D( GL_TEXTURE_2D, 0, 1,
					 FONT_BITMAP_WIDTH, FONT_BITMAP_HEIGHT, 0,
					 	 GL_RED,  GL_UNSIGNED_BYTE, uncompressed_font );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR );

	delete[] uncompressed_font;
}



void Text::AddText( unsigned int colomn, unsigned int row, unsigned int size, const unsigned char* color, const char* text )
{
	const char* str= text;

	float x, x0, y;
	float dx, dy;

	x0= x=  2.0f * float( colomn * LETTER_WIDTH ) / screen_x - 1.0f;
	y=  -2.0f * float( (row + 1) * LETTER_HEIGHT ) / screen_y + 1.0f;

	dx= 2.0f * float( LETTER_WIDTH * size ) / screen_x;
	dy= 2.0f * float( LETTER_HEIGHT * size ) / screen_y;


	TextVertex* v= vertices + vertex_buffer_pos;
	while( *str != 0 )
	{

        if( *str == '\n' )
        {
            x= x0;
            y-=dy;
            str++;
            continue;
        }
		v[0].pos[0]= x;
		v[0].pos[1]= y;
		v[0].tex_coord[0]= *str - 32;
		v[0].tex_coord[1]= 0;

		v[1].pos[0]= x;
		v[1].pos[1]= y + dy;
		v[1].tex_coord[0]= *str - 32;
		v[1].tex_coord[1]= 1;

		v[2].pos[0]= x + dx;
		v[2].pos[1]= y + dy;
		v[2].tex_coord[0]= *str - 32 + 1;
		v[2].tex_coord[1]= 1;

		v[3].pos[0]= x + dx;
		v[3].pos[1]= y;
		v[3].tex_coord[0]= *str - 32 + 1;
		v[3].tex_coord[1]= 0;

        for( unsigned int i= 0; i< 4; i++ )
             *((int*)v[i].color)= *((int*)color);//copy 4 bytes per one asm command

		x+= dx;
		v+= 4;
		str++;
	}
	vertex_buffer_pos= v - vertices;
}

void Text::Draw()
{

	glBindTexture( GL_TEXTURE_2D, font_texture_id );

    text_vbo.VertexSubData( vertices, vertex_buffer_pos * sizeof(TextVertex), 0 );
    text_vbo.VertexAttrib( 0, 2, GL_FLOAT, false, 0 );//vertex coordinates
    text_vbo.VertexAttrib( 1, 2, GL_UNSIGNED_SHORT, false, sizeof(float)*2 );//texture coordinates
    text_vbo.VertexAttrib( 2, 4, GL_UNSIGNED_BYTE, true, sizeof(float)*2 + 2*sizeof(short) );//color
    VertexBuffer::EnableAttribs(3);

    text_shader.Bind();
    text_shader.UniformInt( 0, 0 );//texture - unit 0

    glDrawArrays( GL_QUADS, 0, vertex_buffer_pos );

    vertex_buffer_pos= 0;
}


Text::Text():
vertex_buffer_pos(0)
{
	CreateTexture();

	vertices= new  TextVertex[ MRPG_MAX_TEXT_BUFFER_SIZE * 4 ];

	int v[4];
	glGetIntegerv( GL_VIEWPORT, v );
	screen_x= float( v[2] );
	screen_y= float( v[3] );

    text_vbo.VertexData( NULL, MRPG_MAX_TEXT_BUFFER_SIZE * 4 * sizeof(TextVertex),
                                    sizeof(TextVertex) );


    text_shader.SetAttribLocation( "v", 0 );
    text_shader.SetAttribLocation( "tc", 1 );
    text_shader.SetAttribLocation( "c", 2 );
	text_shader.Create( text_shader_v, text_shader_f );
    text_shader.FindUniform( "tex" );
}
