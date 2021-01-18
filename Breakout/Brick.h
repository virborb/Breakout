#pragma once
#include <SDL.h>
#include "Window.h"
class Brick
{
public:
	Brick(int x, int y, SDL_Color color);
	SDL_Rect* getRect();
	SDL_Color getColor();
	void setIsDead(bool isdead);
	bool getIsDead();
private:
	static const int width = Window::SCREEN_WIDTH / 10;
	static const int height = 40;
	SDL_Rect rect;
	SDL_Color color;
	bool isDead;
};

