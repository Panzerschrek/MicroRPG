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

    Mesh();
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

	void SetSceneScale( float s );
	void ZoomIn();
	void ZoomOut();

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
	float scene_scale;

	Mesh part_meshes[64];


};

inline void Renderer::SetSceneScale( float s )
{
	scene_scale= s;
}

inline void Renderer::ZoomIn()
{
	if( scene_scale <= 1.0f )
		scene_scale*= 2.0f;
}

inline void Renderer::ZoomOut()
{
	if( scene_scale>= 0.0625f )
		scene_scale*= 0.5f;
}


#endif//RENDERER_H
