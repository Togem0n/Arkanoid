#include <game.h>

Player player;
//Ball ball;
Ball balls[BALL_MAX];
Projectile projectiles[PROJECTILE_MAX];
Brick bricks[Row][Column];
int currentLevel = 1;
bool inGame = true;
bool inWinning = false;
bool isLose = false;