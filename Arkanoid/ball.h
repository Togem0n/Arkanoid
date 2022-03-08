#pragma once

#include <engine.h>
struct Ball {
	float x;
	float y;
	float posX;
	float posY;
	SDL_Texture* texture;
	int radius = 16;
	float xSpeed = 0;
	float ySpeed = 400;
	float xMaxSpeed = 400;

	bool isFlying = false;
	bool isMovingWithPlayer = true;

	void move();
	void moveWithPlayer();
	void setSpeedWhenCollideWithPlayer();
	void setSpeedWhenCollideWithWall();
	void setSpeedWhenCollideWithBrick();
	void update();
	void draw();
};