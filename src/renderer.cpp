#include "renderer.h"
#include "shaders.h"
#include "math.h"
#include "microbe.h"

#define BODY_DEPTH -0.5f
#define SHELL_DEPTH -0.4f
#define PARTS_DEPTH -0.3f

Renderer::Renderer( Level* l, Player* p ):
level(l), player(p)
{
    microbes_vbo.VertexData( NULL, sizeof(MicrobeVertex) * 1024, sizeof(MicrobeVertex) );
    microbes_vbo.IndexData( NULL, 1024 * sizeof(short) );


    microbes_shader.SetAttribLocation( "v", 0 );
    microbes_shader.SetAttribLocation( "c", 1 );
    microbes_shader.Create( microbe_shader_v, microbe_shader_f );
    microbes_shader.FindUniform( "m" );//transform matrix, uniform No 0


    int v[4];
	glGetIntegerv( GL_VIEWPORT, v );
	screen_x= v[2];
	screen_y= v[3];
}

void Renderer::Draw()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    microbes_vbo.Bind();

    microbes_vbo.VertexAttrib( 0, 3, GL_FLOAT, false, 0 );//vertex coordinates
    microbes_vbo.VertexAttrib( 1, 4, GL_UNSIGNED_BYTE, true, sizeof(float)*3 );//color
    VertexBuffer::EnableAttribs(2);


    microbes_shader.Bind();

    for (int i=0; i<level->getLastMicrobeIndex(); ++i)
    {
        Microbe* microbe = level->getMicrobe(i);
        DrawMicrobeBody(microbe->X(), microbe->Y());
    }
    /*DrawMicrobeBody(0.0f,0.0f);
     DrawMicrobeBody(0.5f,0.5f);
      DrawMicrobeBody(-0.5f,-0.2f);*/

    unsigned char color[]= { 245, 240, 255, 128 };
    text.AddText( 0, 2, 2, color, "MicroRPG - a microbic 64k game" );
    text.AddText( 0, 3, 1, color, "By Panzerschrek && Mmaulwurff" );
    text.Draw();
}

void Renderer::DrawMicrobeBody(float x, float y)
{
    static unsigned short* ind= NULL;
    static MicrobeVertex* v= NULL;

    const unsigned int segment_count= 36;

    //generate microbe body mesh
    if( ind == NULL )
    {
        //vertex count= n + 1
        //index count = n*3+
        v =new  MicrobeVertex[ segment_count + 1 ];
        ind= new unsigned short[ segment_count * 3 ];

        static const unsigned char color[]= { 255, 200,190, 0 };

        v[0].pos[0]= 0.0f;
        v[0].pos[1]= 0.0f;
        v[0].pos[2]= BODY_DEPTH;
        *((int*) v[0].color )= *((int*)color );//4 bytes per 1 command

        float a= 0.0f;
        float da= 3.1415926535f * 2.0f / float(segment_count);
        for( unsigned int i= 1; i< segment_count + 1; i++, a+= da )
        {
            v[i].pos[0]= cos(a);
            v[i].pos[1]= sin(a);
            v[i].pos[2]= BODY_DEPTH;

            *((int*) v[i].color )= *((int*)color );//4 bytes per 1 command
            //v[i].color[0]= color[0];v[i].color[1]= color[1];
            //v[i].color[2]= color[2];v[i].color[3]= color[3];
        }

        for( unsigned int i= 1, j=0; i< segment_count+1; i++, j+=3 )
        {
            ind[j]= 0;
            ind[j + 1]= i;
            ind[j + 2]= i + 1;
        }
        ind[ segment_count * 3 - 1 ]= 1;
    }


	float mat[3][16];

	Mat4Identity( mat[0] );//scale matrix
	mat[0][0]= float( screen_y ) / float( screen_x ) * 0.125f;
	mat[0][5]= 0.125f;

	Mat4Identity( mat[1] );//translate matirx
	mat[1][12]= -x;
	mat[1][13]= -y;
	Mat4Mul( mat[0], mat[1], mat[2] );


    microbes_shader.UniformMat4( 0, mat[2] );

    microbes_vbo.VertexSubData( v, (segment_count + 1)*sizeof(MicrobeVertex), 0 );
    microbes_vbo.IndexSubData( ind, segment_count*3 * sizeof(short), 0 );


    glDrawElements( GL_TRIANGLES, segment_count*3, GL_UNSIGNED_SHORT, NULL );

}
