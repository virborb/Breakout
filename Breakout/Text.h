#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class Text
{
public:
	Text(int fontSize = 15);
	~Text();
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor, SDL_Renderer* renderer);
	void free();
	void render(int x, int y, SDL_Renderer* renderer);
	int getWidth();
	int getHeight();
private:
	const char* FONT_PATH = "font/arial.ttf";
	SDL_Texture* texture;
	TTF_Font* font;
	int width;
	int height;
};

