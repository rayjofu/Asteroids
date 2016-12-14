#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameObject.h"

class Asteroid : public sf::CircleShape, public GameObject {
public:
	Asteroid();
	Asteroid(std::string t);
	~Asteroid();
	virtual void update(sf::Vector2u windowSize, float dt);
	virtual void draw(sf::RenderWindow& window);
	virtual std::string getTag();
	void setTag(std::string tag);
	virtual void checkCollisionWith(GameObject* obj);
	virtual sf::Vector2f getCenter();
	virtual float getCollisionRadius();
	sf::Vector2f getVelocity();
	void setVelocity(sf::Vector2f vel);
	float getSpeed();
	void setSpeed(float speed);
	bool isEnabled();
	int getSize();
	void setSize(int size);
	int getLife();
	void setLife(int life);
	int getType();
	void setType(int type);
private:
	float speed;
	sf::Vector2f velocity;
	std::string tag;
	bool enabled;
	int size;
	int life;
	int type;
	sf::Sound smallExplosion;
	sf::SoundBuffer smallExplosion_buffer;
};