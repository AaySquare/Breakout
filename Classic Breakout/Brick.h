#pragma once
#include "GameObject.h"

class Brick : public GameObject
{
private:
	sf::RectangleShape brickShape;
	static constexpr int shapeWidth = 50;
	static constexpr int shapeHeight = 20;
	int color;
	int strength;

public:
	Brick(float startX, float startY, sf::RenderWindow& window);

	sf::FloatRect getPosition();
	sf::RectangleShape getShape();

	int getStrength();
	void setStrength(int strengthValue);
	int getColor();

	float Left() override;
	float Right() override;
	float Top() override;
	float Bottom() override;

	void Draw() override;
	void Update() override;
};

