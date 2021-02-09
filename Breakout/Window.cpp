#include "Window.h"

/**
 * @brief Constructs a new Window.
*/
Window::Window() {
	window = NULL;
	renderer = NULL;
}

/**
 * @brief Initialize SDL and creates window and renderer for SDL.
 *        Initialize SDL_image and SDL_ttf.
 * @return true on successful initialisation otherwise false.
*/
bool Window::init() {
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

/**
 * @brief Destroys renderer and window and close all SDL libraries.
*/
void Window::close()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

/**
 * @brief Clear anything render on the screen
*/
void Window::clearScreen() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
	SDL_RenderClear(renderer);
}

/**
 * @brief Update screen with rendering preformed.
*/
void Window::updateScreen() {
	SDL_RenderPresent(renderer);
}

/**
 * @brief Gets the window..
 * @return The window
*/
SDL_Window* Window::getWindow() {
	return window;
}

/**
 * @brief Gets the Renderer
 * @return The renderer
*/
SDL_Renderer* Window::getRenderer() {
	return renderer;
}
