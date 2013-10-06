#include "microbe.h"

Microbe::Microbe(float x_, float y_) :
    x(x_),
    y(x_)
{
	direction= -3.1415926535f * 0.5f;
}

Microbe::~Microbe()
{}
