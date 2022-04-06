#include <ball.h>
#include <game.h>
#include <engine.h>
#include <draw.h>
#include <init.h>
#include <SDL_image.h>
#include <string>

using std::string;

#define PI 3.1415926

void Ball::move() {
	// feedback: the "common" approach is to call this function as "update", since moving is one of different things that might happen with a ball after the time step.
	// Also delta_time is usually passed to update function as a parameter but not as a global variable. This would make the code more readable and well-structured,
	// since at this moment delta_time is an external thing to the Ball class which also kinda breaks the OOP
	x += xSpeed * delta_time;
	y += ySpeed * delta_time;
	posX = x + radius;
	posY = y + radius;
}

void Ball::moveWithPlayer() {
	// feedback: not sure I fully understand the intent to have a different move function. Could it be combined with the one above perhaps?
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

	if ((posY + ySpeed * delta_time + radius >= player.posY) && abs(posX + xSpeed * delta_time - player.posX) <= radius + player.width / 2) {

		// diff range [0, player.width/2] [0, 64]
		float diff = posX - player.posX;
		// ratio range [0, 100]
		float ratio = diff / (player.width / 2);
		// angle range [0, 90] means angle with verticle
		float angle = 90 / ratio;

		xSpeed = xMaxSpeed * ratio;
		ySpeed = -ySpeed;
		
	}
}

void Ball::setSpeedWhenCollideWithWall() {
	if (posX + xSpeed * delta_time + radius >= Screen_Width || posX + xSpeed * delta_time - radius <= 0) {
		xSpeed = - xSpeed;
		// feedback: quite a lot of commented out code in different places! Would be more readable to remove the comments.
		
		//SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "leftright");
		//SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "xSpeed%f", xSpeed);
	}

	if (posY + ySpeed * delta_time + radius >= Screen_Height || posY + ySpeed * delta_time - radius <= 0) {
		ySpeed = -ySpeed;
		//SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "updown");
		//SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "ySpeed%f", ySpeed);
	}
}

void Ball::setSpeedWhenCollideWithBrick() {

	float max_dis = radius + sqrt(pow(bricks[0][0].width, 2) + pow(bricks[0][0].height, 2)) / 2;

	for (int i = 0; i < Row; i++) {
		for (int j = 0; j < Column; j++) {

			if (bricks[i][j].life <= 0) {
				continue;
			}

			// collide ???
			// + ball.ySpeed * delta_time
			float diffX = abs(posX - bricks[i][j].posX);
			float diffY = abs(posY - bricks[i][j].posY);
			float next_diffX = abs(posX + xSpeed * delta_time - bricks[i][j].posX);
			float next_diffY = abs(posY + ySpeed * delta_time - bricks[i][j].posY);

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
			if ((next_diffY <= radius + bricks[i][j].height / 2) && (diffX <= radius + bricks[i][j].width / 2)) {

				ySpeed *= -1;
				bricks[i][j].life -= 1;
				player.currentPoint += 1;
				collionCounter++;

				string brickTextureName = "img/12864brick";
				string brickLife = std::to_string(bricks[i][j].life);
				brickTextureName.append(brickLife);
				brickTextureName.append(".png");
				bricks[i][j].texture = loadTexture(brickTextureName.c_str());
				
				std::cout << "Current Point: " << int(100*player.currentPoint/player.currentGoal) << "%" << std::endl;

			}
			else if ((next_diffX <= radius + bricks[i][j].width / 2) && (diffY <= radius + bricks[i][j].height / 2)) {

				xSpeed *= -1;
				bricks[i][j].life -= 1;
				player.currentPoint += 1;
				collionCounter++;

				string brickTextureName = "img/12864brick";
				string brickLife = std::to_string(bricks[i][j].life);
				brickTextureName.append(brickLife);
				brickTextureName.append(".png");
				bricks[i][j].texture = loadTexture(brickTextureName.c_str());

				std::cout << "Current point: " << int(100*player.currentPoint/player.currentGoal) << "%" << std::endl;

			}

		}
	}
}

void Ball::checkDead() {
	if ((posY >= player.posY) && abs(posX - player.posX) > radius + player.width / 2) {
		int cnt = 0;
		for (int i = 0; i < BALL_MAX; i++) {
			if (balls[i].isAlive) {
				cnt++;
			}
		}
		if (cnt == 1) {
			resetBall();
			player.life--;
			player.resetTexture();
		}
		else {
			isAlive = false;
			//collionCounter = 0;
		}
	}
}

void Ball::resetBall() {
	x = player.x + player.width / 2 - radius;
	y = player.y - radius * 2;
	collionCounter = 0;
	posX = x + radius;
	posY = y + radius;
	isMovingWithPlayer = true;
}

void Ball::update() {
	if (isMovingWithPlayer) {
		moveWithPlayer();
	}
	else {
		checkDead();
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