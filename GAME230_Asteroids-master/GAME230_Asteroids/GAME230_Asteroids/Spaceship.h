#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

class Spaceship : public sf::CircleShape, public GameObject {
private:
	std::string tag;
	sf::Vector2f velocity;
	float speed;
	int lives;
	bool enabled;
	int powerup;
public:
	Spaceship();
	Spaceship(std::string tag);
	~Spaceship();
	void update(sf::Vector2u windowSize, float dt);
	void draw(sf::RenderWindow& window);
	void setTag(std::string tag);
	std::string getTag();
	void checkCollisionWith(GameObject* obj);
	sf::Vector2f getCenter();
	float getCollisionRadius();
	bool isEnabled();
	void setEnabled(bool enabled);
	sf::Vector2f getVelocity();
	void setVelocity(sf::Vector2f vel);
	float getSpeed();
	void setSpeed(float speed);
	int getLives();
	void setLives(int lives);
	void handleInput(sf::Keyboard::Key key, float dt);
	void setPowerup(int powerup);
	int getPowerup();
};