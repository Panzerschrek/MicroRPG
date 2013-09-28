#include "renderer.h"

Renderer::Renderer( Level* l, Player* p ):
level(l), player(p)
{
}

void Renderer::Draw()
{
	static float ang= 0.0f;

    ang+=5.0f;


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -3.0f);
    glRotatef( ang, 0.0f, 1.0f, 0.0f );

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* front face */
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.7f, 0.1f);  /* green */
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);

    /* back face */
    glColor3f(0.9f, 1.0f, 0.0f);  /* yellow */
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);

    /* top side face */
    glColor3f(0.2f, 0.2f, 1.0f);  /* blue */
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);

    /* bottom side face */
    glColor3f(0.7, 0.0f, 0.1);  /* red */
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glEnd();

    glClearColor( 1.0f, 0.0f, 1.0f, 1.0f );

	glColor3f( 1.0f, 1.0f, 1.0f );
	glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -1.000001f);
    text.Draw();
}
