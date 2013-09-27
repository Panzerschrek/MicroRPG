#ifndef PLAYER_H
#define PLAYER_H

#include "microbe.h"

class Player
{
public:
    Player(){}
    ~Player(){}

private:

    Microbe* microbe;
    Microbe* second_life;
};

#endif//PLAYER_H
