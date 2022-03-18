#pragma once
#include <engine.h>
#include <draw.h>

struct Player
{
	float x = 512;
	float y = 700;
	float posX;
	float posY;
	int width = 128;
	int height = 32;
	float speed = 600;
	float currentGoal = 0;
	float currentPoint = 0;
	int life = 5;
	SDL_Texture *texture;

	int next_proectile_index = 0;
	int numOfBall = 0;

	void move();
	void draw();
	void shoot();
	void drawBall();
	void resetTexture();
};
