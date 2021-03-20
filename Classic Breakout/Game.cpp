#include "Game.h"
#include <chrono>
#include <thread>
#include <sstream>

Game::Game(sf::RenderWindow& window, const unsigned int& windowWidth, const unsigned int& windowHeight)
	: m_window{ window }
	, m_windowWidth{ windowWidth }
	, m_windowHeight{ windowHeight }
{

	RestartGame();

	// TEXTS

	font.loadFromFile("resources/American Captain.ttf");
	titleText.setFont(font);
	titleText.setCharacterSize(50);
	titleText.setFillColor(sf::Color::White);
	titleText.setStyle(sf::Text::Bold);
	titleText.setPosition(((float)m_windowWidth / 2) - 200, ((float)m_windowHeight / 2) - 100);

	descriptionText.setFont(font);
	descriptionText.setCharacterSize(25);
	descriptionText.setFillColor(sf::Color::White);
	descriptionText.setStyle(sf::Text::Regular);
	descriptionText.setPosition(((float)m_windowWidth / 2) - 200, ((float)m_windowHeight / 2) - 30);

	gameOverText.setFont(font);
	gameOverText.setCharacterSize(42);
	gameOverText.setFillColor(sf::Color::White);
	gameOverText.setStyle(sf::Text::Bold);
	gameOverText.setPosition(((float)m_windowWidth / 2) - 150, (float)m_windowHeight / 2);

	pauseText.setFont(font);
	pauseText.setCharacterSize(42);
	pauseText.setFillColor(sf::Color::White);
	pauseText.setStyle(sf::Text::Regular);
	pauseText.setPosition(((float)m_windowWidth / 2) - 80, (float)m_windowHeight / 2);

	restartText.setFont(font);
	restartText.setCharacterSize(25);
	restartText.setFillColor(sf::Color::White);
	restartText.setStyle(sf::Text::Regular);
	restartText.setPosition(((float)m_windowWidth / 2) - 60, ((float)m_windowHeight / 2) + 100);

	scoreText.setFont(font);
	scoreText.setCharacterSize(80);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setStyle(sf::Text::Regular);
	scoreText.setPosition(150.0f, 40.0f);

	livesText.setFont(font);
	livesText.setCharacterSize(80);
	livesText.setFillColor(sf::Color::White);
	livesText.setStyle(sf::Text::Regular);
	livesText.setPosition(m_windowWidth - 160.0f, 40.0f);

	// SPRITE

	texture.loadFromFile("resources/HeartSprite.png");
	heartSprite.setTexture(texture);
	heartSprite.setPosition(m_windowWidth - 270.0f, 40.0f);
	heartSprite.scale(0.5f, 0.5f);

	// SOUND

	paddleBuffer.loadFromFile("resources/ball.wav");
	paddleSound.setBuffer(paddleBuffer);

	brickBuffer.loadFromFile("resources/brick.wav");
	brickSound.setBuffer(brickBuffer);

	loselifeBuffer.loadFromFile("resources/loselife.wav");
	loselifeSound.setBuffer(loselifeBuffer);

	wallBuffer.loadFromFile("resources/wall.wav");
	wallSound.setBuffer(wallBuffer);
	
}

// Initialization for the start of the game and when restarting the game
void Game::RestartGame()
{
	isPaused = false;
	isGameOver = false;
	currentScore = 0;
	ballBrickHitCount = 0;
	gameOverText.setString("");
	pauseText.setString("");
	restartText.setString("");
	scoreText.setString("0");

	player = std::make_unique<Paddle>((float)m_windowWidth / 2, (float)m_windowHeight - 70, m_window);
	ball = std::make_unique<Ball>((float)m_windowWidth / 2, (float)m_windowHeight / 3, m_window);
	brick = std::make_unique<Brick>((float)0, (float)0, m_window);

	player->setLives(3);
	std::stringstream s;
	s << player->getLives();
	livesText.setString(s.str());

	bricks.clear();

	CreateBricksLayout();

	ReadHighScoreFile();
}

