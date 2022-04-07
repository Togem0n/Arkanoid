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
	// Initialization

	INIT_SDL();

	INIT_PLAYER();

	INIT_BALL();

	INIT_BRICKS();

	Uint64 previous_ticks = SDL_GetPerformanceCounter();

	while (1)
	{
		Uint64 ticks = SDL_GetPerformanceCounter();
		Uint64 delta_ticks = ticks - previous_ticks;
		previous_ticks = ticks; 
		delta_time = (float)delta_ticks / SDL_GetPerformanceFrequency(); 

		prepareScene();	
		GetInput();

		if (inGame) {
			// win or die
			CHECK_CONDITION();
			NEW_BALL(); // feedback: I'd change the name of this function to something that describes more what it is doing.
						// Right now when I read this, it feels like it will always spawn a new ball each update.

			// update()
			player.move();

			for (int i = 0; i < BALL_MAX; i++) {
				if (balls[i].isAlive) {
					balls[i].update();
				}
			}
			// ball.update();

			// draw stuffs
			Draw_Player();
			Draw_Ball();
			Draw_Bricks();
		}
		else if(inWinning && keys[SDL_SCANCODE_SPACE]){
			GO_NEXTLEVEL();
		}
		else if (isLose && keys[SDL_SCANCODE_SPACE]) {
			RESTART_LEVEL();
		}

		if (inWinning && !inGame) {
			Draw_Win();
		}

		if (isLose && !inGame) {
			Draw_Lose();
		}

		presentScene();

		SDL_Delay(16); 
 
	}

	return 0;
}