#pragma once
#include <SDL.h>

#include "Text.h"
#include "Button.h"
#include "Window.h"
#include "Action.h"

class SubmitScreen
{
public:
	SubmitScreen(SDL_Renderer* renderer);
	Action handleEvent(SDL_Event* e);
	void render(SDL_Renderer* renderer);
private:
	Text newHighscore;
	Text inputText;
	SDL_Rect inputRect;
	std::string input;
	bool renderInput;
	Button newGame;
	Button quit;
	Button submit;
};

