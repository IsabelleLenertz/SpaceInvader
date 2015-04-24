#include "Monster.h"

Monster::Monster (Coordinate position, Coordinate maxSpeed, Image graphic, Image hitbox, string name): Shooter(position, maxSpeed, graphic, hitbox, name), motionCounter(0)
{
}

void Monster::Move()
{
    if (this->motionCounter > 0) {
        this->m_position.x += this->m_maxSpeed.x;
        this->m_position.y += this->m_maxSpeed.y;
    } else {
        this->m_position.x -= this->m_maxSpeed.x;
        this->m_position.y -= this->m_maxSpeed.y;
    }

    this->motionCounter ++;

    if (this->motionCounter > 80)
        this->motionCounter = -80;
}

void Monster::Action(vector <Sprite*> & sprites, Image missileImage, Image missileHitbox, Coordinate missileSpeed){

    int ranShooting = rand()%1000;
    if (ranShooting == 1)
    {
        this->ShootMissile(sprites, missileImage, missileHitbox, missileSpeed);
    }
};
