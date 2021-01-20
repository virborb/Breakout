#include "Main.h"

int main(int argc, char* args[]) {
	Window window;

	if (!window.init()) {
		printf("Failed to initialize!\n");
	}
	else {
		bool quit = false;
		SDL_Event e;
		srand((unsigned int) time(NULL));
		Breakout breakout;
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
			if (!breakout.moveAndRenderBall(window))
			{
				break;
			}

			window.updateScreen();
		}
	}
	return 0;
}
