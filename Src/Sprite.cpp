#include "Sprite.h"
#include "structures.h"
#include "sdl.h"
#include "sdl_image.h"
#include "Shooter.h"
#include <string>

/// Pointers to the display window and the background.
extern SDL_Surface* pScreen;
extern SDL_Surface* pBackground;

/// Dimensions of the screen.
extern const int SCREEN_HEIGHT;
extern const int SCREEN_WIDTH;

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
    if ( m_position.y <= (otherSpritesPosition.y + otherSpritesHitbox.xSize) && m_position.y >= otherSpritesPosition.y)
    {
        if ( (m_position.x <= (otherSpritesPosition.x + otherSpritesHitbox.xSize)) && (m_position.x >= otherSpritesPosition.x) )
        {
            return true;
        }

        if ( ((m_position.x + m_hitbox.xSize) <= (otherSpritesPosition.x + otherSpritesHitbox.xSize)) && ((m_position.x + m_hitbox.xSize) >= otherSpritesPosition.x) )
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

int Sprite::DetectCollision (vector <Sprite*> & sprites)
{
    /// Go through the list of sprite.
    for(vector<Sprite*>::iterator currentSprite=sprites.begin() ; currentSprite < sprites.end(); currentSprite++ )
    {
        /// For each sprite, check if there is a collision with another.
        for(vector<Sprite*>::iterator it=sprites.begin() ; it < sprites.end(); it++ )
        {
            if ( currentSprite != it )
            {
                if ( ((*currentSprite)->collision((*it)->getPosition(),(*it)->getHitbox()) ) == true )
                {
                    /// Delete the element
                    delete *currentSprite;
                    /// Remove the reference from the list
                    currentSprite = sprites.erase(currentSprite);

                    /// Delete the element
                    delete *it;
                    /// Remove the reference from the list
                    it = sprites.erase(it);

                    /// To simplify, we will only check one collision at a time.
                    /// This allows us to delete an element of a list we are iterating on.
                    return 1;
                }
            }
        }
    }
    return 0;
}

/**Function used to destroy the sprites if they go outside the screen.
Return 1 if an element was destroyed.
Return 0 if no sprite was destroyed.
*/

int Sprite :: DestroyOutOfScreen(vector <Sprite*> & sprites)
{
    const int SCREEN_WIDTH = 600;
    const int SCREEN_HEIGHT = 450;

    for(vector<Sprite*>::iterator it=sprites.begin() ; it < sprites.end(); it++ )
    {
        /// Make sure the sprites can go a little (10 pixels) out of the screen without being destroyed.
        if ((*it)->m_position.x < -10 || ((*it)->m_position.x + (*it)->m_graphic.xSize) > (SCREEN_WIDTH + 10) )
        {
            /// Delete the element
            delete *it;
            /// Remove the reference from the list
            it = sprites.erase(it);
            /// To simplify, we will check only for 1 sprite out of the screen at the time.
            /// This allows us to delete an element of a list we are iterating on.
            /// return 1 if an element was destroyed.
            return 1;
        }

        if ( (*it)->m_position.y > SCREEN_HEIGHT || (*it)->m_position.y < 0 )
        {
            /// Delete the element
            delete *it;
            /// Remove the reference from the list
            it = sprites.erase(it);
            /// To simplify, we will check only for 1 sprite out of the screen at the time.
            /// This allows us to delete an element of a list we are iterating on.
            /// return 1 if an element was destroyed.
            return 1;
        }
    }
    /// Return 0 if no sprite was destroyed.
    return 0;
}
