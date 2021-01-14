#pragma once
#include <SDL.h>
#include "Window.h"

class Paddle
{
public:
	Paddle();
	SDL_Rect* getRect();
	SDL_Color getColor();
	//Takes key presses and adjusts the paddle's velocity
	void handleEvent(SDL_Event& e);
	void move();
private:
	static const int WIDTH =  100;
	static const int HEIGHT = 5;
	int velocity;
	static const int VEL = 10;
	SDL_Rect rect;
	SDL_Color color;
};

