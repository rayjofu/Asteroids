#include "Spaceship.h"
#include <iostream>

using namespace sf;
using namespace std;

Spaceship::Spaceship() : CircleShape() {
	enabled = true;
}

Spaceship::Spaceship(string tag) {
	this->tag = tag;
	enabled = true;
}

Spaceship::~Spaceship() {

}

bool Spaceship::isEnabled() {
	return enabled;
}

void Spaceship::setEnabled(bool enabled) {
	this->enabled = enabled;
}

Vector2f Spaceship::getVelocity() {
	return velocity;
}

void Spaceship::setVelocity(Vector2f vel) {
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

float Spaceship::getSpeed() {
	return speed;
}

void Spaceship::setSpeed(float speed) {
	this->speed = speed;
}

void Spaceship::handleInput(Keyboard::Key key, float dt) {
	if (key == Keyboard::Up) {
		velocity += speed * dt * Vector2f(sin(this->getRotation() * 3.14 / 180), -cos(this->getRotation() * 3.14 / 180));
	}
	else if (key == Keyboard::Left) {
		this->rotate(-210 * dt);
	}
	else if (key == Keyboard::Right) {
		this->rotate(210 * dt);
	}
}

void Spaceship::update(Vector2u windowSize, float dt) {
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

	velocity -= 0.5f * velocity * dt;
}

void Spaceship::draw(sf::RenderWindow& window) {
	window.draw(*this);
}

string Spaceship::getTag() {
	return tag;
}

void Spaceship::setTag(string tag) {
	this->tag = tag;
}

void Spaceship::checkCollisionWith(GameObject* obj) {
/*	Vector2f pos = obj->getCenter() - this->getCenter();
	if ((pos.x * pos.x + pos.y * pos.y) <= pow(this->getRadius(), 2)) {
//		cout << "collision at " << obj->getCenter().x << " " << obj->getCenter().y << endl;

		if (obj->getTag() == "asteroid") {
			cout << "spaceship collided into astroid" << endl;
			--lives;
			enabled = false;
		}
	}
*/
}

Vector2f Spaceship::getCenter() {
	return this->getPosition();
}

float Spaceship::getCollisionRadius() {
	return this->getRadius();
}

int Spaceship::getLives() {
	return lives;
}

void Spaceship::setLives(int lives) {
	this->lives = lives;
}

void Spaceship::setPowerup(int powerup) {
	this->powerup = powerup;
}

int Spaceship::getPowerup() {
	return powerup;
}