#include <player.h>
#include <projectile.h>
#include <ball.h>
#include <brick.h>
#define PROJECTILE_MAX 20
#define Screen_Width 1024
#define Screen_Height 768
#define Row 8
#define Column 8

extern Player player;
extern Ball ball;
extern Projectile projectiles[PROJECTILE_MAX];
extern Brick bricks[Row][Column];