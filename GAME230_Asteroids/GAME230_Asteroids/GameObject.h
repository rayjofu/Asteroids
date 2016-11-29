#pragma once

#include <SFML/Graphics.hpp>

class GameObject {
public:
	virtual void update(sf::Vector2u windowSize, float dt) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual int getRenderBucket() = 0;
private:
};