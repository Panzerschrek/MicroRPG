#ifndef MICROBE_H
#define MICROBE_H

#include "game_constants.h"

class Microbe
{
public:
    float X();
    float Y();
    float Dir();
    Microbe();
    ~Microbe();

private:

    float x, y;
    float direction;

    unsigned char body_type, nucleus_type, shell_type;

    unsigned char part_slots[ MAX_PART_SLOTS ];

    int health, energy, biomass;
};



inline float Microbe::X()
{
    return x;
}

float Microbe::Y()
{
    return y;
}

inline float Microbe::Dir()
{
    return direction;
}

#endif//MICROBE_H
