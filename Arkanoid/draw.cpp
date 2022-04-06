#include <draw.h>
#include <game.h>
#include <string>

using std::string;

void prepareScene(void)
{
	SDL_SetRenderDrawColor(renderer, 96, 128, 255, 255);
	SDL_RenderClear(renderer);
}

void presentScene(void)
{
	SDL_RenderPresent(renderer);
}

SDL_Texture *loadTexture(const char *filename)
{
	SDL_Texture* texture;

	//SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

	texture = IMG_LoadTexture(renderer, filename); // feedback: doesn't seem like SDL_DestroyTexture is called anywhere in your code
													// for the allocated texture. Without doing it its likely that you have a memory leak

	return texture;
}

void blit(SDL_Texture *texture, int x, int y)
{
	SDL_Rect dest;

	dest.x = x;
	dest.y = y;

	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

	SDL_RenderCopy(renderer, texture, NULL, &dest);
}

void Draw_Player() {
	blit(player.texture, player.x, player.y);
}

void Draw_Ball() {

	for (int i = 0; i < BALL_MAX; i++) {
		//balls[i].update();
		if (balls[i].isAlive) {
			blit(balls[i].texture, balls[i].x, balls[i].y);
		}
	}
	//blit(ball.texture, ball.x, ball.y);
}

void Draw_Bricks() {
	for (int i = 0; i < Row; i++) {
		for (int j = 0; j < Column; j++) {
			if (bricks[i][j].life <= 0) {
				continue;
			}
			//if (bricks[i][j].getHit) {
			//	bricks[i][j].getHitTimer++;
			//	if (bricks[i][j].getHitTimer > 25) {
			//		bricks[i][j].getHitTimer = 0;
			//		bricks[i][j].getHit = false;

			//		string brickTextureName = "12864brick";
			//		string brickLife = std::to_string(bricks[i][j].life);
			//		brickTextureName.append(brickLife);
			//		brickTextureName.append(".png");
			//		bricks[i][j].texture = loadTexture(brickTextureName.c_str());
			//	}
			//}

			blit(bricks[i][j].texture, bricks[i][j].x, bricks[i][j].y);
		}
	}
}

void Draw_Win() {
	SDL_Texture* winTexture = loadTexture("win.png");;
	blit(winTexture, 0, 0);
}

void Draw_Lose() {
	// feedback: is there a reason you load the texture every time you want to draw it? It would be more efficient to save it somewhere and load
	// only the first time. And then just blit it when you want to draw it. It is also leaking the texture as you overwrite it every time.
	SDL_Texture* loseTexture = loadTexture("lose.png");;
	blit(loseTexture, 0, 0);
}