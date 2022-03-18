#pragma once

#include <engine.h>
struct Ball {
	float x = -1;
	float y = -1;
	float posX = -1;
	float posY = -1;
	SDL_Texture* texture;
	int radius = 16;
	float xSpeed = 0;
	float ySpeed = 400;
	float xMaxSpeed = 400;
	int index = 0;
	int collionCounter = 0;

	bool isAlive = false;
	bool isFlying = false;
	bool isMovingWithPlayer = true;

	void move();
	void moveWithPlayer();
	void setSpeedWhenCollideWithPlayer();
	void setSpeedWhenCollideWithWall();
	void setSpeedWhenCollideWithBrick();
	void update();
	void draw();
	void checkDead();
	void resetBall();
};