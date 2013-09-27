#ifndef TEXT_H
#define TEXT_H

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

	void Text();
	void Text(){}
	void AddText( unsigned int row, unsigned int colomn, const char* text );

	void Draw();

	Text();
	~Text(){}

	private:

	TextVertex* vertices;
	unsigned int vertex_buffer_size;
	unsigned int vertex_buffer_pos;

	GLUnit text_texture_id;

};
#endif//TEXT_H
