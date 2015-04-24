 /*
    Project SDL
    Copyright (C) 2015  Isabelle Delmas-Lenertz

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>
#include <cstdlib>
#include <vector>
#include "sdl.h"
#include "sdl_image.h"
#include "structures.h"
#include "Sprite.h"
#include "Shooter.h"
#include "Monster.h"
#include "Player.h"
#include "Missile.h"


using namespace std;

/// Screen dimensions
/// Set as global variable because it will be used by most of the classes and functions.
const int SCREEN_WIDTH=600;
const int SCREEN_HEIGHT=450;

/// Pointers to the display window and the background.
/// Set as global variable because it will be used by most of the classes and functions.
SDL_Surface* pScreen = NULL;



/** Initialize SDL (SDL_INIT_EVERYTHING) and the png Video mode (IMG_INIT_PNG).
*/
void initSDL();

/** Create the windowed environment (Screen), load and display the background.
pTempBackground is a pointer that will be set to the temporary background.
pBackground is a pointer that will be set to the actual usable background.
*/
void windowAndBackground(SDL_Surface* & pTempBackround, SDL_Surface* & pBackground);

/** Go through the dynamic list of sprites, look for collisions and erase the colliding sprites.
Return 1 if a collision occurred.
*/
int detectCollision (vector <Sprite*> & sprites);


int main(int argc, char* argv[])
{
    /// Initiate the score counter.
    int score = 0;

    /// Create the pointer to the future SDL_Surface storing the background.
    SDL_Surface* pTempBackround = NULL;
    SDL_Surface* pBackground = NULL;

    ///Create the Input structure storing the user's input and set it to false.
    Input inputStorage;
    memset(&inputStorage, 0, sizeof(inputStorage)); /// Set all the possible input to false.

    /// Initiate SDL
    initSDL();

    /// Create the Screen, load and display the Background.
    windowAndBackground(pTempBackround, pBackground);

    /// Defines the colors than will be used later.
    SDL_Color white = {255, 255, 255, 255};
    /// Convert a SDL_Color to make it usable in a specific window (our Screen).
    Uint32 whiteColor = SDL_MapRGB(pScreen->format, white.r, white.g, white.b);

    /// Define the characteristics of the monsters.
    /// speed of the monsters.
    Coordinate monsterSpeed = {10,0}; /// Speed of the regular monsters

    /// monster type 1.
    Image monster1Image; // = {"img/enemy/Enemy2/enemy2_1.png", 25, 33, whiteColor, NULL, NULL};
    monster1Image.address = "img/enemy/Enemy2/enemy2_1.png";
    monster1Image.xSize = 25;
    monster1Image.ySize = 33;
    monster1Image.transparencyColor = whiteColor;
    Image monster1Hitbox = monster1Image;
    monster1Hitbox.address = "img/enemy/Enemy2/enemy2_1_hitbox.png";
    Coordinate monster1Coordinate = {70, 20};

    /// Define the characteristics of the player.
    Image playerImage;
    playerImage.address = "img/player/tower1_1.png";
    playerImage.xSize = 28;
    playerImage.ySize = 44;
    playerImage.transparencyColor = whiteColor;
    Image playerHitbox = playerImage;
    playerHitbox.address = "img/player/tower1_1_hitbox.png";
    Coordinate playerCoordinate = {286, 404};
    Coordinate playerMaxSpeed = {3, 0};

    /// Define the characteristic of the missiles.
    Image missileImage;
    missileImage.address = "img/missile/missile.png";
    missileImage.transparencyColor = whiteColor;
    Image missileHitbox = missileImage;
    Coordinate missileSpeed = {0, -1};


    /// Create the monsters (5 raws of 15 monsters)
    vector <Sprite*> sprites;
    for (uint16_t i = 0; i < 15; i++)
    {
        for (uint16_t j = 0; j < 5; j++)
        {
            sprites.push_back(new Monster( { (monster1Coordinate.x + 35*i), monster1Coordinate.y + 35 * j} , monsterSpeed, monster1Image, monster1Hitbox, "Monster type 1") );
        }
    }

    /// Create a vector to store the monster's missiles.
    vector <Sprite*> monsterMissile;

    /// Create the player
    Player player(playerCoordinate, playerMaxSpeed, playerImage, playerHitbox, "Player");


    /// set caption
    SDL_WM_SetCaption("Monster Shooting", NULL);

    /// Display the initial elements
    SDL_Flip(pScreen);

    ///repeat as long as the user does no quit
    while(inputStorage.quit == false)
    {
        /// Check all the waiting inputs and update inputStorage
        updateInput(&inputStorage);

        /// If the left arrow if down, move the player left
        if (inputStorage.key[SDLK_LEFT])
        {
            player.moveLeft();
        }

        /// If the right arrow if down, move the player right
        else if (inputStorage.key[SDLK_RIGHT])
        {
            player.moveRight();
        }
        /// If the key space in down, shoot a missile
        else if (inputStorage.key[SDLK_SPACE])
        {
            /// Assure that the player shoots only one missile at a time.
            inputStorage.key[SDLK_SPACE] = false;
            /// Create a new sprite, Missile, each time the play hits SPACE.
            player.ShootMissile (sprites, missileImage, missileHitbox, missileSpeed);
        }

        /// Check for collision

        /// Draw the new screen
        SDL_BlitSurface (pBackground, NULL, pScreen, NULL);
        /// Draw all the sprites at their new location (monster and missile shoot by the player)
        for(vector<Sprite*>::iterator it=sprites.begin() ; it < sprites.end(); it++ )
        {
            /// Shoot a missile if a random number is 1.
            int ranShooting = rand()%1000;
            if (ranShooting == 1)
            {
                (*it)->ShootMissile (monsterMissile, missileImage, missileHitbox, {-missileSpeed.x, -missileSpeed.y});
            }
            /// Move the Sprites
            (*it)->Move();
            (*it)->draw();
        }

        /// Draw and move the missiles shot by the monsters.
        for(vector<Sprite*>::iterator it=monsterMissile.begin() ; it < monsterMissile.end(); it++ )
        {
            (*it)->Move();
            (*it)->draw();
        }
        score += detectCollision (sprites);
        player.draw();
        /// Update the screen
        SDL_Flip(pScreen);

        /// Wait a little
        SDL_Delay(10);
    }

    cout << score << endl;
    /// Free the surfaces
    SDL_FreeSurface(pScreen);
    SDL_FreeSurface(pBackground);
    SDL_Quit();

    /// Indicate normal termination
    cout << "Terminating normally." << endl;
    return EXIT_SUCCESS;
}

