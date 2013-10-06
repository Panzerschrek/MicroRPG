#include <time.h>

#include "renderer.h"
#include "shaders.h"
#include "background.h"
#include "microbe.h"
#include "math.h"

#include "part_generation.h"


void Mesh::Draw()
{
    if( index_count == 0 )//non indexed geometry
        glDrawArrays( primitive_type, 0, vertex_count );
    else
        glDrawElements( primitive_type, index_count, GL_UNSIGNED_SHORT, NULL );
}

Renderer::Renderer( Level* l, Player* p ):
    level(l), player(p), scene_scale(1.0f)
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


    // GenRoundBody( &part_meshes[ PART_ROUND_BODY ] );
    // GenDefaultShell( &part_meshes[ PART_DEFAULT_SHELL ] );
    //GenDefaultNucleus( &part_meshes[ PART_DEFAULT_NUCLEUS ] );
    //GenFlagellum( &part_meshes[ PART_FLAGELLUM ] );
    for( int i= 0; i< PART_COUNT; i++ )
        generation_func_table[i]( &part_meshes[i] );


}

void Renderer::DrawBackground()
{
    glBindTexture( GL_TEXTURE_2D, background_texture );
    glEnable( GL_TEXTURE_2D );
    glUseProgram(0);

    glColor3f( 0.7f, 0.8f, 0.9f );

    glBegin( GL_QUADS );
    glTexCoord2f( 0.0f, 0.0f );
    glVertex3f( -1.0f, -1.0f, 1.0f );

    glTexCoord2f( 1.0f, 0.0f );
    glVertex3f( 1.0f, -1.0f, 1.0f );

    glTexCoord2f( 1.0f, 1.0f );
    glVertex3f( 1.0f, 1.0f, 1.0f );

    glTexCoord2f( 0.0f, 1.0f );
    glVertex3f( -1.0f, 1.0f, 1.0f );
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



    for (int i=0; i<level->getLastMicrobeIndex(); ++i)
    {
        Microbe* microbe = level->getMicrobe(i);

        float mat[3][16];

        Mat4Identity( mat[0] );//scale matrix
        mat[0][0]= float( screen_y ) / float( screen_x ) * scene_scale;
        mat[0][5]= scene_scale;

        Mat4Identity( mat[1] );//translate matirx
        mat[1][12]= microbe->X();
        mat[1][13]= microbe->Y();
        //Mat4Mul( mat[0], mat[1], mat[2] );

        Mat4Identity( mat[2] );//rotate matrix
        mat[2][0]= cos( microbe->Dir() );
        mat[2][1]= sin( microbe->Dir() );
        mat[2][4]= -mat[2][1];
        mat[2][5]= mat[2][0];

		//rotate * translate * scale
        Mat4Mul( mat[2], mat[1] );
        Mat4Mul( mat[2], mat[0] );


        microbes_shader.UniformMat4( 0, mat[2] );

        for( int j= 0; j< PART_COUNT; j++ )
        {
            if( generation_func_animation_table[j] )
                generation_func_table[j]( &part_meshes[j] );

            microbes_vbo.VertexSubData( part_meshes[j].vertices,
                                        part_meshes[j].vertex_count * sizeof(MicrobeVertex), 0 );
            if(  part_meshes[j].indeces != NULL )
                microbes_vbo.IndexSubData( part_meshes[j].indeces,
                                           part_meshes[j].index_count * sizeof(short), 0 );
            part_meshes[j].Draw();
        }
    }


    unsigned char color[]= { 255, 255, 255, 32 };
    text.AddText( 0, 2, 2, color, "MicroRPG - a microbic 64k game" );
    text.AddText( 0, 3, 1, color, "By Panzerschrek && Mmaulwurff" );
    text.Draw();
}
