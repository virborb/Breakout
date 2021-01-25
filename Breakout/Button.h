#pragma once
#include <SDL.h>
#include "Text.h"

class Button
{
public:
    Button();
    void setPosition(int x, int y);
    bool handleEvent(SDL_Event* e);
    void render(SDL_Renderer* renderer);
    void setText(std::string str, SDL_Color textColor, SDL_Renderer* renderer);
    int getWidth();
    int getHeight();
private:
    static const int WIDTH = 100;
    static const int HEIGHT = 20;
    SDL_Rect rect;
    SDL_Color color;
    Text text;
};

