#include "Brick.h"

/**
 * @brief Constructs a brick at given position and color.
 * @param x The x cordinate.
 * @param y The y cordinate
 * @param color The color of the brick.
*/
Brick::Brick(int x, int y, SDL_Color color)
{
    rect = { x, y, width, height };
    this->color = color;
    isDead = false;
}

/**
 * @brief Returns The size and postion of the brick.
 * @return The size and position.
*/
SDL_Rect* Brick::getRect()
{
    return &rect;
}

/**
 * @brief Gets the color of the brick.
 * @return The color.
*/
SDL_Color Brick::getColor()
{
    return color;
}

/**
 * @brief Sets if brick is dead or not.
 * @param isDead The boolean if dead or not.
*/
void Brick::setIsDead(bool isDead) {
    this->isDead = isDead;
}

/**
 * @brief Check if brick is dead
 * @return A boolean if dead or not.
*/
bool Brick::getIsDead() {
    return isDead;
}
