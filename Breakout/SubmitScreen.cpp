#include "SubmitScreen.h"

SubmitScreen::SubmitScreen(SDL_Renderer* renderer)
{
	SDL_Color color = { 0, 0xFF, 0 };
	newHighscore.loadFromRenderedText("New Highscore, Enter name to submit score.", color, renderer);
	inputRect = { Window::SCREEN_WIDTH / 2 - newGame.getWidth() - 25, Window::SCREEN_HEIGHT / 2, 250, 20 };
	newGame.setText("New game", color, renderer);
	quit.setText("Quit game", color, renderer);
	submit.setText("Submit score", color, renderer);
	renderInput = true;
}

Action SubmitScreen::handleEvent(SDL_Event* e)
{
	if (newGame.handleEvent(e)) {
		return Action::NewGame;
	}
	else if (quit.handleEvent(e))
	{
		return Action::Quit;
	}
	else if (submit.handleEvent(e))
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

void SubmitScreen::render(SDL_Renderer* renderer)
{
	if (renderInput)
	{
		SDL_Color color = { 0, 0xFF, 0 };
		//Text is not empty
		if (input != "")
		{
			//Render new text
			inputText.loadFromRenderedText(input.c_str(), color, renderer);
		}
		//Text is empty
		else
		{
			//Render space texture
			inputText.loadFromRenderedText(" ", color, renderer);
		}
	}
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