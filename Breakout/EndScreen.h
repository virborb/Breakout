#pragma once
#include <SDL.h>
#include "Button.h"
#include "Text.h"
#include "Window.h"
class EndScreen
{
public:
	static const int NO_ACTION = 0;
	static const int NEW_GAME = 1;
	static const int QUIT = 2;
	EndScreen(SDL_Renderer* renderer);
	void render(SDL_Renderer* renderer);
	int handleEvent(SDL_Event* e);
	Button* getButtons();
private:
	Text text;
	Button newGame;
	Button quit;
};

