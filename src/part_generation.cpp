#include "renderer.h"
#include "math.h"
#include "time.h"


#define BODY_DEPTH 0.9f
#define SHELL_DEPTH 0.7f
#define PARTS_DEPTH 0.8f

void GenRoundBody( Mesh* m )
{
    const unsigned int segment_count= 16;
    MicrobeVertex* v= new  MicrobeVertex[ segment_count + 2 ];


    static const unsigned char color[]= { 255, 200,190, 0 };

    v[0].pos[0]= 0.0f;
    v[0].pos[1]= 0.0f;
    v[0].pos[2]= BODY_DEPTH;
    *((int*) v[0].color )= *((int*)color );//4 bytes per 1 command

    float a= 0.0f;
    float da= MRPG_PI * 2.0f / float(segment_count);
    for( unsigned int i= 1; i< segment_count + 2; i++, a+= da )
    {
        v[i].pos[0]= cos(a);
        v[i].pos[1]= sin(a);
        v[i].pos[2]= BODY_DEPTH;

        *((int*) v[i].color )= *((int*)color );//4 bytes per 1 command
        //v[i].color[0]= color[0];v[i].color[1]= color[1];
        //v[i].color[2]= color[2];v[i].color[3]= color[3];
    }

    m->indeces= 0;
    m->vertices= v;
    m->primitive_type= GL_TRIANGLE_FAN;
    m->vertex_count= segment_count + 2;
    m->index_count= 0;
}


void GenDefaultNucleus( Mesh* m )
{
    const unsigned int segment_count= 8;
    MicrobeVertex* v= new  MicrobeVertex[ segment_count + 2 ];


    static const unsigned char color[]= { 230, 230,190, 0 };

    v[0].pos[0]= 0.0f;
    v[0].pos[1]= 0.0f;
    v[0].pos[2]= PARTS_DEPTH;
    *((int*) v[0].color )= *((int*)color );//4 bytes per 1 command

    float a= 0.0f;
    float da= MRPG_PI * 2.0f / float(segment_count);
    for( unsigned int i= 1; i< segment_count + 2; i++, a+= da )
    {
        v[i].pos[0]= 0.15f * cos(a);
        v[i].pos[1]= 0.15f * sin(a);
        v[i].pos[2]= PARTS_DEPTH;

        *((int*) v[i].color )= *((int*)color );//4 bytes per 1 command
        //v[i].color[0]= color[0];v[i].color[1]= color[1];
        //v[i].color[2]= color[2];v[i].color[3]= color[3];
    }

    m->indeces= 0;
    m->vertices= v;
    m->primitive_type= GL_TRIANGLE_FAN;
    m->vertex_count= segment_count + 2;
    m->index_count= 0;
}


void GenDefaultShell( Mesh* m )
{
    const unsigned int segment_count= 16;

    //vertex count= n * 2
    //quads index count = n * 4
    MicrobeVertex* v =new  MicrobeVertex[ segment_count *2 ];
    unsigned short* ind= new unsigned short[ segment_count * 4 ];

    static const unsigned char color[]= { 255/2, 200/2,190/2, 0 };

    float a= 0.0f;
    float da= MRPG_PI * 2.0f / float(segment_count);
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
    ind[ segment_count * 4 - 1 ]= 0;


    m->indeces= ind;
    m->vertices= v;
    m->primitive_type= GL_QUADS;
    m->vertex_count= segment_count * 2;
    m->index_count= segment_count * 4;


}


void GenFlagellum( Mesh* m )
{
    const unsigned int segment_count= 16;


    MicrobeVertex* v;
    unsigned short* ind;

    if( m->vertices != NULL )
    {
        v= m->vertices;
        ind= m->indeces;
    }
    else
    {
        v= new  MicrobeVertex[ segment_count *2 + 2 ];
        ind=  new unsigned short[ segment_count * 4 ];
    }

    static const unsigned char color[]= { 32, 32,32, 0 };

    float a= 2.0f * MRPG_PI * float( clock() ) / float( CLOCKS_PER_SEC );
    float da= 6.0f * MRPG_PI / float( segment_count );
    float y= -1.0f;
    float dy= -2.0f / float( segment_count );
    float width= 0.15f;
    float d_w= width / float( segment_count +1 );
    float amplitude= 0.0625f;
    for( unsigned int i= 0; i< segment_count *2 + 2; i+=2, a+= da, y+= dy, width-= d_w )
    {
        v[i].pos[0]= amplitude * sin(a) -0.5f * width;
        v[i+1].pos[0]= v[i].pos[0] + width;

        v[i].pos[1]= v[i+1].pos[1]= y;

        v[i].pos[2]= v[i+1].pos[2]= PARTS_DEPTH;

        *((int*) v[i].color )= *((int*)color );//4 bytes per 1 command
        *((int*) v[i+1].color )= *((int*)color );
    }

    for( unsigned int i= 0, j=0; i< segment_count * 4; i+=4, j+=2 )
    {
        ind[ i ]= j;
        ind[ i + 1 ] = j + 1;
        ind[ i + 2 ] = j + 3;
        ind[ i + 3 ] = j + 2;
    }

    if( m->vertices == NULL )
    {
        m->indeces= ind;
        m->vertices= v;
    }
    m->primitive_type= GL_QUADS;
    m->vertex_count= segment_count * 2 + 2;
    m->index_count= segment_count * 4;


}


void (*generation_func_table[])( Mesh* m )=
{
	GenRoundBody, GenDefaultShell, GenDefaultNucleus, GenFlagellum
};

bool generation_func_animation_table[]=
{
	false, false, false, true
};
