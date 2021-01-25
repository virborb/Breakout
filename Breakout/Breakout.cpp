#include "Breakout.h"

Breakout::Breakout() 
{
	bricks = createBricks();
	ball = Ball(Window::SCREEN_WIDTH / 2 - 7 / 2, Window::SCREEN_HEIGHT - 18, 7);
	nextLevelText = Text(25);
	textColor = { 0, 0, 0xFF };
	lives = TOTAL_LIVES;
	score = 0;
	level = 1;
}

std::vector <Brick> Breakout::createBricks()
{
	int width = Window::SCREEN_WIDTH / 10;
	int height = 40;
	std::vector <Brick> bricks;
	for (int x = 0; x < COLUMS; x++)
	{
		for (int y = 0; y < ROWS; y++)
		{
			SDL_Color color = { rand() % 255, rand() % 255, rand() % 255, 0xFF };
			bricks.push_back(Brick(width * x, height * y + 20, color));
		}
	}
	return bricks;
}

void Breakout::checkNextLevel(Window window)
{
	if (bricks.empty())
	{
		bricks = createBricks();
		ball = Ball(Window::SCREEN_WIDTH / 2 - 7 / 2, Window::SCREEN_HEIGHT - 18, 7);
		ball.setSpeed(1 + (0.10 * level));
		paddle.centerPaddle();
		paddle.increaseVelocity();
		paddle.decreaseWidth();
		level++;
		nextLevelText.loadFromRenderedText("Level " + std::to_string(level), textColor, window.getRenderer());
		nextLevelText.render(Window::SCREEN_WIDTH / 2 - nextLevelText.getWidth() / 2,
			Window::SCREEN_HEIGHT / 2 - nextLevelText.getHeight() / 2, window.getRenderer());
		window.updateScreen();
		SDL_Delay(1000);
		window.clearScreen();
	}
}

Paddle* Breakout::getPaddle()
{
	return &paddle;
}

void Breakout::loadInfoBar(Window window) {
	scoreText.loadFromRenderedText("Score: " + std::to_string(score), textColor, window.getRenderer());
	livesText.loadFromRenderedText("Lives: " + std::to_string(lives), textColor, window.getRenderer());

	scoreText.render(10, 0, window.getRenderer());
	livesText.render(100, 0, window.getRenderer());
}

void Breakout::renderBricks(Window window) {
	for (int i = 0; i < bricks.size(); i++)
	{
		if (!bricks[i].getIsDead())
		{
			SDL_Color color = bricks[i].getColor();
			SDL_SetRenderDrawColor(window.getRenderer(), color.r, color.g, color.b, color.a);
			SDL_RenderFillRect(window.getRenderer(), bricks[i].getRect());
		}
		else
		{
			score += POINTS;
			bricks.erase(bricks.begin() + i);
		}
	}
}

void Breakout::moveAndRenderPaddle(Window window) 
{
	SDL_Color color = paddle.getColor();
	paddle.move();
	SDL_SetRenderDrawColor(window.getRenderer(), color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(window.getRenderer(), paddle.getRect());
}

bool Breakout::moveAndRenderBall(Window window)
{
	if (!ball.move(&bricks, &paddle))
	{
		return false;
	}
	ball.DrawBall(window.getRenderer());
	return true;
}

bool Breakout::CheckIsDead()
{
	if (lives == 0)
	{
		return true;
	}
	lives--;
	double speed = ball.getSpeed();
	ball = Ball(Window::SCREEN_WIDTH / 2 - 7 / 2, Window::SCREEN_HEIGHT - 18, 7);
	ball.setSpeed(speed);
	paddle.centerPaddle();
	return false;
}

void Breakout::startNewGame()
{
	bricks = createBricks();
	level = 1;
	lives = TOTAL_LIVES;
	score = 0;
	ball = Ball(Window::SCREEN_WIDTH / 2 - 7 / 2, Window::SCREEN_HEIGHT - 18, 7);
	paddle = Paddle();
}