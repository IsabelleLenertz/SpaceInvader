#ifndef MISSILE_H
#define MISSILE_H

#include "Sprite.h"
using namespace std;


class Missile : public Sprite
{
    public:
        Missile(Coordinate position, Coordinate maxSpeed, Image graphic, Image hitbox, std::string name);

    private:
};

#endif // MISSILE_H
