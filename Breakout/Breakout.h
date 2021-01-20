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
	int buttonid;
	SDL_Color textColor;
	int lives;
	int score;
	int level;

	const SDL_MessageBoxButtonData buttons[2] = {
		{ 0, 0, "no" },
		{ 0, 1, "yes" }
	};
	const SDL_MessageBoxColorScheme colorScheme = {
		{ 
			/* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
			{ 255,   0,   0 },
			/* [SDL_MESSAGEBOX_COLOR_TEXT] */
			{   0, 255,   0 },
			/* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
			{ 255, 255,   0 },
			/* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
			{   0,   0, 255 },
			/* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
			{ 255,   0, 255 }
		}
	};
	const SDL_MessageBoxData messageboxdata = {
		SDL_MESSAGEBOX_INFORMATION,
		NULL,
		"Game Over",
		"Game over, Start a new game?",
		SDL_arraysize(buttons),
		buttons,
		&colorScheme
	};
};

