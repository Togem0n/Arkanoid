#include <init.h>
#include <game.h>
#include <readfile.h>
#include <string>

void INIT_SDL() {
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Arkanoid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Screen_Width, Screen_Height, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
}

void INIT_PLAYER() {
	player.x = 512;
	player.y = 700;
	player.posX = player.x + player.width / 2;
	player.posY = player.y; //define pos of player in up middle of rect

	player.life = 5;
	player.resetTexture();

	player.currentGoal = 0;
	player.currentPoint = 0;
}

void INIT_BALL() {
	Ball& ball = balls[player.numOfBall];
	ball.isAlive = true;
	ball.x = player.x + player.width / 2 - ball.radius;
	ball.y = player.y - ball.radius * 2;
	ball.posX = ball.x + ball.radius;
	ball.posY = ball.y + ball.radius;
	ball.texture = loadTexture("img/ball.png");
	ball.isMovingWithPlayer = true;
	player.numOfBall++;
}

void INIT_BRICKS() {
	string levelName = "level";
	string levelIndex = std::to_string(currentLevel);
	levelName.append(levelIndex);
	levelName.append(".txt");
	std::cout << levelName << std::endl;

	vector<string> level = readLevel(levelName);

	for (int i = 0; i < level.size(); i++) {
		std::cout << level[i] << std::endl;
	}

	for (int i = 0; i < Row; i++) {
		for (int j = 0; j < Column; j++) {

			if (level[i][j] == '0') {
				continue;
			}
			bricks[i][j].life = level[i][j] - '0';

			player.currentGoal += bricks[i][j].life;

			bricks[i][j].x = j * bricks[i][j].width;
			bricks[i][j].y = i * bricks[i][j].height;
			bricks[i][j].posX = bricks[i][j].x + bricks[i][j].width / 2;
			bricks[i][j].posY = bricks[i][j].y + bricks[i][j].height / 2;

			string brickTextureName = "img/12864brick";
			string brickLife = std::to_string(bricks[i][j].life);
			brickTextureName.append(brickLife);
			brickTextureName.append(".png");
			bricks[i][j].texture = loadTexture(brickTextureName.c_str());
		}
	}

	for (int i = 0; i < Row; i++) {
		for (int j = 0; j < Column; j++) {
			std::cout << "(" << bricks[i][j].x << ", " << bricks[i][j].y << ") ";
		}
		std::cout << std::endl;
	}

	std::cout << "Total goal: " << player.currentGoal << std::endl;
}

void CHECK_CONDITION() { // feedback: the naming of this function is quite generic, it could have a name that is more representative like "CheckWinState"
						// Also some styling feedback - some functions like this one have all letters uppercase. But others - don't. It's good to follow
						// consitent naming style.
	if (player.currentPoint >= player.currentGoal && inGame) {
		currentLevel += 1;
		inGame = false;
		inWinning = true;
	}

	if (player.life == 0 && inGame) {
		inGame = false;
		isLose = true;
	}
}

void GO_NEXTLEVEL() {
	inGame = true;
	inWinning = false;
	INIT_PLAYER();
	RESET_BALLS();
	INIT_BALL();
	INIT_BRICKS();
}

void RESTART_LEVEL() {
	inGame = true;
	inWinning = false;
	isLose = false;	

	INIT_PLAYER();
	RESET_BALLS();
	INIT_BALL();
	INIT_BRICKS();
}

void NEW_BALL() {
	for (int i = 0; i < BALL_MAX; i++) {
		if (balls[i].isAlive && balls[i].collionCounter >= NumToSpawnNewBall) {
			balls[i].collionCounter %= NumToSpawnNewBall;
			INIT_BALL();
		}
	}
}

void RESET_BALLS() {
	for (int i = 0; i < BALL_MAX; i++) {
		balls[i].isAlive = false;
		balls[i].index = 0;
		balls[i].collionCounter = 0;
		player.numOfBall = 0;
	}
}