#ifndef SPRITE_H
#define SPRITE_H
#include "structures.h"
#include <string>

using namespace std;



class Sprite
{
    public:
    Sprite(Coordinate position, Coordinate maxSpeed, Image graphic, Image hitBox, std::string name);
    virtual ~Sprite();

    /// Function use to draw a sprite of on the screen.
    void draw();

    /// Function use to modify the coordinate.
    virtual void Move();

    /// Function use to detect collision with another sprite.
    virtual bool collision (Coordinate otherSpritesPosition, Image otherSpritesHitbox);

    /// Function use to read the position, the speed, and the hit box of a sprite.
    virtual Coordinate getPosition() const;
    virtual Coordinate getSpeed() const;
    virtual Image getHitbox() const;

    ///To be left empty. nothing happens if the sprite is not a shooter.
    virtual void ShootMissile (vector <Sprite*> & sprites, Image missileImage, Image missileHitbox, Coordinate missileSpeed);


    protected:
    Coordinate m_position;
    Coordinate m_maxSpeed;
    Image m_graphic;
    Image m_hitbox;
    std::string m_name;

};

#endif // SPRITE_H
