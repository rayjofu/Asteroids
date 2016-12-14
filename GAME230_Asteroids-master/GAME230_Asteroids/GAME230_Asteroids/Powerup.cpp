#include "Powerup.h"
#include "Spaceship.h"
#include <iostream>

using namespace sf;
using namespace std;

Powerup::Powerup() {
	enabled = true;
}
Powerup::Powerup(std::string tag) {
	this->tag = tag;
	enabled = true;
}
Powerup::~Powerup() {

}
void Powerup::update(sf::Vector2u windowSize, float dt) {
	// powerup stays immobile
}
void Powerup::draw(sf::RenderWindow& window) {
	window.draw(*this);
}
string Powerup::getTag() {
	return tag;
}
void Powerup::setTag(std::string tag) {
	this->tag = tag;
}
void Powerup::checkCollisionWith(GameObject* obj) {
	Vector2f pos = obj->getCenter() - this->getCenter();
	if ((pos.x * pos.x + pos.y * pos.y) <= (this->getCollisionRadius() + obj->getCollisionRadius()) * (this->getCollisionRadius() + obj->getCollisionRadius())) {
		if (!obj->isEnabled() && ((Spaceship*)obj)->getPowerup() == 0) {
			return;
		}

		if (((Spaceship*)obj)->getPowerup() == 2 && type == 1 || ((Spaceship*)obj)->getPowerup() == 1 && type == 2) {
			return;
		}

		if (((Spaceship*)obj)->getPowerup() == 1 && type == 1) {
			return;
		}

		if (((Spaceship*)obj)->getPowerup() == 2 && type == 2) {
			return;
		}

		if (enabled && obj->getTag() == "spaceship") {
			enabled = false;
			if (type == 2) {
				((Spaceship*)obj)->setEnabled(false);
			}
			cout << "powerup collided with ship" << endl;
		}
	}
}
Vector2f Powerup::getCenter() {
	return this->getPosition();
}
float Powerup::getCollisionRadius() {
	return this->getRadius();
}
bool Powerup::isEnabled() {
	return enabled;
}
int Powerup::getType() {
	return type;
}
void Powerup::setType(int type) {
	this->type = type;
}