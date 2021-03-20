#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <ctime>

#include "Game.h"

int main()
{
	srand((unsigned)time(0));
	const unsigned int windowWidth = 740;
	const unsigned int windowHeight = 900;
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Breakout");
	window.setFramerateLimit(60);

	Game game(window, windowWidth, windowHeight);
	game.Run();
	
	return 0;
}