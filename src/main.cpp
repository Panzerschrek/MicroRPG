#include "micro_rpg.h"
#include "main_loop.h"
#include "renderer.h"

int main()
{


	Player* player= new Player();
	Level* level= new Level();
	Renderer* renderer= new Renderer( level, player );
	MainLoop* main_loop= new MainLoop( renderer, level, player );


	for( int i= 0; i< 10000; i++ )
		main_loop->Loop(), usleep(16000);


	printf( "MicroRPG!\n" );
	return 0;
}
