#ifndef PLAYER_H
#define PLAYER_H

#include <Shooter.h>


class Player : public Shooter
{
    public:
        Player(Coordinate position, Coordinate maxSpeed, Image graphic, Image hitbox, std::string name);
        virtual void moveLeft();
        virtual void moveRight();

    private:
};

#endif // PLAYER_H
