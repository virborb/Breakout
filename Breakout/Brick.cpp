#include "Brick.h"


Brick::Brick(int x, int y, SDL_Color color)
{
    rect = { x, y, width, height };
    this->color = color;
}

SDL_Rect* Brick::getRect()
{
    return &rect;
}

SDL_Color Brick::getColor()
{
    return color;
}
