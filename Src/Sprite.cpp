#include "Sprite.h"
#include "structures.h"
#include "sdl.h"
#include "sdl_image.h"
#include "Shooter.h"
#include <string>

/// Pointers to the display window and the background
extern SDL_Surface* pScreen;
extern SDL_Surface* pBackground;

using namespace std;

Sprite::Sprite(Coordinate position, Coordinate maxSpeed, Image graphic, Image hitbox, string name): m_position(position), m_maxSpeed(maxSpeed), m_graphic(graphic), m_hitbox(hitbox), m_name(name)
{
    /** Load and convert the sprite's image */

    /// Create a pointer to temporary surface to load the sprite's image.
    SDL_Surface* pLoadingImage;

    /// Load the image of the sprite into a SDL surface and check for error
    pLoadingImage = IMG_Load(m_graphic.address);
    if (pLoadingImage == NULL){
        cerr << "Could not load " << this->m_name << " image: " << SDL_GetError();
    }

    /// Convert the image into a usable surface and check for error.
    this->m_graphic.pImage = SDL_DisplayFormat(pLoadingImage);
    if (this->m_graphic.pImage == NULL) {
        cerr << "Could not convert " << this->m_name << " image: " << SDL_GetError();
    }

    /// Set the transparency color
    SDL_SetColorKey(this->m_graphic.pImage, SDL_SRCCOLORKEY, this->m_graphic.transparencyColor);

    /// Free the temporary surface
    SDL_FreeSurface(pLoadingImage);


    /** Load and convert the sprite's hit box */

    /// Create a pointer to temporary surface to load the sprite's image.
    SDL_Surface* pLoadingHitbox;

    /// Load the image of the sprite into a SDL surface and check for error
    pLoadingHitbox = IMG_Load(m_hitbox.address);
    if (pLoadingHitbox == NULL){
        cerr << "Could not load " << this->m_name << " hit box: " << SDL_GetError();
    }

    /// Convert the image into a usable surface and check for error.
    this->m_hitbox.pImage = SDL_DisplayFormat(pLoadingHitbox);
    if (this->m_hitbox.pImage == NULL) {
        cerr << "Could not convert " << this->m_name << " hit box: " << SDL_GetError();
    }

    /// Set the transparency color
    SDL_SetColorKey(this->m_hitbox.pImage, SDL_SRCCOLORKEY, this->m_hitbox.transparencyColor);

    /// Free the temporary surface
    SDL_FreeSurface(pLoadingHitbox);
}

Sprite::~Sprite()
{
    SDL_FreeSurface(this->m_graphic.pImage);
    SDL_FreeSurface(this->m_hitbox.pImage);
}

void Sprite::draw()
{
    /// Create a rectangle to define the position of the sprite
    SDL_Rect SpriteLocation = {this->m_position.x, this->m_position.y, this->m_graphic.xSize, this->m_graphic.ySize};

    /// Display the image on the screen
    SDL_BlitSurface (this->m_graphic.pImage, NULL, pScreen, &SpriteLocation);
}

void Sprite::Move()
{
    /// Modify the position of the sprite
    this->m_position.x += this->m_maxSpeed.x;
    this->m_position.y += this->m_maxSpeed.y;

}

// Function use to detect collision with another sprite.
bool Sprite::collision (Coordinate otherSpritesPosition, Image otherSpritesHitbox)
{
    if ( m_position.y == (otherSpritesPosition.y + otherSpritesHitbox.xSize) )
    {
        if ( (m_position.x < (otherSpritesPosition.x + otherSpritesHitbox.xSize)) && (m_position.x > otherSpritesPosition.x) )
        {
            return true;
        }

        if ( ((m_position.x + m_hitbox.xSize) < (otherSpritesPosition.x + otherSpritesHitbox.xSize)) && ((m_position.x + m_hitbox.xSize) > otherSpritesPosition.x) )
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

}


Coordinate Sprite::getPosition() const
{
    return this->m_position;
}

Coordinate Sprite::getSpeed() const
{
    return this->m_maxSpeed;
}

Image Sprite::getHitbox() const
{
    return this->m_hitbox;
}

///To be left empty. nothing happens if the sprite is not a shooter.
void Sprite::ShootMissile (vector <Sprite*> & sprites, Image missileImage, Image missileHitbox, Coordinate missileSpeed)
{

}