/** Initialize SDL (SDL_INIT_EVERYTHING) and the png Video mode (IMG_INIT_PNG).
*/
void initSDL()
{
    ///initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING)== -1)
    {
        cerr << "Could not initialize SDL!" << SDL_GetError() << endl;
        exit(1);
    }
    else
    {
        cout << "SDL initialized properly!" << endl;
    }

    /// Initiates the png Video mode
    if (IMG_Init(IMG_INIT_PNG) == -1)
    {
        cerr << "Could not initiate the png video mode: " << SDL_GetError() << endl;
    }
}

/** Create the windowed environment (Screen), load and display the background.
pTempBackground is a pointer that will be set to the temporary background.
pBackground is a pointer that will be set to the actual usable background.
*/
void windowAndBackground(SDL_Surface* & pTempBackround, SDL_Surface* & pBackground)
{
    /// Create windowed environment
    pScreen = SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,0,SDL_DOUBLEBUF | SDL_HWSURFACE);
    if (pScreen == NULL){
        cerr << "Could not set up display surface!" << SDL_GetError() << endl;
        exit(1);
    }

    /// Display the background
    pTempBackround = IMG_Load("img/background/bg600_450.png");
    if (pTempBackround == NULL)
    {
        cerr << "Could not load the background: " << SDL_GetError() << endl;
        exit (3);
    }
    /// Convert the previous surface into a usable image and copy it into a new surface.
    pBackground = SDL_DisplayFormat(pTempBackround);
    if (pBackground == NULL)
    {
        cerr << "could not convert the pTempBackground using SDL_DisplayFormat: " << SDL_GetError() << endl;
    }

    SDL_FreeSurface (pTempBackround);
    SDL_BlitSurface (pBackground, NULL, pScreen, NULL);
}

int detectCollision (vector <Sprite*> & sprites)
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
                    currentSprite = sprites.erase(currentSprite);
                    it = sprites.erase(it);
                    return 1;
                }
            }
        }
    }
    return 0;
}
