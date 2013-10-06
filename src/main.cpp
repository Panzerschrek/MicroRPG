#include "micro_rpg.h"
#include "main_loop.h"
#include "renderer.h"
int main()
{
    Level* level= new Level();
    Player* player= new Player(level);
    MainLoop* main_loop= new MainLoop( level, player );

	while(1)
		main_loop->Loop();

	return 0;
}
