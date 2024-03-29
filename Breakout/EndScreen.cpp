#include "EndScreen.h"

/**
 * @brief Creates a end screen uses when losing with no new highscore
 * @param renderer The renderer to use.
*/
EndScreen::EndScreen(SDL_Renderer* renderer)
{
	SDL_Color color = { 0, 0xFF, 0 };
	title = Text(30);
	title.loadFromRenderedText("Game Over", color, renderer);
	newGame.setText("New game", color, renderer);
	newGame.setPosition(Window::SCREEN_WIDTH / 2 - newGame.getWidth() - highscore.getWidth() / 2 - 5, Window::SCREEN_HEIGHT / 2 + 20);
	highscore.setText("Highscores", color, renderer);
	highscore.setPosition(Window::SCREEN_WIDTH / 2 - highscore.getWidth() / 2 , Window::SCREEN_HEIGHT / 2 + 20);
	quit.setText("Quit game", color, renderer);
	quit.setPosition(Window::SCREEN_WIDTH / 2  + highscore.getWidth() / 2 + 5, Window::SCREEN_HEIGHT / 2 + 20);
}

/**
 * @brief Handles the button presses on the screen and return what button was pressed.
 * @param e The SDL event pointer
 * @return An Action to do next.
*/
Action EndScreen::handleEvent(SDL_Event* e)
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

/**
 * @brief Render the end screen.
 * @param score The score to render.
 * @param renderer The renderer to use.
*/
void EndScreen::render(int score, SDL_Renderer* renderer)
{
	SDL_Color color = { 0, 0xFF, 0 };
	title.render(Window::SCREEN_WIDTH / 2 - title.getWidth() / 2, Window::SCREEN_HEIGHT / 2 - 100, renderer);
	text.loadFromRenderedText("Your score is " + std::to_string(score), color, renderer);
	text.render(Window::SCREEN_WIDTH / 2 - text.getWidth() / 2, Window::SCREEN_HEIGHT / 2, renderer);
	newGame.render(renderer);
	highscore.render(renderer);
	quit.render(renderer);
}
