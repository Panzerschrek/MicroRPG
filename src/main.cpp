#include "micro_rpg.h"
#include "main_loop.h"
#include "renderer.h"
int main()
{

	Player* player= new Player();
	Level* level= new Level();
	MainLoop* main_loop= new MainLoop( level, player );


	for( int i= 0; i< 10000; i++ )
		main_loop->Loop(), usleep(16000);


	printf( "MicroRPG!\n" );
	return 0;
}
