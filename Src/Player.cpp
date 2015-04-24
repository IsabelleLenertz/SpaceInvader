#include "Player.h"

extern const int SCREEN_WIDTH;

Player::Player(Coordinate position, Coordinate maxSpeed, Image graphic, Image hitbox, string name): Shooter(position, maxSpeed, graphic, hitbox, name)
{
    //ctor
}

void Player::moveRight()
{
    /// Allow moves only on the x axes.
    if ( m_position.x < (600 - m_graphic.xSize) )
    {
        this->m_position.x += this->m_maxSpeed.x;
    }
}

void Player::moveLeft()
{
    if (m_position.x > 0)
    {
        this->m_position.x -= this->m_maxSpeed.x;
    }
}
