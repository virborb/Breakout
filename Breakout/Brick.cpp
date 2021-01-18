#include "Brick.h"


Brick::Brick(int x, int y, SDL_Color color)
{
    rect = { x, y, width, height };
    this->color = color;
    isDead = false;
}

SDL_Rect* Brick::getRect()
{
    return &rect;
}

SDL_Color Brick::getColor()
{
    return color;
}

void Brick::setIsDead(bool isDead) {
    this->isDead = isDead;
}

bool Brick::getIsDead() {
    return isDead;
}
