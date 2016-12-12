#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

class Laser : public sf::CircleShape, public GameObject {
public:
	Laser();
	Laser(std::string tag);
	~Laser();
	void update(sf::Vector2u windowSize, float dt);
	void draw(sf::RenderWindow& window);
	void setTag(std::string t);
	std::string getTag();
	void checkCollisionWith(GameObject* obj);
	sf::Vector2f getCenter();
	float getCollisionRadius();
	void setEnabled(bool enabled);
	bool isEnabled();
	sf::Vector2f getVelocity();
	void setVelocity(sf::Vector2f vel);
	float getSpeed();
	void setSpeed(float speed);
private:
	std::string tag;
	float speed;
	sf::Vector2f velocity;
	float lifetime;
	bool enabled;
};