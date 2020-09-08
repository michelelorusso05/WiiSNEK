#include "fruit.h"
#include <stdlib.h>
#include <time.h>
#include <grrlib.h>
#include "snake.h"

void Fruit::draw()
{
	GRRLIB_Rectangle(Fruit::pos.x * squareSize + PalCorrectionX, Fruit::pos.y * squareSize + PalCorrectionY, squareSize, squareSize, RED, true);
}

void Fruit::checkForSnake(Snake& snake)
{
	Vector2 snakePos = snake.getPos();
	if (snakePos.x == Fruit::pos.x && snakePos.y == Fruit::pos.y)
	{
		snake.addSquare();

		bool isNewPosValid = false;


		// Generate a new position and check if it doesn't equal to any of the snake's body parts.
		do {
			isNewPosValid = true;
			std::vector<Vector2> snakeTail = snake.getTail();
			// Generate a new position
			Fruit::pos.x = rand() % gridWidth;
			Fruit::pos.y = rand() % gridHeight;

			for (int i = 0; i < static_cast<int>(snakeTail.size()); i++)
			{
				if (Fruit::pos.x == snakeTail[i].x && Fruit::pos.y == snakeTail[i].y)
				{
					isNewPosValid = false;
				}
			}
			
		}	while (!isNewPosValid);


	} 
}

Fruit::Fruit()
{
	srand(time(NULL));

	Fruit::pos.x = rand() % gridWidth;
	Fruit::pos.y = rand() % gridHeight;
}