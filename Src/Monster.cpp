#include "Monster.h"

Monster::Monster (Coordinate position, Coordinate maxSpeed, Image graphic, Image hitbox, string name): Shooter(position, maxSpeed, graphic, hitbox, name)
{
    //ctor
}

void Monster::Move()
{
    //this->m_position.x += this->m_maxSpeed.x;
}
