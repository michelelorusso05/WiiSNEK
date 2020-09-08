#pragma once

#include <vector>
#include "global.h"

class Snake
{
public:
	void draw();
	// It draws the snake to the screen, no shit Sherlock

	void updatePos(Vector2);
	// It updates the snake's position and also its tail

	Vector2 getPos();
	// Returns the snake's current position

	void addSquare();
	// Adds a square to the snake

	void revive();
	// Revives the snake resetting the score, beginning a new game

	int getLength();
	// Returns the snake's current length

	bool checkAlive();
	// Returns the snake's current state

	std::vector<Vector2> getTail();
	// Returns the snake's tail positions

	Snake();
	// Default constructor, initializes the class

private:
	Vector2 pos;
	int length;
	std::vector<Vector2> tailPos;
	bool isAlive = true;
};