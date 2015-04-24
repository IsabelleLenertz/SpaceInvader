#include "Player.h"

extern const int SCREEN_WIDTH;
extern Input inputStorage;

Player::Player(Coordinate position, Coordinate maxSpeed, Image graphic, Image hitbox, string name): Shooter(position, maxSpeed, graphic, hitbox, name)
{
    //ctor
}

void Player::Action(vector <Sprite*> & sprites, Image missileImage, Image missileHitbox, Coordinate missileSpeed){

    if (inputStorage.key[SDLK_SPACE])
    {
        /// Assure that the player shoots only one missile at a time.
        inputStorage.key[SDLK_SPACE] = false;
        /// Create a new sprite, Missile, each time the play hits SPACE.
        this->ShootMissile(sprites, missileImage, missileHitbox, missileSpeed);
    }
};


void Player::Move()
{
        /// If the left arrow if down, move the player left
        if (inputStorage.key[SDLK_LEFT])
        {
            this->moveLeft();
        }
        /// If the right arrow if down, move the player right
        else if (inputStorage.key[SDLK_RIGHT])
        {
            this->moveRight();
        }
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
