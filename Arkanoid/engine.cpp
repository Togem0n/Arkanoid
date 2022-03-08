#include "engine.h"

SDL_Window* window;
SDL_Renderer* renderer;

bool keys[SDL_NUM_SCANCODES] = { false };

float delta_time = 0.f;
