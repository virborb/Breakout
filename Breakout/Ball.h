#pragma once
#include <SDL.h>

class Ball
{
public:
	Ball(int centreX, int centreY, int radius);
	void DrawBall(SDL_Renderer* renderer);
private:
	static const int VEL = 10;
	int centreX;
	int centreY; 
	int radius;
	int velX; 
	int velY;
};

