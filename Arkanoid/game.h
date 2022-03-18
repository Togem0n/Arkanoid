#include <player.h>
#include <projectile.h>
#include <ball.h>
#include <brick.h>
#define PROJECTILE_MAX 20
#define BALL_MAX 100
#define Screen_Width 1024
#define Screen_Height 768
#define Row 10
#define Column 8
#define NumToSpawnNewBall 20

extern Player player;
//extern Ball ball;
extern Ball balls[BALL_MAX];
extern Projectile projectiles[PROJECTILE_MAX];
extern Brick bricks[Row][Column];
extern int currentLevel;
extern bool inGame;
extern bool inWinning;
extern bool isLose;