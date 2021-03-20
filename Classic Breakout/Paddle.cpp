#include "Paddle.h"

Paddle::Paddle(float startX, float startY, sf::RenderWindow& window)
	: GameObject{ startX, startY, window }, lives{ 3 } 
{
	paddleShape.setSize(sf::Vector2f(shapeWidth, shapeHeight));
	paddleShape.setPosition(position);
}

sf::FloatRect Paddle::getPosition()
{
	return paddleShape.getGlobalBounds();
}

sf::RectangleShape Paddle::getShape()
{
	return paddleShape;
}

int Paddle::getLives()
{
	return lives;
}

void Paddle::setLives(int lifeValue)
{
	lives = lifeValue;
}

void Paddle::HandleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && (paddleShape.getPosition().x > 5.0f))
	{
		paddleShape.move(-speed*3, 0.0f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && (paddleShape.getPosition().x < m_window.getSize().x - 69.0f))
	{
		paddleShape.move(speed*3, 0.0f);
	}
}

float Paddle::Left()
{
	return 0.0f;
}

float Paddle::Right()
{
	return 0.0f;
}

float Paddle::Top()
{
	return 0.0f;
}

float Paddle::Bottom()
{
	return 0.0f;
}

void Paddle::Draw()
{
	m_window.draw(paddleShape);
}

void Paddle::Update(){}
