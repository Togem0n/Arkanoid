#include "engine.h"

SDL_Window* window;
SDL_Renderer* renderer;

// feedback: by the name of this file I was expecting to see some logic related to the engine functions: input handling/rendering etc. It seems like
// it is just a place for some global vars instead. Those could be distributed instead  to classes that handle specific parts of the game:
// renderer should be part of the draw.cpp, window - draw.cpp or main.cpp 

bool keys[SDL_NUM_SCANCODES] = { false };

float delta_time = 0.f;
