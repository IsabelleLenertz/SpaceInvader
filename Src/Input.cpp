//#include "Input.h"
//#include <cstring>
//#include "sdl.h"
//
//Input::Input(): m_quit(false)
//{
//    /// Initialize all the values to 0
//    memset (this, false, sizeof(*this));
//}
//
///** Return the value of m_quit. */
//bool Input::getQuit()
//{
//    return m_quit;
//}
//
///** Return true (the key is pressed) or false (the key is released) for a specific key
//testedKey = the key to be tested*/
//bool getKeyState(uint16_t testedKey)
//{
//    return m_key[testedKey];
//}
//
//
///** Update the array representing the keyboard by treating all the waiting events */
//void Input::update()
//{
//    /// Creat a SDL_Event to store all the incoming events
//    SDL_Event event;
//
//    /// while there is an event stored in event waiting to be treated.
//    while (SDL_PollEvent(&event))
//    {
//        switch (event.type)
//        {
//            case SDL_KEYDOWN:
//                /// If a key was pressed, change the matching bool to true.
//                m_key[event.key.keysym.sym] = true;
//                break;
//            case SDL_KEYUP:
//                /// If a key was released, change the matching bool to false.
//                m_key[event.key.keysym.sym] = false;
//                break;
//            case SDL_QUIT:
//                /// If the user quit, change m_quit to true.
//                m_quit = true;
//        }
//    }
//}
