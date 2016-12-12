#pragma once
#include <SFML/Graphics.hpp>

class GameObject {
public:
	virtual ~GameObject() {};
	virtual void update(sf::Vector2u windowSize, float dt) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual std::string getTag() = 0;
	virtual void checkCollisionWith(GameObject* obj) = 0;
	virtual sf::Vector2f getCenter() = 0;
	virtual float getCollisionRadius() = 0;
	virtual bool isEnabled() = 0;
private:
};