#include <iostream>
#include <string>
#include "sdl.h"
#include "structures.h"


using namespace std;

/** Update the array representing the keyboard by treating all the waiting events */
void updateInput (Input* input)
{
    /// Creat a SDL_Event to store all the incoming events
    SDL_Event event;

    /// while there is an event stored in event waiting to be treated.
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_KEYDOWN:
                /// If a key was pressed, change the matching bool to true.
                input->key[event.key.keysym.sym] = true;
                break;
            case SDL_KEYUP:
                /// If a key was released, change the matching bool to false.
                input->key[event.key.keysym.sym] = false;
                break;
            case SDL_QUIT:
                /// If the user quit, change m_quit to true.
                input->quit = true;
        }
    }
}

//void collision (vector <Sprite*> & sprites)
//{
//    for(vector<Sprite*>::iterator it=sprites.begin() ; it < sprites.end(); it++ )
//    {
//        for ( vector<Sprite*>::iterator currentSprite=sprites.begin() ; currentSprite < sprites.end(); currentSprite++)
//        {
//            if
//            {
//                /// check if there is a collision between it and current sprite.
//            }
//        }
//    }
//
//}
