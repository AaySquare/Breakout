#include "Brick.h"
#include <iostream>

Brick::Brick(float startX, float startY, sf::RenderWindow& window)
    : GameObject{ startX, startY, window }, strength {0}
{
    // Giving random color to brick(yellow or orange) and setting brick strength of each brick
	brickShape.setSize(sf::Vector2f(shapeWidth, shapeHeight));
    brickShape.setPosition(position);
    color = (rand() % 2) + 1;
    if (color == 1)
    {
        brickShape.setFillColor(sf::Color::Yellow);
        strength = 1;
    }
    else if (color == 2)
    {
        brickShape.setFillColor(sf::Color(255, 165, 0));
        strength = 2;
    }
}

sf::FloatRect Brick::getPosition()
{
    return brickShape.getGlobalBounds();
}

sf::RectangleShape Brick::getShape()
{
    return brickShape;
}

int Brick::getStrength()
{
    return strength;
}

void Brick::setStrength(int strengthValue)
{
    strength = strengthValue;
}

int Brick::getColor()
{
    return color;
}

float Brick::Left()
{
    return brickShape.getPosition().x - brickShape.getSize().x / 2.0f;
}

float Brick::Right()
{
    return brickShape.getPosition().x + brickShape.getSize().x / 2.0f;
}

float Brick::Top()
{
    return brickShape.getPosition().y - brickShape.getSize().y / 2.0f;
}

float Brick::Bottom()
{
    return brickShape.getPosition().y + brickShape.getSize().y / 2.0f;
}

void Brick::Draw()
{
    m_window.draw(brickShape);
}

void Brick::Update()
{

}
