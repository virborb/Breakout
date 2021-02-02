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
	void renderNewHighscore(SDL_Renderer* renderer);
	void connectDB();
	void collectHighscores(SDL_Renderer* renderer);
	bool checkNewHighscore(int score, SDL_Renderer* renderer);
private:
	struct Highscore
	{
		Text name;
		Text score;
	};
	Text title;
	Text newHighscore;
	Text inputText;
	SDL_Rect inputRect;
	std::string input;
	bool renderInput;
	std::vector <Highscore*> scores;
	Button newGame;
	Button quit;
	Button submit;
	MYSQL* conn;
};

