#pragma once
#include <engine.h>

struct Brick
{
	float x = -1;
	float y = -1;
	float posX = -1;
	float posY = -1;
	SDL_Texture* texture;
	bool getHit = false;
	int getHitTimer = 0;
	// 1024 * 768 in total
	// 1024 * 512 allow to spawn bricks
	// 1024 /  128 = 8 bricks maxinum per row
	// 512 / 64 = 8 bricks maxinum rows

	// 768 - 512 = 256 not allow to spawn bricks
	int width = 128;
	int height = 64;

	int life = 0;

	void draw();
};
