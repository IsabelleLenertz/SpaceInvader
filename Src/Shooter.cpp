#include "Shooter.h"

#include <vector>
#include "Sprite.h"
#include "structures.h"
#include "Missile.h"
using namespace std;




Shooter::Shooter (Coordinate position, Coordinate maxSpeed, Image graphic, Image hitbox, string name): Sprite(position, maxSpeed, graphic, hitbox, name)
{
    //ctor
}

/** Adds a missile to the list of sprites.
vector <Sprite*> & sprites = a dynamic list of sprites
missileImage, missileHitbox, missileSpeed = the general characteristics of missiles defined in main.
*/
void Shooter::ShootMissile (vector <Sprite*> & sprites, Image missileImage, Image missileHitbox, Coordinate missileSpeed)
{
    /// The position of the missile is 5 pixels above the shooter, centered.
    /// The other characteristics of missiles are defined in main.cpp
    Coordinate missilePosition;
    missilePosition.x = m_position.x - missileImage.xSize + m_graphic.xSize/2;
    missilePosition.y = m_position.y - 5;

    /// Expend the list of sprites initiated in main.
    sprites.push_back( new Missile (missilePosition, missileSpeed, missileImage, missileHitbox, "missile") );
}
