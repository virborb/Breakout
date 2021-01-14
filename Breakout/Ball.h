#pragma once
#include <SDL.h>
#include <vector>
#include "Window.h"
#include "Brick.h"
#include "Paddle.h"

class Ball
{
public:
	Ball(int centreX, int centreY, int radius);
	void DrawBall(SDL_Renderer* renderer);
	bool move(std::vector <Brick>* bricks, Paddle* paddle);
	bool checkCollision(std::vector <Brick>* bricks);
	bool checkCollision(Paddle* paddle);
	double distanceSquared(double x1, double y1, double x2, double y2);
private:
	static const int VEL = 10;
	int centreX;
	int centreY; 
	int radius;
	int velX; 
	int velY;
};

