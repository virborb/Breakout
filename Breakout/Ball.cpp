#include "Ball.h"

Ball::Ball(int centreX, int centreY, int radius)
{
	this->centreX = centreX;
	this->centreY = centreY;
	this->radius = radius;
	velX = VEL;
	velY = VEL;
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

bool Ball::move(std::vector <Brick>* bricks, Paddle* paddle)
{
	//Move the dot left or right
	centreX += velX;

	//If the dot collided or went too far to the left or right
	if ((centreX - radius < 0) || (centreX + radius > Window::SCREEN_WIDTH) || checkCollision(bricks) || checkCollision(paddle))
	{
		//Move back
		centreX -= velX;
		velX = -velX;
	}

	//Move the dot up or down
	centreY += velY;

	if ((centreY + radius > Window::SCREEN_HEIGHT)) 
	{
		return false;
	}

	//If the dot collided or went too far up or down
	if ((centreY - radius < 0) || (centreY + radius > Window::SCREEN_HEIGHT) || checkCollision(bricks) || checkCollision(paddle))
	{
		//Move back
		centreY -= velY;
		velY = -velY;
	}
	return true;
}

bool Ball::checkCollision(std::vector <Brick>* bricks)
{
	for (int i = 0; i < bricks->size(); i++)
	{
		//Closest point on collision box
		int cX, cY;
		SDL_Rect* b = bricks->operator[](i).getRect();

		//Find closest x offset
		if (centreX < b->x)
		{
			cX = b->x;
		}
		else if (centreX > b->x + b->w)
		{
			cX = b->x + b->w;
		}
		else
		{
			cX = centreX;
		}
		//Find closest y offset
		if (centreY < b->y)
		{
			cY = b->y;
		}
		else if (centreY > b->y + b->h)
		{
			cY = b->y + b->h;
		}
		else
		{
			cY = centreY;
		}

		//If the closest point is inside the circle
		if (distanceSquared(centreX, centreY, cX, cY) < radius * radius)
		{
			//This box and the circle have collided
			bricks->erase(bricks->begin() + i);
			return true;
		}
	}

	//If the shapes have not collided
	return false;
}

bool Ball::checkCollision(Paddle* paddle)
{
	//Closest point on collision box
	int cX, cY;
	SDL_Rect* b = paddle->getRect();

	//Find closest x offset
	if (centreX < b->x)
	{
		cX = b->x;
	}
	else if (centreX > b->x + b->w)
	{
		cX = b->x + b->w;
	}
	else
	{
		cX = centreX;
	}
	//Find closest y offset
	if (centreY < b->y)
	{
		cY = b->y;
	}
	else if (centreY > b->y + b->h)
	{
		cY = b->y + b->h;
	}
	else
	{
		cY = centreY;
	}

	//If the closest point is inside the circle
	if (distanceSquared(centreX, centreY, cX, cY) < radius * radius)
	{
		//This box and the circle have collided
		return true;
	}


	//If the shapes have not collided
	return false;
}

double Ball::distanceSquared(double x1, double y1, double x2, double y2)
{
	double deltaX = x2 - x1;
	double deltaY = y2 - y1;
	return deltaX * deltaX + deltaY * deltaY;
}