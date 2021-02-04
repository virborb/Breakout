#include "Ball.h"

Ball::Ball()
{
	Ball(0, 0, 0);
}

Ball::Ball(int centreX, int centreY, double radius)
{
	this->centreX = centreX;
	this->centreY = centreY;
	this->radius = radius;
	color = { 0xFF, 0x0, 0x0, 0xFF };
	velX = 1 + (double)(rand() %  VEL/2);
	velY = -VEL;
	speed = 1;
}

void Ball::DrawBall(SDL_Renderer* renderer)
{
	const int diameter = static_cast<int>(radius * 2);

	int x = static_cast<int>(radius - 1);
	int y = 0;
	int tx = 1;
	int ty = 1;
	int error = (tx - diameter);

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

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
	centreX += static_cast<int>(velX);

	if ((centreX - radius < 0) || (centreX + radius > Window::SCREEN_WIDTH) || checkCollision(bricks) || checkCollision(paddle))
	{
		centreX -= static_cast<int>(velX);
		velX = -velX;
	}

	centreY += static_cast<int>(velY);

	if ((centreY + radius > Window::SCREEN_HEIGHT)) 
	{
		return false;
	}

	if ((centreY - radius < 0) || checkCollision(bricks) || checkCollision(paddle))
	{
		centreY -= static_cast<int>(velY);
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

		if (distanceSquared(centreX, centreY, cX, cY) < radius * radius)
		{
			bricks->operator[](i).setIsDead(true);
			return true;
		}
	}

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

	if (distanceSquared(centreX, centreY, cX, cY) < radius * radius)
	{
		int deltaX = ((centreX - b->x) / 10) - 5;
		if (deltaX == 0)
		{
			deltaX++;
		}
		velX = deltaX * speed;
		return true;
	}


	return false;
}

double Ball::distanceSquared(double x1, double y1, double x2, double y2)
{
	double deltaX = x2 - x1;
	double deltaY = y2 - y1;
	return deltaX * deltaX + deltaY * deltaY;
}

double Ball::getSpeed()
{
	return speed;
}

void Ball::setSpeed(double speed)
{
	this->speed = speed;
	velX = velX * speed;
	velY = velY * speed;
}