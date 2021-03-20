#include "GameObject.h"

GameObject::GameObject(float startX, float startY, sf::RenderWindow& window)
	: position{ startX, startY }
	, speed{ 5.0f }
	, m_window{ window }
{
}