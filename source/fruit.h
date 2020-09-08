#pragma once

#include "global.h"
#include "snake.h"

class Fruit
{
public:
	void draw();
	// Again, draws the fruit to the screen.
	void checkForSnake(Snake& snake);
	// Checks if position equals with snake position.
	// If so, add a square to the snake, and generate a new position.
	Fruit();
	// Default constructor, initializes the class
private:
	Vector2 pos;
};