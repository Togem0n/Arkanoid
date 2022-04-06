#include <projectile.h>
#include <engine.h>

void Projectile::update() {
	if (!alive) return; // feedback: styling: usually return statements are always placed in a new line for better readability
	x += 400 * delta_time;
}

void Projectile::draw() {
	if (!alive) return;
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_Rect rect = { (int)x, (int)y, 8, 8 };
	SDL_RenderFillRect(renderer, &rect);
}