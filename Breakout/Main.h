#pragma once
#include <stdio.h>
#include <time.h>

#include "Breakout.h"

const SDL_MessageBoxButtonData buttons[2] = {
		{ 0, 0, "no" },
		{ 0, 1, "yes" }
};
const SDL_MessageBoxColorScheme colorScheme = {
	{
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
	SDL_MESSAGEBOX_INFORMATION,
	NULL,
	"Game Over",
	"Game over, Start a new game?",
	SDL_arraysize(buttons),
	buttons,
	&colorScheme
};


