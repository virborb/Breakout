#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class Text
{
public:
	Text();
	~Text();
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor, SDL_Renderer* renderer);
	void free();
	void render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	int getWidth();
	int getHeight();
private:
	static const int FONT_SIZE = 15;
	SDL_Texture* texture;
	TTF_Font* font;
	int width;
	int height;
};
