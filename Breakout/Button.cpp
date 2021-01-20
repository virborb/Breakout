#include "Button.h"

Button::Button()
{
    rect.x = 0;
    rect.y = 0;
    rect.w = WIDTH;
    rect.h = HEIGHT;
    color = { 0x0, 0xFF, 0x0 };
}

void Button::setPosition(int x, int y)
{
    rect.x = x;
    rect.y = y;
}

void Button::setText(std::string str, SDL_Color textColor, SDL_Renderer* renderer)
{
    text.loadFromRenderedText(str, textColor, renderer);
}

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

void Button::render(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
    text.render(rect.x + rect.w/2, rect.y + rect.h/2, renderer);
}