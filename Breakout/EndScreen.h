#pragma once
#include <SDL.h>
#include "Button.h"
#include "Text.h"
#include "Window.h"
#include "Action.h"

class EndScreen
{
public:
	EndScreen(SDL_Renderer* renderer);
	void render(SDL_Renderer* renderer);
	Action handleEvent(SDL_Event* e);
private:
	Text text;
	Button newGame;
	Button quit;
};

