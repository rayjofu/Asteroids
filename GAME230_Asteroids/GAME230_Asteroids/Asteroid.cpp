#include "Asteroid.h"
#include "Spaceship.h"
#include "Laser.h"
#include <iostream>

using namespace sf;
using namespace std;

Asteroid::Asteroid() : CircleShape() {
	enabled = true;
}

Asteroid::Asteroid(string tag) {
	this->tag = tag;
	enabled = true;
}

Asteroid::~Asteroid() {

}

Vector2f Asteroid::getVelocity() {
	return velocity;
}

void Asteroid::setVelocity(Vector2f vel) {
	if (vel.x == 0.f) {
		velocity = Vector2f(0, speed * vel.y / sqrt(vel.y * vel.y));
	}
	else if (vel.y == 0.f) {
		velocity = Vector2f(speed * vel.x / sqrt(vel.x * vel.x), 0);
	}
	else {
		velocity = Vector2f(speed * vel.x / sqrt(vel.x * vel.x), speed * vel.y / sqrt(vel.y * vel.y));
	}
}

float Asteroid::getSpeed() {
	return speed;
}

void Asteroid::setSpeed(float speed) {
	this->speed = speed;
}

void Asteroid::update(Vector2u windowSize, float dt) {
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
}

void Asteroid::draw(sf::RenderWindow& window) {
	window.draw(*this);
}

string Asteroid::getTag() {
	return tag;
}

void Asteroid::setTag(string tag) {
	this->tag = tag;
}

void Asteroid::checkCollisionWith(GameObject* obj) {
	Vector2f pos = obj->getCenter() - this->getCenter();
	if ((pos.x * pos.x + pos.y * pos.y) <= (this->getCollisionRadius() + obj->getCollisionRadius()) * (this->getCollisionRadius() + obj->getCollisionRadius())) {
		if (obj->getTag() == "asteroid") {
			Asteroid* ptr = (Asteroid*) obj;
			Vector2f vel = ptr->getVelocity();
			ptr->setVelocity(this->getVelocity());
			this->setVelocity(vel);
		}
		else if (!obj->isEnabled()) {
			return;
		}
		
		if (obj->getTag() == "spaceship") {
			((Spaceship*)obj)->setEnabled(false);
			((Spaceship*)obj)->setLives(((Spaceship*)obj)->getLives() - 1);
			((Spaceship*)obj)->setFillColor(Color::Red);
			cout << "asteroid collided into ship" << endl;
		}
		else if (obj->getTag() == "laser") {
			((Laser*)obj)->setEnabled(false);
			this->enabled = false;
			cout << "asteroid collided into laser" << endl;
		}
	}
}

Vector2f Asteroid::getCenter() {
	return this->getPosition();
}

float Asteroid::getCollisionRadius() {
	return this->getRadius();
}

bool Asteroid::isEnabled() {
	return enabled;
}

int Asteroid::getSize() {
	return size;
}

void Asteroid::setSize(int size) {
	this->size = size;
}