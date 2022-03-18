#include <player.h>
#include <game.h>
#include <SDL_image.h>
#include <ball.h>
#include <string>

using std::string;

void Player::move()
{
	if (keys[SDL_SCANCODE_D]) {
		x += speed * delta_time;
		posX = x + player.width / 2;
	}
	if (keys[SDL_SCANCODE_A]) {
		x -= speed * delta_time;
		posX = x + player.width / 2;
	}

	for (int i = 0; i < BALL_MAX; i++) {
		if (balls[i].isMovingWithPlayer && keys[SDL_SCANCODE_W] && balls[i].isAlive) {
			SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "debug");
			balls[i].isMovingWithPlayer = false;
		}
	}
}

void Player::shoot()
{
	if (keys[SDL_SCANCODE_SPACE]) {
		Projectile& projectile = projectiles[next_proectile_index];
		projectile.alive = true;
		projectile.x = x;
		projectile.y = y;
		next_proectile_index++;
		next_proectile_index %= PROJECTILE_MAX;
	}
}

void Player::draw()
{
	SDL_SetRenderDrawColor(renderer, 150, 25, 40, 255);
	SDL_Rect rect = { (int)x, (int)y, width, height };
	SDL_RenderFillRect(renderer, &rect);

}

void Player::drawBall() {
	SDL_SetRenderDrawColor(renderer, 150, 25, 40, 255);

	SDL_RenderDrawPoint(renderer, 50, 50);
}

void Player::resetTexture() {
	string playerTextureName = "player";
	string playerLife = std::to_string(player.life);
	playerTextureName.append(playerLife);
	playerTextureName.append(".png");
	player.texture = loadTexture(playerTextureName.c_str());
}