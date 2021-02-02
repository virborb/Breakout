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
#include "Action.h"

class HighScoreScreen
{
public:
	HighScoreScreen(SDL_Renderer* renderer);
	Action handleEvent(SDL_Event* e);
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
	std::vector <Highscore*> scores;
	Button newGame;
	Button quit;
	MYSQL* conn;
};

