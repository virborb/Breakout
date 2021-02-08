#include "Paddle.h"

/**
 * @brief Makes a Paddle that centered at the bottom of the screen.
*/
Paddle::Paddle() {
	rect = { Window::SCREEN_WIDTH/2 - WIDTH/2, Window::SCREEN_HEIGHT- 10, WIDTH, HEIGHT };
	color = {0xFF, 0xFF, 0xFF, 0xFF};
    velocity = 0;
}

/**
 * @brief Handles key presses on A and D.
 * @param e The SDL event pointer.
*/
void Paddle::handleEvent(SDL_Event& e)
{
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_a: velocity -= speed; break;
        case SDLK_d: velocity += speed; break;
        }
    }
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        if (velocity != 0) {
            switch (e.key.keysym.sym)
            {
            case SDLK_a: velocity += speed; break;
            case SDLK_d: velocity -= speed; break;
            }
        }
    }
}

/**
 * @brief Moves the paddle left or right.
*/
void Paddle::move()
{
    rect.x += static_cast<int>(velocity);

    if ((rect.x < 0) || (rect.x + rect.w > Window::SCREEN_WIDTH))
    {
        rect.x -= static_cast<int>(velocity);
    }
}

/**
 * @brief Moves the paddle to the center.
*/
void Paddle::centerPaddle()
{
    rect.x = Window::SCREEN_WIDTH / 2 - rect.w / 2;
}

/**
 * @brief Returns the size and position of the paddle
 * @return The size and position.
*/
SDL_Rect* Paddle::getRect()
{
	return &rect;
}

/**
 * @brief Gets the color of the paddle 
 * @return The color
*/
SDL_Color Paddle::getColor()
{
	return color;
}

/**
 * @brief Increases the velocity by 0.5 units.
*/
void Paddle::increaseVelocity()
{
    speed = speed + 0.5;
}

/**
 * @brief Decreases the width of the paddle.
*/
void Paddle::decreaseWidth()
{
    rect.w = static_cast<int> (rect.w * 0.9);
}