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
        case SDLK_a: velocity -= VEL; break;
        case SDLK_d: velocity += VEL; break;
        }
    }
    //If a key was released
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        if (velocity != 0) {
            //Adjust the velocity
            switch (e.key.keysym.sym)
            {
            case SDLK_a: velocity += VEL; break;
            case SDLK_d: velocity -= VEL; break;
            }
        }
    }
}

void Paddle::move()
{
    rect.x += velocity;

    if ((rect.x < 0) || (rect.x + WIDTH > Window::SCREEN_WIDTH))
    {
        rect.x -= velocity;
    }
}

SDL_Rect* Paddle::getRect()
{
	return &rect;
}

SDL_Color Paddle::getColor()
{
	return color;
}