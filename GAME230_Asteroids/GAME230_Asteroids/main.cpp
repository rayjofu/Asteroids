#include <SFML/Graphics.hpp>
#include "Asteroid.h"
#include <vector>
#include <random>
#include <iostream>
#include "BucketGrid.h"
#include "Spaceship.h"
#include "Laser.h"

using namespace sf;
using namespace std;

void add_asteroid(int size, Vector2f pos);
void create_objects(int n);
void delete_objects();
void update_state();
void render_frame();

float dt;
vector<GameObject*> objects;
Spaceship* ship;
BucketGrid grid;
short state;
float respawnTimer;
short maxLasers;
float laserTimer;
short numAsteroids;
short level;
short initial_asteroids;
short window_offset = 100;
RenderWindow window(VideoMode(1000, 1000 + window_offset), "Asteroids");
RectangleShape separator;
int score;
Text score_text;
Text lives_text;
Font text_font;

int main()
{
	srand(time(NULL));
	initial_asteroids = 1;
	state = 0;
	level = 0;
	respawnTimer = 0.f;
	laserTimer = 0.5f;
	maxLasers = 5;
	score = 0;

	if (!text_font.loadFromFile("ARIALUNI.TTF")) {
		cout << "File 'ARIALUNI.TFF' not found!" << endl;
	}
	score_text.setFont(text_font);
	score_text.setString("0");
	score_text.setOrigin(score_text.getLocalBounds().left + score_text.getLocalBounds().width, score_text.getLocalBounds().top);
	score_text.setPosition(950, 1040);
	score_text.setColor(Color::White);

	

	create_objects(level + initial_asteroids);

	lives_text.setFont(text_font);
	lives_text.setString("Lives: x" + to_string(ship->getLives()));
//	lives_text.setOrigin(lives_text.getLocalBounds().left + lives_text.getLocalBounds().width, lives_text.getLocalBounds().top);
	lives_text.setPosition(1, 1040);
	lives_text.setColor(Color::White);

	separator = RectangleShape();
	separator.setSize(Vector2f(window.getSize().x, 1.f));
	separator.setPosition(0.f, 1000.f);
	
	Clock clock;

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
		}

		dt = clock.restart().asSeconds();

		update_state();
		render_frame();
	}

	delete_objects();
	return 0;
}

void add_asteroid(int size, Vector2f pos) {
	Asteroid* asteroid = new Asteroid("asteroid");
	asteroid->setSize(size);

	int radius = 15.f * pow(2, size);
	asteroid->setRadius(radius);
	asteroid->setOrigin(radius, radius);
	asteroid->setFillColor(Color::Yellow);
	asteroid->setPosition(pos);

	int signX, signY;
	signX = rand() % 2 + 1;
	signX = pow(-1, signX);
	signY = rand() % 2 + 1;
	signY = pow(-1, signY);
	asteroid->setSpeed(50.f * (3 - size) * sqrt(2));
	asteroid->setVelocity(Vector2f(signX * (3 - size) * 50.f, signY * (3 - size) * 50.f));

	objects.push_back(asteroid);
	grid.bucket_add(grid.getBucket(asteroid->getCenter()), asteroid);
}

void create_objects(int n) {
	delete_objects();
	
	float radius = 30.f;
	ship = new Spaceship("spaceship");
	ship->setLives(3);
	ship->setRadius(radius);
	ship->setOrigin(radius, radius);
	ship->setFillColor(Color(0, 0, 255, 255));
	ship->setPosition(Vector2f(window.getSize().x / 2, (window.getSize().y - window_offset) / 2));
	ship->setSpeed(300.f);
	ship->setVelocity(Vector2f(0.f, 0.f));
	objects.push_back(ship);
	grid.bucket_add(grid.getBucket(ship->getCenter()), ship);

	int randX, randY;
	for (int i = 0; i < n; ++i) {
		randX = rand() % window.getSize().x;
		randY = rand() % (window.getSize().y - window_offset);
		
		// make sure asteroid does not spawn on ship
		while ((window.getSize().x / 2 - randX) * (window.getSize().x / 2 - randX) +
			(window.getSize().y / 2 - randY) * (window.getSize().y / 2 - randY) < 90 * 90) {
			randX = rand() % window.getSize().x;
			randY = rand() % (window.getSize().y - window_offset);
		}
//		add_asteroid(rand() % 3, Vector2f(randX, randY));
		add_asteroid(2, Vector2f(randX, randY));
	}

	numAsteroids = n;
}

