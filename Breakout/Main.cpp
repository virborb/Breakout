#include "Main.h"

int main(int argc, char* args[]) {
	Window window;
	if (!window.init()) {
		printf("Failed to initialize!\n");
	}
	else 
	{
		bool quit = false;
		srand((unsigned int) time(NULL));
		SDL_Event e;
		Controller controller = Controller(window.getRenderer());
		while (!quit)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				controller.eventHandler(&e);
			}
			window.clearScreen();
			quit = controller.renderScreen(window.getRenderer(), window);
			window.updateScreen();
		}
		controller.close();
		window.close();
	}
	return 0;
}
