#include "micro_rpg.h"
#include "main_loop.h"

int main()
{
	MainLoop ml;
	for( int i= 0; i< 10000; i++ )
		ml.Loop(), usleep(16000);
	usleep(100000);
	printf( "MicroRPG!\n" );
	return 0;
}
