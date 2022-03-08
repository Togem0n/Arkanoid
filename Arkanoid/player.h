#pragma once
#include <engine.h>

struct Player
{
	float x = 512;
	float y = 700;
	float posX;
	float posY;
	int width = 128;
	int height = 32;
	float speed = 600;
	SDL_Texture *texture;

	int next_proectile_index = 0;

	void move();
	void draw();
	void shoot();
	void drawBall();
};
