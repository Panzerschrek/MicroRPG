#include "micro_rpg.h"
#include "main_loop.h"
#include "renderer.h"
int main()
{

	Player* player= new Player();
	Level* level= new Level();
	MainLoop* main_loop= new MainLoop( level, player );


	while(1)
		main_loop->Loop();

	return 0;
}
