#ifndef RENDERER_H
#define RENDERER_H


#include "player.h"
#include "level.h"
#include "micro_rpg.h"
#include "text.h"


class Renderer
{
	public:
	Renderer( Level* l, Player* p );
	~Renderer(){}

	void Draw();

	private:
	Player* player;
	Level* level;

	Text text;


};

#endif//RENDERER_H
