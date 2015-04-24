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

    /// Function used to draw a sprite of on the screen.
    void draw();

    /// Function used to modify the coordinate.
    virtual void Move();

    /// Function used to detect collision with another sprite.
    virtual bool collision (Coordinate otherSpritesPosition, Image otherSpritesHitbox);

    /// Function used to read the position, the speed, and the hit box of a sprite.
    virtual Coordinate getPosition() const;
    virtual Coordinate getSpeed() const;
    virtual Image getHitbox() const;

    /// Function used to detect sprite collision within a list.
    static int DetectCollision (vector <Sprite*> & sprites);

    protected:
    Coordinate m_position;
    Coordinate m_maxSpeed;
    Image m_graphic;
    Image m_hitbox;
    std::string m_name;

};

#endif // SPRITE_H
