#ifndef PLAYER_H
#define PLAYER_H

#include <Shooter.h>


class Player : public Shooter
{
    public:
        Player(Coordinate position, Coordinate maxSpeed, Image graphic, Image hitbox, std::string name);
        virtual void Move();
         virtual void Action(vector <Sprite*> & sprites, Image missileImage, Image missileHitbox, Coordinate missileSpeed);

    private:
         void moveLeft();
         void moveRight();
};

#endif // PLAYER_H
