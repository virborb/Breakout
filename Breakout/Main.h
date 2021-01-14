#pragma once
#include <stdio.h>
#include <string>
#include <stdlib.h> 
#include <time.h>
#include <vector>

#include "Window.h"
#include "Brick.h"
#include "Paddle.h"
#include "Ball.h"

static const int COLUMS = 10;
static const int ROWS = 5;

const SDL_MessageBoxButtonData buttons[] = {
        { 0, 0, "no" },
        { 0, 1, "yes" }
};
const SDL_MessageBoxColorScheme colorScheme = {
    { /* .colors (.r, .g, .b) */
        /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
        { 255,   0,   0 },
        /* [SDL_MESSAGEBOX_COLOR_TEXT] */
        {   0, 255,   0 },
        /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
        { 255, 255,   0 },
        /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
        {   0,   0, 255 },
        /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
        { 255,   0, 255 }
    }
};
const SDL_MessageBoxData messageboxdata = {
    SDL_MESSAGEBOX_INFORMATION, /* .flags */
    NULL, /* .window */
    "Game Over", /* .title */
    "Game over, Start a new game?", /* .message */
    SDL_arraysize(buttons), /* .numbuttons */
    buttons, /* .buttons */
    &colorScheme /* .colorScheme */
};

std::vector <Brick> createBricks();

