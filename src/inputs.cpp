#include <SDL2/SDL.h>
#include <map>

void INP_GetInputs(SDL_Event event, std::map<int, bool>* keyboardP)
{   
    switch (event.type)
    {
    case SDL_KEYUP: 
        try
        {
            keyboardP->at(event.key.keysym.sym) = false;
        }

        catch (const std::exception&) 
        {
            keyboardP->insert({event.key.keysym.sym,false});
        }

        break;

    case SDL_KEYDOWN:
        try
        {
            keyboardP->at(event.key.keysym.sym) = true;
        }

        catch (const std::exception&) 
        {
            keyboardP->insert({event.key.keysym.sym,true});
        }

        break;
    }

}
