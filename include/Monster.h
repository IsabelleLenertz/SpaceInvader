#ifndef MONSTER_H
#define MONSTER_H

#include <Shooter.h>


class Monster : public Shooter
{
    public:
        Monster(Coordinate position, Coordinate maxSpeed, Image graphic, Image hitbox, string name);
        virtual void Move();


    private:
};

#endif // MONSTER_H
