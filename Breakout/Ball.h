#pragma once
#include <SDL.h>
#include <vector>
#include "Window.h"
#include "Brick.h"
#include "Paddle.h"

class Ball
{
public:
	Ball();
	Ball(int centreX, int centreY, double radius);
	void DrawBall(SDL_Renderer* renderer);
	bool move(std::vector <Brick>* bricks, Paddle* paddle);
	bool checkCollision(std::vector <Brick>* bricks);
	bool checkCollision(Paddle* paddle);
	double distanceSquared(double x1, double y1, double x2, double y2);
	double getSpeed();
	void setSpeed(double speed);
private:
	static const int VEL = 5;
	SDL_Color color;
	int centreX;
	int centreY; 
	double radius;
	double velX; 
	double velY;
	double speed;
};

