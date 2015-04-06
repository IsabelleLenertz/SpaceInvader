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

    /// Function use to read the position and the speed of a sprite.
    virtual Coordinate getPosition() const;
    virtual Coordinate getSpeed() const;


    protected:
    Coordinate m_position;
    Coordinate m_maxSpeed;
    Image m_graphic;
    Image m_hitbox;
    std::string m_name;

};

#endif // SPRITE_H
