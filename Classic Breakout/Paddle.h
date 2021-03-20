#pragma once
#include "GameObject.h"

class Paddle : public GameObject
{
private:
	sf::RectangleShape paddleShape;
	static constexpr int shapeWidth = 60;
	static constexpr int shapeHeight = 10;
	int lives;

public:
	Paddle(float startX, float startY, sf::RenderWindow& window);

	sf::FloatRect getPosition();
	sf::RectangleShape getShape();

	int getLives();
	void setLives(int lifeValue);
	void HandleInput();

	float Left() override;
	float Right() override;
	float Top() override;
	float Bottom() override;

	void Draw() override;
	void Update() override;
};

