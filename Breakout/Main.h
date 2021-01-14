#pragma once
#include <stdio.h>
#include <string>
#include <stdlib.h> 
#include <time.h>
#include <vector>

#include "Window.h"
#include "Brick.h"
#include "Paddle.h"

static const int TOTAL_TILES = 50;
static const int COLUMS = 10;
static const int ROWS = 5;

std::vector <Brick> createTiles();

