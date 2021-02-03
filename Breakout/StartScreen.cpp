#include "StartScreen.h"

StartScreen::StartScreen(SDL_Renderer* renderer)
{
	SDL_Color color = { 0, 0xFF, 0 };
	title = Text(30);
	title.loadFromRenderedText("BREAKOUT", color, renderer);
	newGame.setText("Start game", color, renderer);
	newGame.setPosition(Window::SCREEN_WIDTH / 2 - newGame.getWidth() / 2, Window::SCREEN_HEIGHT / 2 + 20);
	highscore.setText("Highscores", color, renderer);
	highscore.setPosition(Window::SCREEN_WIDTH / 2 - highscore.getWidth() / 2, Window::SCREEN_HEIGHT / 2 + 45);
	quit.setText("Quit game", color, renderer);
	quit.setPosition(Window::SCREEN_WIDTH / 2 - quit.getWidth() / 2, Window::SCREEN_HEIGHT / 2 + 70);
}

Action StartScreen::handleEvent(SDL_Event* e)
{
	if (newGame.handleEvent(e)) {
		return Action::NewGame;
	}
	else if (quit.handleEvent(e))
	{
		return Action::Quit;
	}
	else if (highscore.handleEvent(e))
	{
		return Action::Highscore;
	}
	return Action::NoAction;
}

void StartScreen::render(SDL_Renderer* renderer)
{
	title.render(Window::SCREEN_WIDTH / 2 - title.getWidth() / 2, Window::SCREEN_HEIGHT / 2 - 50, renderer);
	newGame.render(renderer);
	highscore.render(renderer);
	quit.render(renderer);
}