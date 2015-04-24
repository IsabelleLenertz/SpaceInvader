#ifndef STRUCTURES_H
#define STRUCTURES_H


#include <iostream>
#include <string>
#include <vector>
#include "sdl.h"

using namespace std;

class Sprite;

/// Used to defined the coordinates or the maximum speed of a sprite.
struct Coordinate
{
    int16_t x; /// Coordinate along the x axes.
    int16_t y; /// Coordinate along the y axes.
};


/** Used to define the address of an image, its size and its transparency color.
address = the relative address to the file
xSize = the width of the image
ySize = the height of the image
transparencyColor = use to define the transparency color of the Image using SetColorKey
pLoadingImage = pointer to a temporary SDL_Surface to load the image
pImage = pointer to a usable SDL_Surface containing the image
**/
struct Image
{
    char const * address = "";
    uint16_t xSize = 0;
    uint16_t ySize = 0;
    Uint32 transparencyColor = 0;
    SDL_Surface* pImage = NULL;
};

struct Input
{
    bool key[SDLK_LAST];
    bool quit = false;
};

/** Update the array representing the keyboard by treating all the waiting events */
void updateInput (Input* input);

void collision (vector <Sprite*> & sprites);


#endif
