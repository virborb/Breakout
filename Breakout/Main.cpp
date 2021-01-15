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
		std::vector <Brick> bricks = createBricks();
		Paddle paddle;
		Ball ball = Ball(Window::SCREEN_WIDTH / 2 - 7 / 2, Window::SCREEN_HEIGHT - 18, 7);
		Text text;
		int buttonid = 0;
		SDL_Color textColor = { 0, 0, 0 };
		while (!quit)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
				paddle.handleEvent(e);
			}
			window.clearScreen();

			if (!text.loadFromRenderedText("Score: 45      Lives: 3", textColor, window.getRenderer()))
			{
				printf("Failed to render text texture!\n");
			}

			for (int i = 0; i < bricks.size(); i++)
			{
				SDL_Color color = bricks[i].getColor();
				SDL_SetRenderDrawColor(window.getRenderer(), color.r, color.g, color.b, color.a);
				SDL_RenderFillRect(window.getRenderer(), bricks[i].getRect());
			}
			SDL_Color color = paddle.getColor();
			SDL_SetRenderDrawColor(window.getRenderer(), color.r, color.g, color.b, color.a);
			paddle.move();
			if (!ball.move(&bricks, &paddle))
			{
				SDL_ShowMessageBox(&messageboxdata, &buttonid);
				if (buttonid == 0) {
					break;
				}
				bricks = createBricks();
				ball = Ball(Window::SCREEN_WIDTH / 2 - 7 / 2, Window::SCREEN_HEIGHT - 18, 7);
				paddle = Paddle();
			}
			SDL_RenderFillRect(window.getRenderer(), paddle.getRect());
			ball.DrawBall(window.getRenderer());
			text.render(10, 0, window.getRenderer());

			window.updateScreen();
		}
	}
	return 0;
}

std::vector <Brick> createBricks()
{
	int width = Window::SCREEN_WIDTH / 10;
	int height = 40;
	std::vector <Brick> bricks;
	for (int x = 0; x < COLUMS; x++)
	{
		for (int y = 0; y < ROWS; y++)
		{
			SDL_Color color = { rand() % 255, rand() % 255, rand() % 255, 0xFF };
			bricks.push_back(Brick(width * x, height * y+20, color));
		}
	}
	return bricks;
}