// To read bricks layout using a txt file and count number of rows and columns of bricks
void Game::ReadBricksFile()
{
	std::string bricksText;
	int numOfLines = 0;

	std::ifstream MyReadFile("resources/Bricks Layout.txt");

	while (std::getline(MyReadFile, bricksText))
	{
		++numOfLines;
		
		for (unsigned int i = 0; i < bricksText.length(); i++)
		{
			if (bricksText[i] == '-')
			{
				bricksCountX = bricksText.length();
			}
			else
			{
				std::cout << " Error creating a bricks layout! Only '-' character allowed in the 'Bricks Layout' text file. ";
				return;
			}
		}

		totalRows.emplace_back(bricksCountX);
	}

	for (unsigned int i = 0; i < bricksText.length(); i++)
	{
		if (bricksText[i] == '-')
		{
			bricksCountY = numOfLines;
		}
	}

	MyReadFile.close();
}

// Creates a layout of bricks
void Game::CreateBricksLayout()
{
	ReadBricksFile();

	int columns = 0;
	for (unsigned int i = 0; i < totalRows.size(); i++)
	{
		columns++;

		if (columns <= bricksCountY)
		{
			for (int rows = 0; rows < totalRows[i]; rows++)
			{
				bricks.emplace_back(std::make_unique<Brick>(
					rows * (brick->getShape().getSize().x + 3) + 0,
					columns * (brick->getShape().getSize().y + 3) + m_windowHeight / 6, m_window));
			}
		}
		
	}
}

// To create and write player's highscore to a highscore text file
void Game::CreateHighScoreFile()
{
	std::ofstream writeFile("resources/HighScore.txt");

	if (writeFile.is_open())
	{
		if (currentScore > highScore)
		{
			highScore = currentScore;
		}
		writeFile << highScore;
	}
	
	writeFile.close();
}

// To read player's highscore from the highscore text file
void Game::ReadHighScoreFile()
{
	std::ifstream readFile("resources/HighScore.txt");

	if (readFile.is_open())
	{
		while (!readFile.eof())
		{
			readFile >> highScore; 
		}
	}

	readFile.close(); 
}

