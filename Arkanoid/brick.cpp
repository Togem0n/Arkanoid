#include <brick.h>
#include <game.h>
#include <engine.h>
#include <SDL_image.h>

void Brick::draw() {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_Rect rect = { (int)x, (int)y, width, height };
	SDL_RenderFillRect(renderer, &rect);
}