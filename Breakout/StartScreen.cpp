#include "StartScreen.h"

StartScreen::StartScreen(SDL_Renderer* renderer)
{
	SDL_Color color = { 0, 0xFF, 0 };
	text.loadFromRenderedText("BREAKOUT", color, renderer);
	newGame.setText("Start game", color, renderer);
	newGame.setPosition(Window::SCREEN_WIDTH / 2 - newGame.getWidth() - 10, Window::SCREEN_HEIGHT / 2 + text.getHeight());
	quit.setText("Quit game", color, renderer);
	quit.setPosition(Window::SCREEN_WIDTH / 2 + 10, Window::SCREEN_HEIGHT / 2 + text.getHeight());
}

int StartScreen::handleEvent(SDL_Event* e)
{
	if (newGame.handleEvent(e)) {
		return NEW_GAME;
	}
	else if (quit.handleEvent(e))
	{
		return QUIT;
	}
	return NO_ACTION;
}

void StartScreen::render(SDL_Renderer* renderer)
{
	text.render(Window::SCREEN_WIDTH / 2 - text.getWidth() / 2, Window::SCREEN_HEIGHT / 2, renderer);
	newGame.render(renderer);
	quit.render(renderer);
}