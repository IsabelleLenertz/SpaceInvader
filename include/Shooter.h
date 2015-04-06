#ifndef SHOOTER_H
#define SHOOTER_H

#include <Sprite.h>
using namespace std;


class Shooter : public Sprite
{
    public:
        Shooter(Coordinate position, Coordinate maxSpeed, Image graphic, Image hitbox, std::string name);

    private:
};

#endif // SHOOTER_H
