#include <stdio.h>
#include <SDL.h>
#include <stdlib.h>
#include <ctype.h>

#include <game.h>
#include <engine.h>
#include <player.h>
#include <init.h>
#include <draw.h>
#include <input.h>
#include <SDL_image.h>
#include <brick.h>
#include <readfile.h>

int main(int argc, char* args[])
{
	INIT_SDL();
	bool running = true;
	Uint64 previous_ticks = SDL_GetPerformanceCounter();

	// init player pos
	player.x = 512;
	player.y = 700;
	player.posX = player.x + player.width / 2;
	player.posY = player.y; //define pos of player in up middle of rect

	// init ball pos
	ball.x = player.x + player.width / 2 - ball.radius;
	ball.y = player.y - ball.radius * 2;
	ball.posX = ball.x + ball.radius;
	ball.posY = ball.y + ball.radius;

	// init play&ball's texture
	player.texture = loadTexture("player.png");
	ball.texture = loadTexture("ball.png");

	// read level from file
	vector<string> level = readLevel("level.txt");

	for (int i = 0; i < level.size(); i++) {
		std::cout << level[i] << std::endl;
	}

	// init bricks
	for (int i = 0; i < Row; i++) {
		for (int j = 0; j < Column; j++) {
			if (level[i][j] == '0') {
				continue;
			}
			bricks[i][j].life = level[i][j] - '0';
			bricks[i][j].x = j * bricks[i][j].width;
			bricks[i][j].y = i * bricks[i][j].height;
			bricks[i][j].posX = bricks[i][j].x + bricks[i][j].width / 2;
			bricks[i][j].posY = bricks[i][j].y + bricks[i][j].height / 2;
			bricks[i][j].texture = loadTexture("12864brick.png");
		}
	}

	for (int i = 0; i < Row; i++) {
		for (int j = 0; j < Column; j++) {
			std::cout << "(" << bricks[i][j].x << ", " << bricks[i][j].y << ") ";
		}
		std::cout << std::endl;
	}

	while (1)
	{
		Uint64 ticks = SDL_GetPerformanceCounter();
		Uint64 delta_ticks = ticks - previous_ticks;
		previous_ticks = ticks; 
		delta_time = (float)delta_ticks / SDL_GetPerformanceFrequency(); 

		prepareScene();

		GetInput();
 
		player.move();
		ball.update();
		
		for (int i = 0; i < Row; i++) {
			for (int j = 0; j < Column; j++) {
				//bricks[i][j].draw();
				if (bricks[i][j].life <= 0) {
					continue;
				}
				if (bricks[i][j].getHit) {
					bricks[i][j].getHitTimer++;
					if (bricks[i][j].getHitTimer > 25) {
						bricks[i][j].getHitTimer = 0;
						bricks[i][j].getHit = false;
						bricks[i][j].texture = loadTexture("12864brick.png");
					}
				}
				blit(bricks[i][j].texture, bricks[i][j].x, bricks[i][j].y);
			}
		}
		//std::cout << delta_time << std::endl;
		blit(player.texture, player.x, player.y);
		blit(ball.texture, ball.x, ball.y);

		presentScene();

		SDL_Delay(16); 
 
	}

	return 0;
}