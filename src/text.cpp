#include "../other/font_data.c"
#include "text.h"


#define FONT_BITMAP_WIDTH 768
#define FONT_BITMAP_HEIGHT 18

void Text::CreateTexture()
{
	unsigned char* uncompressed_font= new unsigned char[ FONT_BITMAP_WIDTH * FONT_BITMAP_HEIGHT ];

	for( unsigned int i= 0; i< FONT_BITMAP_WIDTH * FONT_BITMAP_HEIGHT / 8; i++ )
		for( unsigned int j= 0; j< 8; j++ )
					uncompressed_font[ i*8 + j ]= ( ( font_data[i] & (1<<j) ) == 0 ) ? 0 : 255;



	glGenTextures( 1, &font_texture_id );

	glBindTexture( GL_TEXTURE_2D, font_texture_id );

	glTexImage2D( GL_TEXTURE_2D, 0, 1,
					 FONT_BITMAP_WIDTH, FONT_BITMAP_HEIGHT, 0,
					 	 GL_RED,  GL_UNSIGNED_BYTE, uncompressed_font );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );

	delete[] uncompressed_font;
	int err= glGetError();
	printf( "error gl %d\n", err );
}



//leter_ tc_x_left= ( letter_ascii - 32 ) / 768
void Text::Draw()
{
	glEnable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D, font_texture_id );


	glBegin( GL_QUADS );

	glTexCoord2f( 0.0f, 0.0f );
	glVertex2f( -1.0f, -0.2f );

	glTexCoord2f( 1.0f, 0.0f );
	glVertex2f( 1.0f, -0.2f );

	glTexCoord2f( 1.0f, 1.0f );
	glVertex2f( 1.0f, 0.2f );

	glTexCoord2f( 0.0f, 1.0f );
	glVertex2f( -1.0f, 0.2f );

	glEnd();
}

Text::Text()
{
	CreateTexture();
}
