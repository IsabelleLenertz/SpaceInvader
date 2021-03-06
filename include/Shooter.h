#ifndef SHOOTER_H
#define SHOOTER_H
#include <vector>

#include <Sprite.h>
using namespace std;


class Shooter : public Sprite
{
    public:
        Shooter(Coordinate position, Coordinate maxSpeed, Image graphic, Image hitbox, std::string name);
        virtual void Action(vector <Sprite*> & sprites, Image missileImage, Image missileHitbox, Coordinate missileSpeed)=0;

    protected:
        void ShootMissile (vector <Sprite*> & sprites, Image missileImage, Image missileHitbox, Coordinate missileSpeed);

};

#endif // SHOOTER_H
