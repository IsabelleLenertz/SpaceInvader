#include "Player.h"

Player::Player(Coordinate position, Coordinate maxSpeed, Image graphic, Image hitbox, string name): Shooter(position, maxSpeed, graphic, hitbox, name)
{
    //ctor
}

void Player::moveRight()
{
    /// Allow moves only on the x axes.
    this->m_position.x += this->m_maxSpeed.x;

}

void Player::moveLeft()
{
    this->m_position.x -= this->m_maxSpeed.x;
}
