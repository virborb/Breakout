#include "Paddle.h"

Paddle::Paddle() {
	rect = { Window::SCREEN_WIDTH/2 - WIDTH/2, Window::SCREEN_HEIGHT- 10, WIDTH, HEIGHT };
	color = {0xFF, 0xFF, 0xFF, 0xFF};
    velocity = 0;
}

void Paddle::handleEvent(SDL_Event& e)
{
    //If a key was pressed
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        //Adjust the velocity
        switch (e.key.keysym.sym)
        {
        case SDLK_a: velocity -= speed; break;
        case SDLK_d: velocity += speed; break;
        }
    }
    //If a key was released
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        if (velocity != 0) {
            //Adjust the velocity
            switch (e.key.keysym.sym)
            {
            case SDLK_a: velocity += speed; break;
            case SDLK_d: velocity -= speed; break;
            }
        }
    }
}

void Paddle::move()
{
    rect.x += (int) velocity;

    if ((rect.x < 0) || (rect.x + rect.w > Window::SCREEN_WIDTH))
    {
        rect.x -= (int) velocity;
    }
}

void Paddle::centerPaddle()
{
    rect.x = Window::SCREEN_WIDTH / 2 - rect.w / 2;
}

SDL_Rect* Paddle::getRect()
{
	return &rect;
}

SDL_Color Paddle::getColor()
{
	return color;
}

void Paddle::increaseVelocity()
{
    speed = speed + 0.5;
}

void Paddle::decreaseWidth()
{
    rect.w = (int) (rect.w * 0.90);
}