#ifndef SHOOTER_H
#define SHOOTER_H
#include <vector>

#include <Sprite.h>
using namespace std;


class Shooter : public Sprite
{
    public:
        Shooter(Coordinate position, Coordinate maxSpeed, Image graphic, Image hitbox, std::string name);
        virtual void ShootMissile (vector <Sprite*> & sprites, Image missileImage, Image missileHitbox, Coordinate missileSpeed);


    private:
};

#endif // SHOOTER_H
