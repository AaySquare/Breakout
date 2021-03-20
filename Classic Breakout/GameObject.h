#pragma once
#include <SFML/Graphics.hpp>

class GameObject
{
protected:
	sf::Vector2f position;
	float speed;
	sf::RenderWindow& m_window;

public:
	GameObject(float startX, float startY, sf::RenderWindow& window);
	virtual ~GameObject() {};

	virtual float Left() = 0;
	virtual float Right() = 0;
	virtual float Top() = 0;
	virtual float Bottom() = 0;

	virtual void Draw() = 0;
	virtual void Update() = 0;
};

