#include "renderer.h"
#include "shaders.h"
#include "math.h"
#include "background.h"
#include "microbe.h"

#define BODY_DEPTH 0.9f
#define SHELL_DEPTH 0.8f
#define PARTS_DEPTH 0.7f


void Mesh::Draw()
{
    if( index_count == 0 )//non indexed geometry
        glDrawArrays( primitive_type, 0, vertex_count );
    else
        glDrawElements( primitive_type, index_count, GL_UNSIGNED_SHORT, NULL );
}

Renderer::Renderer( Level* l, Player* p ):
level(l), player(p)
{

	int v[4];
	glGetIntegerv( GL_VIEWPORT, v );
	screen_x= v[2];
	screen_y= v[3];


    microbes_vbo.VertexData( NULL, sizeof(MicrobeVertex) * 1024, sizeof(MicrobeVertex) );
    microbes_vbo.IndexData( NULL, 1024 * sizeof(short) );

    microbes_shader.SetAttribLocation( "v", 0 );
    microbes_shader.SetAttribLocation( "c", 1 );
    microbes_shader.Create( microbe_shader_v, microbe_shader_f );
    microbes_shader.FindUniform( "m" );//transform matrix, uniform No 0


	glGenTextures( 1, &background_texture );
	glBindTexture( GL_TEXTURE_2D, background_texture );

	unsigned char* bg_data= GenBackground( screen_x, screen_y );

	glTexParameteri( GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE );
	glTexImage2D( GL_TEXTURE_2D, 0, 1,
					 screen_x, screen_y, 0,
					 	 GL_RED,  GL_UNSIGNED_BYTE, bg_data );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );


}

void Renderer::DrawBackground()
{
	glBindTexture( GL_TEXTURE_2D, background_texture );
	glEnable( GL_TEXTURE_2D );
	glUseProgram(0);

	glColor3f( 0.7f, 0.8f, 0.9f );

	glBegin( GL_QUADS );
	glTexCoord2f( 0.0f, 0.0f );
	glVertex2f( -1.0f, -1.0f );

	glTexCoord2f( 1.0f, 0.0f );
	glVertex2f( 1.0f, -1.0f );

	glTexCoord2f( 1.0f, 1.0f );
	glVertex2f( 1.0f, 1.0f );

	glTexCoord2f( 0.0f, 1.0f );
	glVertex2f( -1.0f, 1.0f );
	glEnd();
}

void Renderer::Draw()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    DrawBackground();

    microbes_vbo.Bind();

    microbes_vbo.VertexAttrib( 0, 3, GL_FLOAT, false, 0 );//vertex coordinates
    microbes_vbo.VertexAttrib( 1, 4, GL_UNSIGNED_BYTE, true, sizeof(float)*3 );//color
    VertexBuffer::EnableAttribs(2);


    microbes_shader.Bind();

    //temp code
    //srand(0);
    /*for( int i= 0; i< 50; i++ ) {
        float x, y;
        x= 2.0f*float(rand())/float(RAND_MAX) - 1.0f;
        y= 2.0f*float(rand())/float(RAND_MAX) - 1.0f;
        DrawMicrobeBody(x,y);
        DrawCellShell(x,y);
    }*/

    for (int i=0; i<level->getLastMicrobeIndex(); ++i)
    {
        Microbe* microbe = level->getMicrobe(i);
        DrawMicrobeBody(microbe->X(), microbe->Y());
        DrawCellShell(microbe->X(), microbe->Y());
    }
    /*DrawMicrobeBody(0.0f,0.0f);
     DrawMicrobeBody(0.5f,0.5f);
      DrawMicrobeBody(-0.5f,-0.2f);*/

    unsigned char color[]= { 255, 255, 255, 32 };
    text.AddText( 0, 2, 2, color, "MicroRPG - a microbic 64k game" );
    text.AddText( 0, 3, 1, color, "By Panzerschrek && Mmaulwurff" );
    text.Draw();
}

void Renderer::DrawMicrobeBody(float x, float y)
{
    static unsigned short* ind= NULL;
    static MicrobeVertex* v= NULL;

    const unsigned int segment_count= 16;

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



void Renderer::DrawCellShell(float x, float y)
{
    static unsigned short* ind= NULL;
    static MicrobeVertex* v= NULL;

    const unsigned int segment_count= 16;

    //generate shell mesh
    if( ind == NULL )
    {
        //vertex count= n * 2
        //quads index count = n * 4
        v =new  MicrobeVertex[ segment_count *2 ];
        ind= new unsigned short[ segment_count * 4 ];

        static const unsigned char color[]= { 255/2, 200/2,190/2, 0 };

        float a= 0.0f;
        float da= 3.1415926535f * 2.0f / float(segment_count);
        for( unsigned int i= 0; i< segment_count * 2; i+=2, a+= da )
        {
            v[i].pos[0]= cos(a);
            v[i].pos[1]= sin(a);
            v[i+1].pos[0]= v[i].pos[0] * 1.05f;
            v[i+1].pos[1]= v[i].pos[1] * 1.05f;
            v[i].pos[2]= v[i+1].pos[2]= SHELL_DEPTH;

            *((int*) v[i].color )= *((int*)color );//4 bytes per 1 command
            *((int*) v[i+1].color )= *((int*)color );
            //v[i].color[0]= color[0];v[i].color[1]= color[1];
            //v[i].color[2]= color[2];v[i].color[3]= color[3];
        }

        for( unsigned int i= 0, j=0; i< segment_count * 4; i+=4, j+=2 )
        {
            ind[ i ]= j;
            ind[ i + 1 ] = j + 1; 
            ind[ i + 2 ] = j + 3;
            ind[ i + 3 ] = j + 2;
        }
        ind[ segment_count * 4 - 2 ]= 1;
        ind [ segment_count * 4 - 1 ]= 0;
       
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

    microbes_vbo.VertexSubData( v, segment_count * 2 * sizeof(MicrobeVertex), 0 );
    microbes_vbo.IndexSubData( ind, segment_count * 4 * sizeof(short), 0 );


    glDrawElements( GL_QUADS, segment_count * 4, GL_UNSIGNED_SHORT, NULL );

}
