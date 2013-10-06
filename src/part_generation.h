#include "renderer.h"

void GenRoundBody( Mesh* m );
void GenDefaultNucleus( Mesh* m );
void GenDefaultShell( Mesh* m );
void GenFlagellum( Mesh* m );


extern void (*generation_func_table[])( Mesh* m );

//if true - part must be regenerated before drawing
extern bool generation_func_animation_table[];
