#include "Controller.h"

/**
 * @brief Creates a controller which selects what screen to
          render and handles input from user.
 * @param renderer The renderer to use.
*/
Controller::Controller(SDL_Renderer* renderer) :
	startScreen{ renderer },
	endScreen{ renderer },
	highscore{ renderer },
	submit{ renderer }
{
	highscore.connectDB();
	screen = Screen::Start;
	action = Action::NoAction;
	SDL_StartTextInput();
}

/**
 * @brief Closes Database and stop text input.
*/
void Controller::close()
{
	highscore.closeDB();
	SDL_StopTextInput();
}

/**
 * @brief Handles events from the user.
 * @param e The SDL event pointer.
*/
void Controller::eventHandler(SDL_Event* e)
{
	action = Action::NoAction;
	if (e->type == SDL_QUIT)
	{
		action = Action::Quit;
		return;
	}
	switch (screen)
	{
	case Screen::Start:
		action = startScreen.handleEvent(e);
		break;
	case Screen::Game:
		breakout.getPaddle()->handleEvent(e);
		break;
	case Screen::End:
		action = endScreen.handleEvent(e);
		break;
	case Screen::HighScore:
		action = highscore.handleEvent(e);
		break;
	case Screen::Submit:
		action = submit.handleEvent(e);
	}
}

/**
 * @brief Checks which screen to render and returns true if game should close otherwise false.
 * @param renderer The renderer to use.
 * @param window The window to render on.
 * @return true if game should close otherwise false.
*/
bool Controller::renderScreen(SDL_Renderer* renderer, Window window)
{
	switch (screen)
	{
	case Screen::Start:
		return renderStart(renderer);
	case Screen::Game:
		return renderGame(renderer, window);
	case Screen::End:
		return renderEnd(renderer);
	case Screen::HighScore:
		return renderHighscore(renderer);
	case Screen::Submit:
		return renderSubmit(renderer);
	}
	return false;
}

/**
 * @brief Render start screen and check for actions from user.
 * @param renderer The renderer to use.
 * @return true if game should close otherwise false.
*/
bool Controller::renderStart(SDL_Renderer* renderer) {
	startScreen.render(renderer);
	switch (action)
	{
	case Action::NewGame:
		screen = Screen::Game;
		break;
	case Action::Quit:
		return true;
		break;
	case Action::Highscore:
		screen = Screen::HighScore;
		highscore.collectHighscores(renderer);
		break;
	}
	return false;
}

/**
 * @brief Render game screen and check for actions from user.
 * @param renderer The renderer to use.
 * @param window The window to render on.
 * @return true if game should close otherwise false.
*/
bool Controller::renderGame(SDL_Renderer* renderer, Window window)
{
	breakout.checkNextLevel(window);
	breakout.loadInfoBar(window);
	breakout.renderBricks(window);
	breakout.moveAndRenderPaddle(window);
	if (!breakout.moveAndRenderBall(window) &&
		breakout.CheckIsDead())
	{
		if (highscore.checkNewHighscore(breakout.getScore(), renderer))
		{
			screen = Screen::Submit;
		}
		else
		{
			screen = Screen::End;
		}
	}
	return (action == Action::Quit);
}

/**
 * @brief Render end screen and check for actions from user.
 * @param renderer The renderer to use.
 * @return true if game should close otherwise false.
*/
bool Controller::renderEnd(SDL_Renderer* renderer)
{
	endScreen.render(breakout.getScore(), renderer);
	switch (action)
	{
	case Action::NewGame:
		breakout.startNewGame();
		screen = Screen::Game;
		break;
	case Action::Quit:
		return true;
		break;
	case Action::Highscore:
		screen = Screen::HighScore;
		highscore.collectHighscores(renderer);
	}
	return false;
}

/**
 * @brief Render highscore screen and check for actions from user.
 * @param renderer The renderer to use.
 * @return true if game should close otherwise false.
*/
bool Controller::renderHighscore(SDL_Renderer* renderer)
{
	highscore.render(renderer);
	switch (action)
	{
	case Action::NewGame:
		breakout.startNewGame();
		screen = Screen::Game;
		break;
	case Action::Quit:
		return true;
		break;
	}
	return false;
}

/**
 * @brief Render submit screen and check for actions from user.
 * @param renderer The renderer to use.
 * @return true if game should close otherwise false.
*/
bool Controller::renderSubmit(SDL_Renderer* renderer)
{
	int score = breakout.getScore();
	submit.render(score, renderer);
	switch (action)
	{
	case Action::NewGame:
		breakout.startNewGame();
		screen = Screen::Game;
		break;
	case Action::Quit:
		return true;
		break;
	case Action::Submit:
		highscore.submitScore(&score, submit.getName());
		highscore.collectHighscores(renderer);
		screen = Screen::HighScore;
		break;
	}
	return false;
}