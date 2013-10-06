#ifndef PLAYER_H
#define PLAYER_H

#include "microbe.h"
#include "level.h"

class Player
{
public:
    Player(Level * const lev) :
        level(lev),
        microbe(new Microbe(0.0f, 0.0f))
    {
        level->addMicrobe(microbe, microbe->X(), microbe->Y());
    }
    ~Player()
    {
        delete microbe;
    }

private:
    Level* const level;
    Microbe* microbe;
    Microbe* second_life;
}; // class Player

#endif// PLAYER_H