void delete_objects() {
	for (GameObject* obj : objects) {
		grid.bucket_remove(grid.getBucket(obj->getCenter()), obj);
		delete obj;
	}
	objects.clear();
}

void update_state() {
	if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up)) {
		ship->handleInput(Keyboard::Up, dt);
	}
	if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)) {
		ship->handleInput(Keyboard::Left, dt);
	}
	if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)) {
		ship->handleInput(Keyboard::Right, dt);
	}

	laserTimer += dt;
	if (ship->isEnabled() && Keyboard::isKeyPressed(Keyboard::Space)) {
		if (laserTimer > 0.3f) {
			Laser* laser = new Laser("laser");
			laser->setRadius(10.f);
			laser->setSpeed(900.f);
			laser->setOrigin(laser->getRadius(), laser->getRadius());
			laser->setPosition(ship->getPosition());
			Vector2f vel = Vector2f(sin(ship->getRotation() * 3.14 / 180), -cos(ship->getRotation() * 3.14 / 180));
			laser->setVelocity(vel);
			objects.push_back(laser);
			grid.bucket_add(grid.getBucket(laser->getCenter()), laser);
			laserTimer = 0.f;
		}
	}

	for (vector<GameObject*>::iterator it = objects.begin(); it != objects.end();) {
		GameObject* obj = (*it);

		if (!obj->isEnabled()) {
			if (obj->getTag() == "laser") {
				it = objects.erase(remove(objects.begin(), objects.end(), obj), objects.end());
				grid.bucket_remove(grid.getBucket(obj->getCenter()), obj);
				delete obj;
				continue;
			}

			if (obj->getTag() == "asteroid") {
				Asteroid* asteroid = (Asteroid*)obj;
				
				score += 100;
				score_text.setString(to_string(score));
				if (asteroid->getSize() == 0) {
					it = objects.erase(remove(objects.begin(), objects.end(), obj), objects.end());
					grid.bucket_remove(grid.getBucket(obj->getCenter()), obj);
					--numAsteroids;
					delete obj;
					continue;
				}

				Vector2f pos = asteroid->getPosition();
				pos.x -= asteroid->getRadius() / 2 - 1;
				add_asteroid(asteroid->getSize() - 1, pos);

				pos = asteroid->getPosition();
				pos.x += asteroid->getRadius() / 2 + 1;
				add_asteroid(asteroid->getSize() - 1, pos);
				
				++numAsteroids;

				it = objects.erase(remove(objects.begin(), objects.end(), obj), objects.end());
				grid.bucket_remove(grid.getBucket(obj->getCenter()), obj);
				delete obj;
				continue;
			}

		}

		Vector2i curBucket = grid.getBucket(obj->getCenter());
		Vector2u windowPos = Vector2u(window.getSize().x, window.getSize().y - window_offset);
		obj->update(windowPos, dt);
		Vector2i newBucket = grid.getBucket(obj->getCenter());
		if (curBucket != newBucket) {
			grid.bucket_remove(curBucket, obj);
			grid.bucket_add(newBucket, obj);
		}
		grid.detect_collisions(obj, newBucket);

		++it;
	}

	if (ship->getLives() < 0) {
		
	}
	else if (numAsteroids == 0) {
		cout << "level cleared" << endl;
		create_objects(++level + initial_asteroids);
	}
	else if (!ship->isEnabled()) {
		lives_text.setString("Lives: x" + to_string(ship->getLives()));
		if (respawnTimer < 3.f) {
			respawnTimer += dt;
		}
		else {
			respawnTimer = 0.f;
			ship->setFillColor(Color::Blue);
			ship->setEnabled(true);
		}
	}
}

void render_frame() {
	window.clear();

	window.draw(separator);
	window.draw(lives_text);
	window.draw(score_text);
	for (vector<GameObject*>::iterator it = objects.begin(); it != objects.end();) {
		(*it)->draw(window);
		++it;
	}

	window.display();
}