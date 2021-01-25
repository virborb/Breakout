#include "Main.h"

int main(int argc, char* args[]) {
	Window window;
	int buttonid = 0;
	if (!window.init()) {
		printf("Failed to initialize!\n");
	}
	else {
		bool quit = false;
		SDL_Event e;
		srand((unsigned int) time(NULL));
		Breakout breakout;
		EndScreen endScreen = EndScreen(window.getRenderer());
		while (!quit)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
				breakout.getPaddle()->handleEvent(e);
			}
			window.clearScreen();

			breakout.checkNextLevel(window);
			breakout.loadInfoBar(window);
			breakout.renderBricks(window);
			breakout.moveAndRenderPaddle(window);
			if (!breakout.moveAndRenderBall(window) &&
				breakout.CheckIsDead())
			{
				window.clearScreen();
				endScreen.render(window.getRenderer());
				window.updateScreen();
				while (SDL_PollEvent(&e) != 0)
				{
					switch (endScreen.handleEvent(&e))
					{
					case EndScreen::NEW_GAME:
						breakout.startNewGame();
						break;
					case EndScreen::QUIT:
						quit = true;
						break;
					}
				}
			}

			window.updateScreen();
		}
	}
	return 0;
}
