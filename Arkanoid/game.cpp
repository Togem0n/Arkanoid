#include <game.h>

// feedback: a similar comment to what I did in engine.cpp. Would be nice to see some logic here instead of global vars declarations.

Player player;
//Ball ball;
Ball balls[BALL_MAX];
Projectile projectiles[PROJECTILE_MAX];
Brick bricks[Row][Column];
int currentLevel = 1;
bool inGame = true;
bool inWinning = false;
bool isLose = false;