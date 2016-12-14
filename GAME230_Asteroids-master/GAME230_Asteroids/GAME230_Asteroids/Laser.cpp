#include "Laser.h"

using namespace sf;
using namespace std;

Laser::Laser() {
	lifetime = 0.f;
	enabled = true;
}

Laser::Laser(std::string tag) {
	this->tag = tag;
	lifetime = 0.f;
	enabled = true;
}

Laser::~Laser() {

}

void Laser::update(sf::Vector2u windowSize, float dt) {
	Vector2f pos = this->getPosition() + velocity * dt;
	
	if (pos.x < 0 && velocity.x < 0) {
		pos.x = windowSize.x;
	}
	if (pos.x > windowSize.x && velocity.x > 0) {
		pos.x = 0.f;
	}
	if (pos.y < 0 && velocity.y < 0) {
		pos.y = windowSize.y;
	}
	if (pos.y > windowSize.y && velocity.y > 0) {
		pos.y = 0.f;
	}

	this->setPosition(pos);

	lifetime += dt;
	if (lifetime > 1.f) {
		enabled = false;
	}
}

void Laser::draw(RenderWindow& window) {
	window.draw(*this);
}

void Laser::setTag(std::string tag) {
	this->tag = tag;
}

std::string Laser::getTag() {
	return tag;
}

void Laser::checkCollisionWith(GameObject* obj) {

}

sf::Vector2f Laser::getCenter() {
	return this->getPosition();
}

float Laser::getCollisionRadius() {
	return this->getRadius();
}

void Laser::setEnabled(bool enabled) {
	this->enabled = enabled;
}

bool Laser::isEnabled() {
	return enabled;
}

sf::Vector2f Laser::getVelocity() {
	return velocity;
}

void Laser::setVelocity(sf::Vector2f vel) {
	if (vel.x == 0.f) {
		velocity.x = 0.f;
	}
	else {
		velocity.x = speed * vel.x / sqrt(vel.x * vel.x + vel.y * vel.y);
	}
	if (vel.y == 0.f) {
		velocity.y = 0.f;
	}
	else {
		velocity.y = speed * vel.y / sqrt(vel.x * vel.x + vel.y * vel.y);
	}
}

float Laser::getSpeed() {
	return speed;
}

void Laser::setSpeed(float speed) {
	this->speed = speed;
}