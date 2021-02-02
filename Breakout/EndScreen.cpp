#include "EndScreen.h"

EndScreen::EndScreen(SDL_Renderer* renderer)
{
	SDL_Color color = { 0, 0xFF, 0 };
	text.loadFromRenderedText("Game Over. Start new game or quit game?", color, renderer);
	newGame.setText("New game", color, renderer);
	newGame.setPosition(Window::SCREEN_WIDTH / 2 - newGame.getWidth() - 10, Window::SCREEN_HEIGHT / 2 + text.getHeight());
	quit.setText("Quit game", color, renderer);
	quit.setPosition(Window::SCREEN_WIDTH / 2 + 10, Window::SCREEN_HEIGHT / 2 + text.getHeight());
}

Action EndScreen::handleEvent(SDL_Event* e)
{
	if (newGame.handleEvent(e)) {
		return Action::NewGame;
	}
	else if (quit.handleEvent(e))
	{
		return Action::Quit;
	}
	return Action::NoAction;
}

void EndScreen::render(SDL_Renderer* renderer)
{
	text.render(Window::SCREEN_WIDTH / 2 - text.getWidth() / 2, Window::SCREEN_HEIGHT / 2, renderer);
	newGame.render(renderer);
	quit.render(renderer);
}

Button* EndScreen::getButtons() 
{
	Button buttons[] = { newGame, quit };
	return buttons;
}
