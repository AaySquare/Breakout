#pragma once
#include "GameObject.h"
#include "Paddle.h"
#include "Brick.h"

class Ball : public GameObject
{
private:
	sf::CircleShape ballShape;
	static constexpr float radius = 6.0f;

public:
	sf::Vector2f velocity{ speed, speed };

public:
	Ball(float startX, float startY, sf::RenderWindow& window);

	sf::FloatRect getPosition();
	sf::CircleShape getShape();

	float getRadius();
	float getBallVelocity();
	void setBallVelocity(float speedValue);

	float Left() override;
	float Right() override;
	float Top() override;
	float Bottom() override;

	void ReboundTop();
	void ReboundLeft();
	void ReboundRight();
	void ReboundPaddle(Paddle& player);
	void ReboundBrick(Brick& brick);
	void Draw() override;
	void Update() override;
};

