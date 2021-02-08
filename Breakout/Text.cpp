#include "Text.h"

/**
 * @brief Creates a text area with given font size. 
 * @param fontSize The font size(default 15).
*/
Text::Text(int fontSize)
{
	texture = NULL;
	width = 0;
	height = 0;
	font = TTF_OpenFont(FONT_PATH, fontSize);
	if (font == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
	}
}

/**
 * @brief Deconstructs text.
*/
Text::~Text()
{
	free();
}

/**
 * @brief Loads a string of text with given color
 * @param textureText The text to load.
 * @param textColor The color of the text.
 * @param renderer The renderer to use.
 * @return true if it was successfully create otherwise false.
*/
bool Text::loadFromRenderedText(std::string textureText, SDL_Color textColor, SDL_Renderer* renderer)
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		texture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (texture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			width = textSurface->w;
			height = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}

	//Return success
	return texture != NULL;
}

/**
 * @brief Render a string of text to the screen.
 * @param x The x cordinate
 * @param y The y cordinate
 * @param renderer The renderer to use.
*/
void Text::render(int x, int y, SDL_Renderer* renderer)
{
	SDL_Rect renderQuad = { x, y, width, height };
	SDL_RenderCopyEx(renderer, texture, NULL, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);
}

/**
 * @brief Gets Text width.
 * @return The width
*/
int Text::getWidth()
{
	return width;
}

/**
 * @brief Gets Text height.
 * @return The height.
*/
int Text::getHeight()
{
	return height;
}

/**
 * @brief Frees texture if it exists.
*/
void Text::free()
{
	if (texture != NULL)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
		width = 0;
		height = 0;
	}
}