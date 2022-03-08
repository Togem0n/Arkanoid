#include <ball.h>
#include <game.h>
#include <engine.h>
#include <draw.h>
#include <SDL_image.h>

#define PI 3.1415926

void Ball::move() {
	x += xSpeed * delta_time;
	y += ySpeed * delta_time;
	posX = x + radius;
	posY = y + radius;
}

void Ball::moveWithPlayer() {
	if (keys[SDL_SCANCODE_D]) {
		x += player.speed * delta_time;
		posX = x + radius;
	}
	if (keys[SDL_SCANCODE_A]) {
		x -= player.speed * delta_time;
		posX = x + radius;
	}
}

void Ball::setSpeedWhenCollideWithPlayer() {

	if ((ball.posY + ball.ySpeed * delta_time + ball.radius >= player.posY) && abs(ball.posX + ball.xSpeed * delta_time - player.posX) <= ball.radius + player.width / 2) {

		// diff range [0, player.width/2] [0, 64]
		float diff = ball.posX - player.posX;
		// ratio range [0, 100]
		float ratio = diff / (player.width / 2);
		// angle range [0, 90] means angle with verticle
		float angle = 90 / ratio;

		xSpeed = xMaxSpeed * ratio;
		ySpeed = -ySpeed;
		
	}
}

void Ball::setSpeedWhenCollideWithWall() {
	if (ball.posX + ball.xSpeed * delta_time + ball.radius >= Screen_Width || ball.posX + ball.xSpeed * delta_time - ball.radius <= 0) {
		ball.xSpeed = - ball.xSpeed;
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "leftright");
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "xSpeed%f", xSpeed);
	}

	if (ball.posY + ball.ySpeed * delta_time + ball.radius >= Screen_Height || ball.posY + ball.ySpeed * delta_time - ball.radius <= 0) {
		ball.ySpeed = -ball.ySpeed;
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "updown");
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "ySpeed%f", ySpeed);
	}
}

void Ball::setSpeedWhenCollideWithBrick() {

	float max_dis = ball.radius + sqrt(pow(bricks[0][0].width, 2) + pow(bricks[0][0].height, 2)) / 2;

	for (int i = 0; i < Row; i++) {
		for (int j = 0; j < Column; j++) {

			if (bricks[i][j].life <= 0) {
				continue;
			}

			// collide ???
			// + ball.ySpeed * delta_time
			float diffX = abs(ball.posX - bricks[i][j].posX);
			float diffY = abs(ball.posY - bricks[i][j].posY);
			float next_diffX = abs(ball.posX + ball.xSpeed * delta_time - bricks[i][j].posX);
			float next_diffY = abs(ball.posY + ball.ySpeed * delta_time - bricks[i][j].posY);

			// why this doesnt work?
			//if ((diffY > ball.radius + bricks[i][j].height / 2) && (diffX <= ball.radius + bricks[i][j].width / 2)) {
			//
			//	if (next_diffY <= ball.radius + bricks[i][j].height / 2) {

			//		ball.ySpeed *= -1;
			//		bricks[i][j].life -= 1;
			//		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "collide top bottom");

			//	}			

			//}
			//else if ((diffX > ball.radius + bricks[i][j].width / 2) && (diffY <= ball.radius + bricks[i][j].height / 2)) {

			//	if (next_diffX <= ball.radius + bricks[i][j].width / 2) {

			//		ball.xSpeed *= -1;
			//		bricks[i][j].life -= 1;
			//		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "collide left right");

			//	}
			//}
			
			// why this work?
			if ((next_diffY <= ball.radius + bricks[i][j].height / 2) && (diffX <= ball.radius + bricks[i][j].width / 2)) {

				ball.ySpeed *= -1;
				bricks[i][j].life -= 1;
				bricks[i][j].getHit = true;
				bricks[i][j].texture = loadTexture("12864brickGetHit.png");
				SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "collide top bottom");
			}
			else if ((next_diffX <= ball.radius + bricks[i][j].width / 2) && (diffY <= ball.radius + bricks[i][j].height / 2)) {

				ball.xSpeed *= -1;
				bricks[i][j].life -= 1;
				bricks[i][j].getHit = true;
				bricks[i][j].texture = loadTexture("12864brickGetHit.png");
				SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "collide left right");
			}

		}
	}
}

void Ball::update() {
	if (isMovingWithPlayer) {
		moveWithPlayer();
	}
	else {
		setSpeedWhenCollideWithPlayer();
		setSpeedWhenCollideWithWall();
		setSpeedWhenCollideWithBrick();
		move();
	}
}

void Ball::draw() {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_Rect rect = { (int)x, (int)y, radius, radius };
	SDL_RenderFillRect(renderer, &rect);
}