#pragma once
#include <SDL.h>
#include <vector>

#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"
#include "Text.h"
#include "Window.h"

class Breakout
{
public:
	Breakout();
	std::vector <Brick> createBricks();
	void checkNextLevel(Window window);
	Paddle* getPaddle();
	void loadInfoBar(Window window);
	void renderBricks(Window window);
	void moveAndRenderPaddle(Window window);
	bool moveAndRenderBall(Window window);
	bool CheckIsDead();
	void startNewGame();
private:
	static const int COLUMS = 10;
	static const int ROWS = 5;
	static const int TOTAL_LIVES = 3;
	static const int POINTS = 10;

	std::vector <Brick> bricks;
	Paddle paddle;
	Ball ball;
	Text scoreText;
	Text livesText;
	Text nextLevelText;
	SDL_Color textColor;
	int lives;
	int score;
	int level;
};

