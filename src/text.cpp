#include "../other/font_data.c"
#include "text.h"


#define FONT_BITMAP_WIDTH 768
#define FONT_BITMAP_HEIGHT 18

#define LETTER_WIDTH 8
#define LETTER_HEIGHT 18

void Text::CreateTexture()
{
	unsigned char* uncompressed_font= new unsigned char[ FONT_BITMAP_WIDTH * FONT_BITMAP_HEIGHT ];

	for( unsigned int i= 0; i< FONT_BITMAP_WIDTH * FONT_BITMAP_HEIGHT / 8; i++ )
		for( unsigned int j= 0; j< 8; j++ )
					uncompressed_font[ i*8 + j ]= ( ( font_data[i] & (1<<(8-j)) ) == 0 ) ? 0 : 255;



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



void Text::AddText( unsigned int row, unsigned int colomn, unsigned int size, const char* text )
{
	const char* str= text;

	float x, y;
	float dx, dy;

	x=  2.0f * float( colomn * LETTER_WIDTH ) / screen_x - 1.0f;
	y=  -2.0f * float( (row + 1) * LETTER_HEIGHT ) / screen_y + 1.0f;

	dx= 2.0f * float( LETTER_WIDTH ) / screen_x;
	dy= 2.0f * float( LETTER_HEIGHT ) / screen_y;


	TextVertex* v= vertices + vertex_buffer_pos;
	while( *str != 0 )
	{

		vertices[0].pos[0]= x;
		vertices[0].pos[1]= y;
		vertices[0].tex_coord[0]= *str - 32;
		vertices[0].tex_coord[1]= 0;

		vertices[1].pos[0]= x;
		vertices[1].pos[1]= y + dy;
		vertices[1].tex_coord[0]= *str - 32;
		vertices[1].tex_coord[1]= 1;

		vertices[2].pos[0]= x + dx;
		vertices[2].pos[1]= y + dy;
		vertices[2].tex_coord[0]= *str - 32 + 1;
		vertices[2].tex_coord[1]= 1;

		vertices[3].pos[0]= x + dx;
		vertices[3].pos[1]= y;
		vertices[3].tex_coord[0]= *str - 32 + 1;
		vertices[3].tex_coord[1]= 0;

		x+= dx;
		v+= 4;
		str++;
	}
	vertex_buffer_pos= v - vertices;
}

void Text::Draw()
{

	glEnable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D, font_texture_id );

    glColor3ub( 255, 255, 127 );

	glBegin( GL_QUADS );

	glTexCoord2f( 0.0f, 0.0f );
	glVertex2f( -1.0f, -0.03f );

	glTexCoord2f( 1.0f, 0.0f );
	glVertex2f( 1.0f, -0.03f );

	glTexCoord2f( 1.0f, 1.0f );
	glVertex2f( 1.0f, 0.03f );

	glTexCoord2f( 0.0f, 1.0f );
	glVertex2f( -1.0f, 0.03f );

	glEnd();

    glDisable( GL_TEXTURE_2D );
}

Text::Text()
{
	CreateTexture();

	vertices= new  TextVertex[ MRPG_MAX_TEXT_BUFFER_SIZE * 4 ];

	int v[4];
	glGetIntegerv( GL_VIEWPORT, v );
	screen_x= float( v[2] );
	screen_y= float( v[3] );

    text_vbo.VertexData( NULL, MRPG_MAX_TEXT_BUFFER_SIZE * 4 * sizeof(TextVertex),
                                    sizeof(TextVertex) );

	text_shader.Create( text_shader_v, text_shader_f );
}
