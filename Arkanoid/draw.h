#pragma once
#include <engine.h>
#include <SDL_image.h>

void prepareScene(void);
void presentScene(void);

SDL_Texture* loadTexture(const char* filename);
void blit(SDL_Texture* texture, int x, int y);

void Draw_Player();

void Draw_Ball();

void Draw_Bricks();

void Draw_Win();

void Draw_Lose();