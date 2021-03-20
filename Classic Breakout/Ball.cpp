#include "Ball.h"
#include <iostream>

Ball::Ball(float startX, float startY, sf::RenderWindow& window)
	: GameObject{ startX, startY, window }
{
	ballShape.setRadius(radius);
	ballShape.setPosition(position);
}

sf::FloatRect Ball::getPosition()
{
	return ballShape.getGlobalBounds();
}

sf::CircleShape Ball::getShape()
{
	return ballShape;
}

float Ball::getRadius()
{
	return radius;
}

float Ball::getBallVelocity()
{
	return speed;
}

void Ball::setBallVelocity(float speedValue)
{
	speed = speedValue;
}

float Ball::Left()
{
	return ballShape.getPosition().x - ballShape.getRadius();
}

float Ball::Right()
{
	return ballShape.getPosition().x + ballShape.getRadius();
}

float Ball::Top()
{
	return ballShape.getPosition().y - ballShape.getRadius();
}

float Ball::Bottom()
{
	return ballShape.getPosition().y + ballShape.getRadius();
}

void Ball::ReboundTop()
{
	velocity.y = speed;
}

void Ball::ReboundLeft()
{
	velocity.x = speed;
}

void Ball::ReboundRight()
{
	velocity.x = -speed;
}

void Ball::ReboundPaddle(Paddle& player)
{
	velocity.y = -speed;

	if (getShape().getPosition().x < player.getShape().getPosition().x + 15.0f)
	{
		velocity.x = -speed;
	}
	else
	{
		velocity.x = speed;
	}
}

void Ball::ReboundBrick(Brick& brick)
{
	float overlapLeft = Right() - brick.Left();
	float overlapRight = (brick.Right() - Left());
	float overlapTop = Bottom() - brick.Top();
	float overlapBottom = brick.Bottom() - Top();

	bool ballFromLeft = abs(overlapLeft) < abs(overlapRight);

	bool ballFromTop = abs(overlapTop) < abs(overlapBottom);

	float minOverlapX{ ballFromLeft ? overlapLeft : overlapRight };
	float minOverlapY{ ballFromTop ? overlapTop : overlapBottom };

	if (abs(minOverlapX) < abs(minOverlapY))
		velocity.x = ballFromLeft ? -speed : speed;
	else
		velocity.y = ballFromTop ? -speed : speed;

	if (brick.getColor() == 2)
	{
		ballShape.setFillColor(sf::Color((rand() % 255) + 180, rand() % 255, rand() % 255));
	}
}

void Ball::Draw()
{
	m_window.draw(ballShape);
}

void Ball::Update()
{
	ballShape.move(velocity);
}
