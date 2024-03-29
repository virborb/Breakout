#include "SubmitScreen.h"

/**
 * @brief Makes a screen to submit a new highscore.
 * @param renderer The renderer to use.
*/
SubmitScreen::SubmitScreen(SDL_Renderer* renderer)
{
	SDL_Color color = { 0, 0xFF, 0 };
	title = Text(30);
	title.loadFromRenderedText("Game Over", color, renderer);
	inputRect = { Window::SCREEN_WIDTH / 2 - newGame.getWidth() - 25, Window::SCREEN_HEIGHT / 2, 250, 20 };
	newGame.setText("New game", color, renderer);
	quit.setText("Quit game", color, renderer);
	submit.setText("Submit score", color, renderer);
	renderInput = true;
}

/**
 * @brief Handles the button presses on the screen and return what button was pressed
 *        And text input for the name field.
 * @param e The SDL event pointer
 * @return An Action to do next.
*/
Action SubmitScreen::handleEvent(SDL_Event* e)
{
	if (newGame.handleEvent(e)) {
		return Action::NewGame;
	}
	else if (quit.handleEvent(e))
	{
		return Action::Quit;
	}
	else if (submit.handleEvent(e) && !input.empty())
	{
		return Action::Submit;
	}
	if (e->type == SDL_KEYDOWN)
	{
		if (e->key.keysym.sym == SDLK_BACKSPACE && input.length() > 0)
		{
			input.pop_back();
			renderInput = true;
		}
		else if (e->key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
		{
			SDL_SetClipboardText(input.c_str());
		}
		else if (e->key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
		{
			input = SDL_GetClipboardText();
			renderInput = true;
		}
	}
	else if (e->type == SDL_TEXTINPUT)
	{
		if (!(SDL_GetModState() & KMOD_CTRL && (e->text.text[0] == 'c' || e->text.text[0] == 'C' || e->text.text[0] == 'v' || e->text.text[0] == 'V')))
		{
			if (input.size() < 30)
			{
				input += e->text.text;
				renderInput = true;
			}
		}
	}
	return Action::NoAction;
}

/**
 * @brief Render the submit screen.
 * @param renderer The renderer to use.
*/
void SubmitScreen::render(int score, SDL_Renderer* renderer)
{
	SDL_Color color = { 0, 0xFF, 0 };
	if (renderInput)
	{
		if (input != "")
		{
			inputText.loadFromRenderedText(input.c_str(), color, renderer);
		}

		else
		{
			inputText.loadFromRenderedText(" ", color, renderer);
		}
	}
	newHighscore.loadFromRenderedText("Your score is "  + std::to_string(score) +  ", Enter name to submit score.", color, renderer);
	title.render(Window::SCREEN_WIDTH / 2 - title.getWidth() / 2, Window::SCREEN_HEIGHT / 2 - 100, renderer);
	newHighscore.render(Window::SCREEN_WIDTH / 2 - newHighscore.getWidth() / 2, Window::SCREEN_HEIGHT / 2 - 20, renderer);
	inputText.render(Window::SCREEN_WIDTH / 2 - newGame.getWidth() - 20, Window::SCREEN_HEIGHT / 2, renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0xFF, 0, 0xFF);
	SDL_RenderDrawRect(renderer, &inputRect);
	submit.setPosition(Window::SCREEN_WIDTH / 2 - newGame.getWidth() / 2 - submit.getWidth() - 5, Window::SCREEN_HEIGHT / 2 + 25);
	newGame.setPosition(Window::SCREEN_WIDTH / 2 - newGame.getWidth() / 2, Window::SCREEN_HEIGHT / 2 + 25);
	quit.setPosition(Window::SCREEN_WIDTH / 2 + newGame.getWidth() / 2 + 5, Window::SCREEN_HEIGHT / 2 + 25);
	submit.render(renderer);
	newGame.render(renderer);
	quit.render(renderer);
	renderInput = false;
}

/**
 * @brief Gets inputed name from the player.
 * @return The name
*/
std::string SubmitScreen::getName()
{
	return input;
}