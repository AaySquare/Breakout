#pragma once
#include "Brick.h"

#define BOARD_WIDTH 5
#define BOARD_HEIGHT 5

class Board
{
private:
	//Brick bricks[BOARD_WIDTH][BOARD_HEIGHT];
	sf::RenderWindow& m_window;

public:
	Board(sf::RenderWindow& window);
	~Board() {};

	void CreateLevel();
};

