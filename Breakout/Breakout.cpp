#include "Breakout.h"

/**
 * @brief Creates the game screen with bricks, ball and paddle
*/
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


/**
 * @brief Creates all bricks for a game level with random colors.
 * @return The bricks
*/
std::vector <Brick> Breakout::createBricks()
{
	int width = Window::SCREEN_WIDTH / 10;
	int height = 40;
	std::vector <Brick> bricks;
	for (int x = 0; x < COLUMS; x++)
	{
		for (int y = 0; y < ROWS; y++)
		{
			SDL_Color color = { static_cast<Uint8>(rand() % 255), static_cast<Uint8>(rand() % 255), static_cast<Uint8>(rand() % 255), 0xFF };
			bricks.push_back(Brick(width * x, height * y + 20, color));
		}
	}
	return bricks;
}

/**
 * @brief Checks if next level should start.
 * @param window the Window to render on.
*/
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

/**
 * @brief Gets the paddle
 * @return The paddle
*/
Paddle* Breakout::getPaddle()
{
	return &paddle;
}
/**
 * @brief Loads the top info on lives and score.
 * @param window The window to render on.
*/
void Breakout::loadInfoBar(Window window) {
	scoreText.loadFromRenderedText("Score: " + std::to_string(score), textColor, window.getRenderer());
	livesText.loadFromRenderedText("Lives: " + std::to_string(lives), textColor, window.getRenderer());

	scoreText.render(10, 0, window.getRenderer());
	livesText.render(100, 0, window.getRenderer());
}

/**
 * @brief Render the bricks on the screen.
 * @param window The window to render on.
*/
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

/**
 * @brief Moves and renders the paddle on the screen.
 * @param window The window to render on.
*/
void Breakout::moveAndRenderPaddle(Window window) 
{
	SDL_Color color = paddle.getColor();
	paddle.move();
	SDL_SetRenderDrawColor(window.getRenderer(), color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(window.getRenderer(), paddle.getRect());
}

/**
 * @brief Moves and render the ball. Returns false if ball hits bottom otherwise true.
 * @param window The window to render on.
 * @return true if ball didn't hit the bottom otherwise false.
*/
bool Breakout::moveAndRenderBall(Window window)
{
	if (!ball.move(&bricks, &paddle))
	{
		return false;
	}
	ball.DrawBall(window.getRenderer());
	return true;
}


/**
 * @brief Checks if game is over.
 * @return true if game over otherwise false.
*/
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

/**
 * @brief Start a new game.
*/
void Breakout::startNewGame()
{
	bricks = createBricks();
	level = 1;
	lives = TOTAL_LIVES;
	score = 0;
	ball = Ball(Window::SCREEN_WIDTH / 2 - 7 / 2, Window::SCREEN_HEIGHT - 18, 7);
	paddle = Paddle();
}

/**
 * @brief Returns the current score.
 * @return The score.
*/
int Breakout::getScore()
{
	return score;
}