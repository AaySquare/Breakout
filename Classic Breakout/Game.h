#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"

#include <algorithm>
#include <fstream>
#include <iostream>

class Game
{
private:
	sf::RenderWindow& m_window;
	std::unique_ptr<Paddle> player;
	std::unique_ptr<Ball> ball;
	std::vector<std::unique_ptr<Brick>>bricks;
	std::unique_ptr<Brick> brick;
	std::vector<int> totalRows;
	
	int bricksCountX;
	int bricksCountY;
	int spacePos = 0;
	int ballBrickHitCount = 0;
	int currentScore = 0;
	int highScore;
	const float MAX_SPEED = 9.0f;

	sf::Font font;
	sf::Text titleText;
	sf::Text descriptionText;
	sf::Text pauseText;
	sf::Text gameOverText;
	sf::Text restartText;
	sf::Text scoreText;
	sf::Text livesText;

	sf::Texture texture;
	sf::Sprite heartSprite;

	sf::SoundBuffer paddleBuffer;
	sf::Sound paddleSound;

	sf::SoundBuffer brickBuffer;
	sf::Sound brickSound;

	sf::SoundBuffer loselifeBuffer;
	sf::Sound loselifeSound;

	sf::SoundBuffer wallBuffer;
	sf::Sound wallSound;

	bool isPaused;
	bool isGameOver;
	bool isStart;
	bool liveLost;

public:
	const unsigned int m_windowWidth;
	const unsigned int m_windowHeight;

public:
	Game(sf::RenderWindow& window, const unsigned int& windowWidth, const unsigned int& windowHeight);
	void RestartGame();
	void ReadBricksFile();
	void CreateBricksLayout();
	void CreateHighScoreFile();
	void ReadHighScoreFile();
	void HandleCollision();
	void HandleInput();
	void Draw();
	void Update();
	void Run();
};

