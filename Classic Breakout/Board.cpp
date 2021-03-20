#include "Board.h"

Board::Board(sf::RenderWindow& window) : m_window{ window }
{
}

/*void Board::CreateLevel()
{
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		for (int j = 0; j < BOARD_HEIGHT; j++)
		{
			Brick brick;

			brick.colorType = (rand() % 2) + 1;    // Random color
			switch (brick.colorType)
			{
			case 1:
				// Yellow
				brick.getShape().setFillColor(sf::Color::Yellow);
				brick.strength = 1;
			case 2:
				// Orange
				brick.getShape().setFillColor(sf::Color(255, 165, 0));
				brick.strength = 2;
			default:
				break;
			}
			//brick.type = (i ^ j) % 4; // Example of a fixed pattern using xor
			brick.state = true;         // Brick is present
			bricks[i][j] = brick;
		}
	}
}*/
