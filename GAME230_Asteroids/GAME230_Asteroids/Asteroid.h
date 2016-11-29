#pragma once

#include <SFML/Graphics.hpp>
#include "GameObject.h"

class Asteroid : public sf::CircleShape, public GameObject {
public:
	Asteroid();
	Asteroid(float radius);
	sf::Vector2f getVelocity();
	void setVelocity(sf::Vector2f vel);
	void update(sf::Vector2u windowSize, float dt);
	void draw(sf::RenderWindow& window);
	int getRenderBucket();
private:
	sf::Vector2f velocity;
};