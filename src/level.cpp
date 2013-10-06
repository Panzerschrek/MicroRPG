#include "level.h"
#include "microbe.h"

Level::Level() :
    lastMicrobeIndex(0)
{
    addMicrobe(new Microbe(2.0f, 2.0f), 2.0f, 2.0f);
}

Level::~Level()
{
    for (int i=0; i<lastMicrobeIndex; ++i)
    {
        delete microbes[i];
    }
}

void Level::addMicrobe(Microbe* const microbe, const float x, const float y)
{
    if (lastMicrobeIndex < MAX_MICROBES)
    {
        microbes[lastMicrobeIndex++] = new Microbe(x, y);
    }
}

int Level::getLastMicrobeIndex() const
{
    return lastMicrobeIndex;
}

Microbe* Level::getMicrobe(const int index) const
{
    return microbes[index];
}
