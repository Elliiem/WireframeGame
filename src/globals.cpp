#include<map>
#include <SDL2/SDL.h>
#include "window.h"

std::map<int, bool> keyboard;

Win Win(1080,1920);

bool quit = false;
Uint32 black = 0;
Uint32 white = 16777215;
Uint32 red = 16711680;
Uint32 green = 65280;
Uint32 blue = 255;
