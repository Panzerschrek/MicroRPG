#ifndef TEXT_H
#define TEXT_H

#include "micro_rpg.h"

#pragma pack( push, 1 )
struct TextVertex
{
	float pos[2];
	unsigned short tex_coord[2];
	unsigned char color[4];
};
#pragma pack (pop)


class Text
{
	public:

	Text();
	~Text(){}
	void AddText( unsigned int row, unsigned int colomn, const char* text );

	void Draw();


	private:

	void CreateTexture();

	TextVertex* vertices;
	unsigned int vertex_buffer_size;
	unsigned int vertex_buffer_pos;

	GLuint font_texture_id;

};
#endif//TEXT_H
