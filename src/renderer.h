#ifndef RENDERER_H
#define RENDERER_H


#include "player.h"
#include "level.h"
#include "micro_rpg.h"
#include "text.h"
#include "vertex_buffer.h"
#include "glsl_program.h"

#pragma pack( push, 1 )
struct MicrobeVertex
{
    float pos[3];
    unsigned char color[4];
};
#pragma pack(pop)


class Mesh
{
public:

    MicrobeVertex* vertices;
    unsigned short* indeces;
    unsigned int vertex_count, index_count;
    GLenum primitive_type;//quads/triangles/etc

    void Draw();
};


class Renderer
{
	public:
	Renderer( Level* l, Player* p );
	~Renderer(){}

	void Draw();

	private:

   // void DrawMicrobeBody( float x, float y );
    void DrawBackground();

    VertexBuffer microbes_vbo;
    GLSLProgram microbes_shader;
	Player* player;
	Level* level;

	Text text;
	GLuint background_texture;

	unsigned int screen_x, screen_y;

	Mesh part_meshes[64];


};

#endif//RENDERER_H
