#include "Controller.h"

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

void Controller::close()
{
	highscore.closeDB();
	SDL_StopTextInput();
}

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