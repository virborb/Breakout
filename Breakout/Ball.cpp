#include "Ball.h"

Ball::Ball(int centreX, int centreY, int radius)
{
	this->centreX = centreX;
	this->centreY = centreY;
	this->radius = radius;
}

void Ball::DrawBall(SDL_Renderer* renderer)
{
	const int diameter = (radius * 2);

	int x = (radius - 1);
	int y = 0;
	int tx = 1;
	int ty = 1;
	int error = (tx - diameter);

	while (x >= y)
	{
		for (int i = 0; i <= x; i++)
		{
			SDL_RenderDrawPoint(renderer, centreX + i, centreY - y);
			SDL_RenderDrawPoint(renderer, centreX + i, centreY + y);
			SDL_RenderDrawPoint(renderer, centreX - i, centreY - y);
			SDL_RenderDrawPoint(renderer, centreX - i, centreY + y);
		}
		for (int i = 0; i <= y; i++)
		{
			SDL_RenderDrawPoint(renderer, centreX + i, centreY - x);
			SDL_RenderDrawPoint(renderer, centreX + i, centreY + x);
			SDL_RenderDrawPoint(renderer, centreX - i, centreY - x);
			SDL_RenderDrawPoint(renderer, centreX - i, centreY + x);
		}

		if (error <= 0)
		{
			++y;
			error += ty;
			ty += 2;
		}

		if (error > 0)
		{
			--x;
			tx += 2;
			error += (tx - diameter);
		}
	}
}