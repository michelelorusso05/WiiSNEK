#pragma once

typedef struct {
    int x;
    int y;
} Vector2;


#define GRRLIB_BLACK   0x000000FF
#define GRRLIB_WHITE   0xFFFFFFFF
#define DARK_GRAY   0x202020FF
#define GRAY   0x808080FF
#define LIGHT_GRAY   0xC0C0C0FF
#define RED 0xFF0000FF


const int screenWidth = 600;
const int screenHeight = 400;
const int squareSize = 20;
const int gridWidth = screenWidth / squareSize;
const int gridHeight = screenHeight / squareSize;
const int PalCorrectionX = 20;
const int PalCorrectionY = 40;