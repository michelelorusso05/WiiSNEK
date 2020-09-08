#include <vector>
#include "Snake.h"
#include <grrlib.h>

void Snake::draw()
{
	// Draw the head
	GRRLIB_Rectangle(Snake::pos.x * squareSize + PalCorrectionX, Snake::pos.y * squareSize + PalCorrectionY, squareSize, squareSize, LIGHT_GRAY, true);

	for (int i = 0; i < static_cast<int>(Snake::tailPos.size()); i++)
	{
		GRRLIB_Rectangle(Snake::tailPos[i].x * squareSize + PalCorrectionX, Snake::tailPos[i].y * squareSize + PalCorrectionY, squareSize, squareSize, GRRLIB_WHITE, true);
	}
	
}

void Snake::updatePos(Vector2 input)
{

	if (Snake::pos.x + input.x < 0 || Snake::pos.x + input.x > gridWidth - 1
		|| Snake::pos.y + input.y < 0 || Snake::pos.y + input.y > gridHeight - 1)
		isAlive = false;

	else
	{
		if (Snake::length > 1)
		{
			Snake::tailPos.insert(Snake::tailPos.begin(), Snake::pos);
			Snake::tailPos.pop_back();
		}

		Snake::pos.x += input.x;
		Snake::pos.y += input.y;
	}

	// Check if the head collides with the body
	for (int i = 0; i < static_cast<int>(Snake::tailPos.size()); i++)
		{
			if (Snake::tailPos[i].x == Snake::pos.x && Snake::tailPos[i].y == Snake::pos.y)
				isAlive = false;
		}
}

Vector2 Snake::getPos()
{
	return Snake::pos;
}

void Snake::addSquare()
{
	Snake::length += 1;
	Snake::tailPos.push_back(Snake::pos);
}

void Snake::revive()
{
	Snake::isAlive = true;
	Snake::length = 1;
	Snake::tailPos.clear();
	Snake::pos.x = 16;
	Snake::pos.y = 12;
}

int Snake::getLength()
{
	return Snake::length;
}

bool Snake::checkAlive()
{
	return Snake::isAlive;
}

std::vector<Vector2> Snake::getTail()
{
	return Snake::tailPos;
}

Snake::Snake()
{
	Snake::pos.x = 16;
	Snake::pos.y = 12;
	Snake::length = 1;
}
