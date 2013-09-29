#ifndef LEVEL_H
#define LEVEL_H

#define MAX_MICROBES 10

class Microbe;

class Level
{
public:
    Level();
    ~Level();

    void PhysTick();
    void addMicrobe(Microbe *, float x, float y);
    int getLastMicrobeIndex() const;
    Microbe* getMicrobe(int index) const;
private:
    Microbe* microbes[MAX_MICROBES];
    int lastMicrobeIndex;
};

#endif // LEVEL_H
