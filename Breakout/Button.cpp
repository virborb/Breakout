#include "Button.h"

/**
 * @brief Creates a new button.
*/
Button::Button()
{
    rect.x = 0;
    rect.y = 0;
    rect.w = WIDTH;
    rect.h = HEIGHT;
    color = { 0x0, 0x0, 0xFF };
}

/**
 * @brief Sets the position of the button.
 * @param x the x cordinate.
 * @param y the y cordinate.
*/
void Button::setPosition(int x, int y)
{
    rect.x = x;
    rect.y = y;
}

/**
 * @brief Gets the width of the button.
 * @return The width.
*/
int Button::getWidth()
{
    return rect.w;
}

/**
 * @brief Gets the height of the button.
 * @return the height.
*/
int Button::getHeight()
{
    return rect.h;
}

/**
 * @brief Sets the text on the button
 * @param str The string.
 * @param textColor the color of the text
 * @param renderer The renderer to use.
*/
void Button::setText(std::string str, SDL_Color textColor, SDL_Renderer* renderer)
{
    text.loadFromRenderedText(str, textColor, renderer);
}

/**
 * @brief Handle if a button is pressed.
 * @param e The SDL event pointer.
 * @return true if button is pressed otherwise false.
*/
bool Button::handleEvent(SDL_Event* e)
{
    if (e->button.button == SDL_BUTTON_LEFT)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);

        if (x > rect.x && x < rect.x + rect.w && y > rect.y && y < rect.y + rect.h)
        {
            return true;
        }
    }
    return false;
}

/**
 * @brief Render the button.
 * @param renderer the renderer to use.
*/
void Button::render(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
    text.render(rect.x + rect.w/2 - text.getWidth()/2 , rect.y, renderer);
}