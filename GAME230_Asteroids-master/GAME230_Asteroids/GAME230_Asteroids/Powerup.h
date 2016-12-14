#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>

class Powerup : public sf::CircleShape, public GameObject {
private:
	int type;
	bool enabled;
	std::string tag;
public:
	Powerup();
	Powerup(std::string t);
	~Powerup();
	virtual void update(sf::Vector2u windowSize, float dt);
	virtual void draw(sf::RenderWindow& window);
	virtual std::string getTag();
	void setTag(std::string tag);
	virtual void checkCollisionWith(GameObject* obj);
	virtual sf::Vector2f getCenter();
	virtual float getCollisionRadius();
	bool isEnabled();
	int getType();
	void setType(int type);
};