#include "Main.h"

int main(int argc, char* args[]) {
	Window window;
	int buttonid = 0;
	if (!window.init()) {
		printf("Failed to initialize!\n");
	}
	else {
		bool quit = false;
		bool newScore = false;
		Screen screen = Screen::Start;
		SDL_Event e;
		SDL_StartTextInput();
		srand((unsigned int) time(NULL));
		Breakout breakout;
		StartScreen startScreen = StartScreen(window.getRenderer());
		EndScreen endScreen = EndScreen(window.getRenderer());
		HighScoreScreen highscore = HighScoreScreen(window.getRenderer());
		SubmitScreen submit = SubmitScreen(window.getRenderer());
		highscore.connectDB();
		while (!quit)
		{
			Action action = Action::NoAction;
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
				switch (screen)
				{
				case Screen::Start:
					action = startScreen.handleEvent(&e);
					break;
				case Screen::Game:
					breakout.getPaddle()->handleEvent(e);
					break;
				case Screen::End:
					action = endScreen.handleEvent(&e);
					break;
				case Screen::HighScore:
					action = highscore.handleEvent(&e);
					break;
				case Screen::Submit:
					action = submit.handleEvent(&e);
				}
			}
			window.clearScreen();
			switch (screen)
			{
			case Screen::Start:
				startScreen.render(window.getRenderer());
				switch (action)
				{
				case Action::NewGame:
					screen = Screen::Game;
					break;
				case Action::Quit:
					quit = true;
					break;
				case Action::Highscore:
					screen = Screen::HighScore;
					highscore.collectHighscores(window.getRenderer());
					break;
				}
				break;
			case Screen::Game:
				breakout.checkNextLevel(window);
				breakout.loadInfoBar(window);
				breakout.renderBricks(window);
				breakout.moveAndRenderPaddle(window);
				if (!breakout.moveAndRenderBall(window) &&
					breakout.CheckIsDead())
				{
					if (highscore.checkNewHighscore(breakout.getScore(), window.getRenderer()))
					{
						screen = Screen::Submit;
					}
					else
					{
						screen = Screen::End;
					}
				}
				break;
			case Screen::End:
				endScreen.render(breakout.getScore(), window.getRenderer());
				switch (action)
				{
				case Action::NewGame:
					breakout.startNewGame();
					screen = Screen::Game;
					break;
				case Action::Quit:
					quit = true;
					break;
				case Action::Highscore:
					screen = Screen::HighScore;
					highscore.collectHighscores(window.getRenderer());
				}
				break;
			case Screen::HighScore:
				highscore.render(window.getRenderer());
				switch (action)
				{
				case Action::NewGame:
					breakout.startNewGame();
					screen = Screen::Game;
					break;
				case Action::Quit:
					quit = true;
					break;
				}
				break;
			case Screen::Submit:
				int score = breakout.getScore();
				submit.render(score, window.getRenderer());
				switch (action)
				{
				case Action::NewGame:
					breakout.startNewGame();
					screen = Screen::Game;
					break;
				case Action::Quit:
					quit = true;
					break;
				case Action::Submit:
					highscore.submitScore(&score, submit.getName());
					highscore.collectHighscores(window.getRenderer());
					screen = Screen::HighScore;
					break;
				}
				break;
			}
			window.updateScreen();
		}
	}
	return 0;
}
