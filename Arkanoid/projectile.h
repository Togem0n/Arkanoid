#pragma once
struct Projectile {
	float x;
	float y;
	bool alive = false;

	void update();
	void draw();
};