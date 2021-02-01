#pragma once
#include <SDL.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <mysql.h>

#include "Text.h"
#include "Button.h"
#include "Window.h"
#include "database.h"

class HighScoreScreen
{
public:
	static const int NO_ACTION = 0;
	static const int NEW_GAME = 1;
	static const int QUIT = 2;
	HighScoreScreen(SDL_Renderer* renderer);
	int handleEvent(SDL_Event* e);
	void render(SDL_Renderer* renderer);
	void connectDB();
	void collectHighscores(SDL_Renderer* renderer);
private:
	struct Highscore
	{
		Text name;
		Text score;
	};
	Text title;
	std::vector <Highscore*> scores;
	Button newGame;
	Button quit;
	MYSQL* conn;
};