// To handle collisions
void Game::HandleCollision()
{
	// Collision between the ball and left side of the screen
	if (ball->getShape().getPosition().x - ball->getRadius() < 0.0f)
	{
		wallSound.play();
		ball->ReboundLeft();
	}
	// Collision between the ball and right side of the screen
	else if (ball->getShape().getPosition().x + ball->getRadius() > m_windowWidth)
	{
		wallSound.play();
		ball->ReboundRight();
	}
	// Collision between the ball and top side of the screen
	else if (ball->getShape().getPosition().y - ball->getRadius() < 0.0f)
	{
		wallSound.play();
		ball->ReboundTop();
	}
	// Collision between the ball and bottom side of the screen
	else if (ball->getShape().getPosition().y + ball->getRadius() - 20 > m_windowHeight)
	{
		if (player->getLives() <= 1)
		{
			isGameOver = true;
			CreateHighScoreFile();
			ReadHighScoreFile();
			std::stringstream cs;
			std::stringstream hs;
			cs << currentScore;
			hs << highScore;
			gameOverText.setString(
				"Your final score: " + cs.str() + "\n"
				"HighScore to beat: " + hs.str()
			);
			restartText.setString("Press R to restart\nPress Esc to Quit");
		}
		else
		{
			loselifeSound.play();
			player->setLives(player->getLives() - 1);
			ball = std::make_unique<Ball>((float)m_windowWidth / 2, (float)m_windowHeight / 3, m_window);
			std::stringstream s;
			s << player->getLives();
			livesText.setString(s.str());
		}
	}
	// Collision between the ball and the paddle
	else if (ball->getPosition().intersects(player->getPosition()))
	{
		paddleSound.play();
		ball->ReboundPaddle(*player);
	}
	// Collision between the ball and each brick
	for (unsigned int i = 0; i < bricks.size(); i++)
	{
		if (ball->getPosition().intersects(bricks[i]->getPosition()))
		{
			ballBrickHitCount++;
			if (ballBrickHitCount % 6 == 0)
			{
				if (ball->getBallVelocity() == MAX_SPEED)
				{
					ball->setBallVelocity(MAX_SPEED);
				}
				else
				{
					ball->setBallVelocity(ball->getBallVelocity() + 0.5f);
				}
			}

			if (bricks[i]->getStrength() == 1)
			{

				if (bricks[i]->getColor() == 1)
				{
					currentScore += 10;
					std::stringstream s;
					s << currentScore;
					scoreText.setString(s.str());
				}
				else
				{
					currentScore += 20;
					std::stringstream s;
					s << currentScore;
					scoreText.setString(s.str());
				}

				brickSound.play();
				ball->ReboundBrick(*bricks[i]);
				bricks.erase(std::remove(bricks.begin(), bricks.end(), bricks[i]), bricks.end());
			}
			else
			{
				brickSound.play();
				ball->ReboundBrick(*bricks[i]);
				bricks[i]->setStrength(bricks[i]->getStrength() - 1);
			}
		}
	}
	if (bricks.size() == 0)
	{
		isGameOver = true;
		CreateHighScoreFile();
		ReadHighScoreFile();
		std::stringstream cs;
		std::stringstream hs;
		cs << currentScore;
		hs << highScore;
		gameOverText.setString(
			"            You win!\n"
			"Your final score: " + cs.str() + "\n"
			"HighScore to beat: " + hs.str() + "\n"
		);
		restartText.setString("\n\nPress R to restart\nPress Esc to Quit");
	}
	
}

// Handle player input
void Game::HandleInput()
{
	if (!isGameOver && isStart)
	{
		player->HandleInput();
	}
}

// Draw the game objects
void Game::Draw()
{
	// While it's not game over, draw these game objects
	if (!isGameOver && isStart)
	{
		player->Draw();
		ball->Draw();
		for (unsigned int i = 0; i < bricks.size(); i++)
		{
			bricks[i]->Draw();
		}
		m_window.draw(scoreText);
		m_window.draw(livesText);
		m_window.draw(heartSprite);
	}
	
	// If the game hasn't started, draw the title and description texts 
	if (!isStart)
	{
		m_window.draw(titleText);
		m_window.draw(descriptionText);
	}

	m_window.draw(pauseText);
	m_window.draw(gameOverText);
	m_window.draw(restartText);
}

// Update the player and ball
void Game::Update()
{
	if (!isGameOver && isStart)
	{
		player->Update();
		ball->Update();
	}
	
	//brick->Update();
}

void Game::Run()
{
	//Game Loop
	while (m_window.isOpen())
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			// Press Esc to quit the game
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				m_window.close();
			}
			
			// Press P to pause the game
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
			{
				if (!isGameOver && isStart)
				{
					isPaused = !isPaused;
				}
			}
			
			// Press R to restart the game
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
			{
				isStart = false;
				RestartGame();
			}
			
			// Press spacebar to start the game
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
			{
				isStart = true;
			}
		}

		m_window.clear();

		// Setting text to display at the start
		titleText.setString("Welcome to BREAKOUT");
		descriptionText.setString(
			"Press Spacebar to start playing\n\n\n"
			"Controls:\n"
			"Press Left and Right arrows to move\n"
			"Press P to pause\n"
			"Press R to restart\n"
			"Press ESC to Quit"
		);

		// If game has started, handle collision, handle input, update and draw to the game
		if (isStart)
		{
			titleText.setString("");
			HandleCollision();

			if (!isPaused)
			{
				HandleInput();
				Update();
			}

			if (isPaused)
				pauseText.setString("Game Paused");
			else
				pauseText.setString("");
		}

		Draw();

		m_window.display();
	}
}