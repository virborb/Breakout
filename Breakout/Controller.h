#pragma once

#include "Breakout.h"
#include "EndScreen.h"
#include "StartScreen.h"
#include "HighScoreScreen.h"
#include "SubmitScreen.h"
#include "Action.h"

class Controller
{
public:
	Controller(SDL_Renderer* renderer);
	void eventHandler(SDL_Event* e);
	void close();
	bool renderScreen(SDL_Renderer* renderer, Window window);
private:
	enum class Screen { Start, Game, End, HighScore, Submit };
	bool renderStart(SDL_Renderer* renderer);
	bool renderGame(SDL_Renderer* renderer, Window window);
	bool renderEnd(SDL_Renderer* renderer);
	bool renderHighscore(SDL_Renderer* renderer);
	bool renderSubmit(SDL_Renderer* renderer);
	Breakout breakout;
	StartScreen startScreen;
	EndScreen endScreen;
	HighScoreScreen highscore;
	SubmitScreen submit;
	Screen screen;
	Action action;

};

