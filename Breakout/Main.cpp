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
		highscore.connectDB();
		while (!quit)
		{
			int action = 0;
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
				}
			}
			window.clearScreen();
			switch (screen)
			{
			case Screen::Start:
				startScreen.render(window.getRenderer());
				switch (action)
				{
				case StartScreen::NEW_GAME:
					screen = Screen::Game;
					break;
				case StartScreen::QUIT:
					quit = true;
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
					screen = Screen::HighScore;
					newScore = highscore.checkNewHighscore(breakout.getScore(), window.getRenderer());
					highscore.collectHighscores(window.getRenderer());
				}
				break;
			case Screen::End:
				endScreen.render(window.getRenderer());
				switch (action)
				{
				case EndScreen::NEW_GAME:
					breakout.startNewGame();
					screen = Screen::Game;
					break;
				case EndScreen::QUIT:
					quit = true;
					break;
				}
				break;
			case Screen::HighScore:
				if (newScore)
				{
					highscore.renderNewHighscore(window.getRenderer());
				}
				else
				{
					highscore.render(window.getRenderer());
				}
				switch (action)
				{
				case EndScreen::NEW_GAME:
					breakout.startNewGame();
					screen = Screen::Game;
					break;
				case EndScreen::QUIT:
					quit = true;
					break;
				}
				break;
			}
			window.updateScreen();
		}
	}
	return 0;
}
