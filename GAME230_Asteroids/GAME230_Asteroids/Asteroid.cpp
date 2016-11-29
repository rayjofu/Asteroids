#include "Asteroid.h"

using namespace sf;

Asteroid::Asteroid() : CircleShape() {

}

Asteroid::Asteroid(float radius) : CircleShape(radius) {

}

Vector2f Asteroid::getVelocity() {
	return velocity;
}

void Asteroid::setVelocity(Vector2f vel) {
	velocity = vel;
}

void Asteroid::update(Vector2u windowSize, float dt) {
	Vector2f asteroidPos = this->getPosition();
	Vector2f vel = this->getVelocity();
	if (asteroidPos.x < 0 && vel.x < 0) {
		asteroidPos.x = windowSize.x;
	}
	if (asteroidPos.x > windowSize.x && vel.x > 0) {
		asteroidPos.x = 0.f;
	}
	if (asteroidPos.y < 0 && vel.y < 0) {
		asteroidPos.y = windowSize.y;
	}
	if (asteroidPos.y > windowSize.y && vel.y > 0) {
		asteroidPos.y = 0.f;
	}
	this->setPosition(asteroidPos + vel * dt);
}

void Asteroid::draw(sf::RenderWindow& window) {
	window.draw(*this);
}

int Asteroid::getRenderBucket() {
	return 0;
}