#ifndef MONSTER_H
#define MONSTER_H

#include <Shooter.h>


class Monster : public Shooter
{
    public:
        Monster(Coordinate position, Coordinate maxSpeed, Image graphic, Image hitbox, string name);
        virtual void Move();
        virtual void Action(vector <Sprite*> & sprites, Image missileImage, Image missileHitbox, Coordinate missileSpeed);


    private:

        int motionCounter;
};

#endif // MONSTER_H
