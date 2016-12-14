#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Asteroid.h"
#include <vector>
#include <random>
#include <iostream>
#include "BucketGrid.h"
#include "Spaceship.h"
#include "Laser.h"
#include "Powerup.h"

using namespace sf;
using namespace std;

void add_asteroid(int size, Vector2f pos, int type);
void add_powerup(int type, Vector2f pos);
void create_objects(int n);
void delete_asteroids();
void update_state();
void render_frame();

float dt;
vector<GameObject*> objects;
Spaceship* ship;
BucketGrid grid;
float respawnTimer;
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
Text level_text;
Font text_font;
Texture texture_spaceship;
Texture texture_spaceship2;
bool booster;
Texture texture_laser;
Texture texture_asteroid;
Texture texture_asteroid2;
int lives;
bool toggle_menu;
RectangleShape menu;
RectangleShape menu_bg;
Text restart;
Text text_exit;
float menu_timer;
bool gameover_flag;
RectangleShape gameover_outline;
RectangleShape gameover_bg;
Text gameover;
Text gameover_score;
FloatRect bounds;
int initial_lives;
Texture texture_star;
Texture texture_shield;
Texture texture_laser_upgrade;
int laser_speed;
bool laser_upgrade;
Sound fire;
Sound smallExplosion;
Sound mediumExplosion;
Sound thrust;
Sound victory;
SoundBuffer fire_buffer;
SoundBuffer smallExplosion_buffer;
SoundBuffer mediumExplosion_buffer;
SoundBuffer thrust_buffer;
SoundBuffer victory_buffer;

int main()
{
	srand(time(NULL));
	initial_asteroids = 2;
	level = 0;
	respawnTimer = 0.f;
	laserTimer = 0.5f;
	score = 0;
	lives = initial_lives = 3;
	booster = true;
	toggle_menu = false;
	gameover_flag = false;
	ship = NULL;
	laser_speed = 700.f;
	laser_upgrade = false;

	if (!text_font.loadFromFile("ARIALUNI.TTF")) {
		cout << "File 'ARIALUNI.TFF' not found!" << endl;
	}
	if (!texture_spaceship.loadFromFile("spaceship.png")) {
		cout << "File 'spaceship.png' not found!" << endl;
	}
	if (!texture_spaceship2.loadFromFile("spaceship2.png")) {
		cout << "File 'spaceship2.png' not found!" << endl;
	}
	if (!texture_laser.loadFromFile("laser.png")) {
		cout << "File 'laser.png' not found!" << endl;
	}
	if (!texture_asteroid.loadFromFile("asteroid.png")) {
		cout << "File 'asteroid.png' not found!" << endl;
	}
	if (!texture_asteroid2.loadFromFile("asteroid2.png")) {
		cout << "File 'asteroid2.png' not found!" << endl;
	}
	if (!texture_star.loadFromFile("star.png")) {
		cout << "File 'star.png' not found!" << endl;
	}
	if (!texture_shield.loadFromFile("shield.png")) {
		cout << "File 'shield.png' not found!" << endl;
	}
	if (!texture_laser_upgrade.loadFromFile("laser_upgrade.png")) {
		cout << "File 'laser_upgrade.png' not found!" << endl;
	}
	if (!fire_buffer.loadFromFile("fire.wav")) {
		cout << "File 'fire.wav' not found!" << endl;
	}
	if (!smallExplosion_buffer.loadFromFile("bangSmall.wav")) {
		cout << "File 'bangSmall.wav' not found!" << endl;
	}
	if (!mediumExplosion_buffer.loadFromFile("bangMedium.wav")) {
		cout << "File 'bangMedium.wav' not found!" << endl;
	}
	if (!thrust_buffer.loadFromFile("thrust.wav")) {
		cout << "File 'thrust.wav' not found!" << endl;
	}
	if (!victory_buffer.loadFromFile("level_complete.wav")) {
		cout << "File 'level_complete.wav' not found!" << endl;
	}
	fire.setBuffer(fire_buffer);
	smallExplosion.setBuffer(smallExplosion_buffer);
	mediumExplosion.setBuffer(mediumExplosion_buffer);
	thrust.setBuffer(thrust_buffer);
	victory.setBuffer(victory_buffer);

	// menu
	menu_bg.setSize(Vector2f(250.f, 200.f));
	menu_bg.setOrigin(125.f, 100.f);
	menu_bg.setPosition(window.getSize().x / 2, (window.getSize().y - window_offset) / 2);
	menu_bg.setFillColor(Color::Red);

	menu.setSize(Vector2f(230.f, 180.f));
	menu.setOrigin(115.f, 90.f);
	menu.setPosition(window.getSize().x / 2, (window.getSize().y - window_offset) / 2);
	menu.setFillColor(Color::Black);

	restart.setFont(text_font);
	restart.setString("New Game [N]");
	restart.setFillColor(Color::Green);
	bounds = restart.getLocalBounds();
	restart.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
	restart.setPosition(window.getSize().x / 2, (window.getSize().y - window_offset) / 2 - 30);
	
	text_exit.setFont(text_font);
	text_exit.setString("Exit [X]");
	text_exit.setFillColor(Color::Yellow);
	bounds = text_exit.getLocalBounds();
	text_exit.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
	text_exit.setPosition(window.getSize().x / 2, (window.getSize().y - window_offset) / 2 + 30);

	gameover_outline.setSize(Vector2f(300.f, 200.f));
	gameover_outline.setOrigin(150.f, 100.f);
	gameover_outline.setPosition(window.getSize().x / 2, (window.getSize().y - window_offset) / 2 - 220.f);
	gameover_outline.setFillColor(Color::Red);

	gameover_bg.setSize(Vector2f(280.f, 180.f));
	gameover_bg.setOrigin(140.f, 90.f);
	gameover_bg.setPosition(window.getSize().x / 2, (window.getSize().y - window_offset) / 2 - 220.f);
	gameover_bg.setFillColor(Color::Black);

	gameover.setString("GAMEOVER!");
	gameover.setFont(text_font);
	gameover.setFillColor(Color::Yellow);
	bounds = gameover.getLocalBounds();
	gameover.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
	gameover.setPosition(window.getSize().x / 2, (window.getSize().y - window_offset) / 2 - 250.f);

	gameover_score.setString(to_string(score));
	gameover_score.setFont(text_font);
	gameover_score.setFillColor(Color::Magenta);
	bounds = gameover_score.getLocalBounds();
	gameover_score.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
	gameover_score.setPosition(window.getSize().x / 2, (window.getSize().y - window_offset) / 2 - 190.f);

	menu_timer = 3.f;

	create_objects(level + initial_asteroids);

	separator = RectangleShape();
	separator.setSize(Vector2f(window.getSize().x, 1.f));
	separator.setPosition(0.f, 1000.f);

	lives_text.setFont(text_font);
	lives_text.setString("Lives: x" + to_string(ship->getLives()));
	bounds = lives_text.getLocalBounds();
	lives_text.setOrigin(0, bounds.top + bounds.height/2.f);
	lives_text.setPosition(50, 1050);
	lives_text.setColor(Color::Blue);

	level_text.setFont(text_font);
	level_text.setString("Level " + to_string(level));
	level_text.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
	level_text.setPosition(window.getSize().x / 2.f, 1050);
	level_text.setColor(Color::Green);

	score_text.setFont(text_font);
	score_text.setString("0");
	bounds = score_text.getLocalBounds();
	score_text.setOrigin(bounds.left + bounds.width, bounds.top + bounds.height / 2.f);
	score_text.setPosition(900, 1050);
	score_text.setColor(Color::Magenta);	
	
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

	delete_asteroids();
	delete ship;
	return 0;
}

void add_powerup(int type, Vector2f pos) {
	Powerup* powerup = new Powerup("powerup");
	powerup->setType(type);
	powerup->setPosition(pos);
	powerup->setRadius(20.f);
	powerup->setOrigin(20.f, 20.f);

	// shield
	if (type == 1) {
		powerup->setTexture(&texture_shield);
	}
	// invincibility
	else if (type == 2) {
		powerup->setTexture(&texture_star);
	}
	// laser upgrade
	else if (type == 3) {
		powerup->setTexture(&texture_laser_upgrade);
	}

	objects.push_back(powerup);
	grid.bucket_add(grid.getBucket(powerup->getCenter()), powerup);
}

void add_asteroid(int size, Vector2f pos, int type) {
	Asteroid* asteroid = new Asteroid("asteroid");
	asteroid->setSize(size);

	int radius = 15.f * pow(2, size);
	asteroid->setRadius(radius);
	asteroid->setOrigin(radius, radius);
	asteroid->setPosition(pos);
	asteroid->setType(type);

	if (type == 2) {
		asteroid->setLife(2);
		asteroid->setTexture(&texture_asteroid2);
	}
	else {
		asteroid->setLife(1);
		asteroid->setTexture(&texture_asteroid);
	}

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
	delete_asteroids();

	if (ship == NULL) {
		float radius = 30.f;
		ship = new Spaceship("spaceship");
		ship->setLives(lives);
		ship->setRadius(radius);
		ship->setOrigin(radius, radius);
		ship->setFillColor(Color::White);
		ship->setPosition(Vector2f(window.getSize().x / 2, (window.getSize().y - window_offset) / 2));
		ship->setSpeed(300.f);
		ship->setVelocity(Vector2f(0.f, 0.f));
		ship->setTexture(&texture_spaceship);
		ship->setPowerup(0);
		objects.push_back(ship);
		grid.bucket_add(grid.getBucket(ship->getCenter()), ship);
	}

	int randX, randY;
	for (int i = 0; i < n; ++i) {
		randX = rand() % window.getSize().x;
		randY = rand() % (window.getSize().y - window_offset);
		
		// make sure asteroid does not spawn on ship
		while ((ship->getPosition().x - randX) * (ship->getPosition().x - randX) +
			(ship->getPosition().y - randY) * (ship->getPosition().y - randY) < 200 * 200) {
			randX = rand() % window.getSize().x;
			randY = rand() % (window.getSize().y - window_offset);
		}
//		add_asteroid(rand() % 3, Vector2f(randX, randY));
		if (i % 5 == 0) {
			add_asteroid(2, Vector2f(randX, randY), 2);
		}
		else {
			add_asteroid(2, Vector2f(randX, randY), 1);
		}
	}

	numAsteroids = n;
}

void delete_asteroids() {
	for (vector<GameObject*>::iterator it = objects.begin(); it != objects.end();) {
		GameObject* obj = (*it);
		if (obj->getTag() == "spaceship") {
			++it;
			continue;
		}
		grid.bucket_remove(grid.getBucket(obj->getCenter()), obj);
		it = objects.erase(it);
		delete obj;
	}
}

void update_state() {
	menu_timer += dt;
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		if (menu_timer > 0.2f) {
			toggle_menu = !toggle_menu;
			menu_timer = 0;
		}
	}

	if (toggle_menu) {
		if (Keyboard::isKeyPressed(Keyboard::N)) {
			level = 0;
			level_text.setString("Level " + to_string(level));
			lives = initial_lives;
			lives_text.setString("Lives: x" + to_string(lives));
			ship->setLives(lives);
			ship->setPosition(window.getSize().x / 2.f, (window.getSize().y - window_offset)/2.f);
			ship->setVelocity(Vector2f(0.f, 0.f));
			ship->setFillColor(Color::White);
			score = 0;
			score_text.setString(to_string(score));
			create_objects(level + initial_asteroids);
			gameover_flag = false;
			toggle_menu = false;
		}
		if (Keyboard::isKeyPressed(Keyboard::X)) {
			window.close();
		}
		dt = 0.f;
		return;
	}

	if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up)) {
		if (thrust.getStatus() != Sound::Status::Playing) {
			thrust.play();
		}
		ship->handleInput(Keyboard::Up, dt);
		if (booster) {
			ship->setTexture(&texture_spaceship2);
		}
		else {
			ship->setTexture(&texture_spaceship);
		}
		booster = !booster;
	}
	if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)) {
		ship->handleInput(Keyboard::Left, dt);
	}
	if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)) {
		ship->handleInput(Keyboard::Right, dt);
	}

	laserTimer += dt;
	if ((ship->isEnabled() || !ship->isEnabled() && ship->getPowerup() == 2 || !ship->isEnabled() && ship->getPowerup() == 1) && Keyboard::isKeyPressed(Keyboard::Space)) {
		if (!laser_upgrade && laserTimer > 0.3f || laser_upgrade && laserTimer > 0.15f) {
			if (fire.getStatus() != Sound::Status::Playing) {
				fire.play();
			}
			Laser* laser = new Laser("laser");
			laser->setRadius(10.f);
			laser->setSpeed(laser_speed);
			laser->setOrigin(laser->getRadius(), laser->getRadius());
			laser->setPosition(ship->getPosition());
			laser->setRotation(ship->getRotation());
			laser->setTexture(&texture_laser);
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

			else if (obj->getTag() == "asteroid") {
				Asteroid* asteroid = (Asteroid*)obj;
				
				score += 100;
				score_text.setString(to_string(score));
				if (asteroid->getSize() == 0) {
					smallExplosion.play();
					it = objects.erase(remove(objects.begin(), objects.end(), obj), objects.end());
					grid.bucket_remove(grid.getBucket(obj->getCenter()), obj);
					--numAsteroids;
					delete obj;
					continue;
				}

				mediumExplosion.play();

				Vector2f pos = asteroid->getPosition();
				int type = asteroid->getType();
				int size = asteroid->getSize();
				int radius = asteroid->getRadius();

				Vector2f newPos;
				newPos = Vector2f(pos.x - radius / 2 - 1, pos.y);
				pos.x -= radius / 2 - 1;
				add_asteroid(size - 1, newPos, type);

				newPos = Vector2f(pos.x + radius / 2 + 1, pos.y);
				pos.x += radius / 2 + 1;
				add_asteroid(size - 1, newPos, type);

				int random = rand() % 10 + 1;
				if (random == 1 || random == 2 || random == 3) {
					add_powerup(random, pos);
				}
				
				++numAsteroids;

				it = objects.erase(remove(objects.begin(), objects.end(), obj), objects.end());
				grid.bucket_remove(grid.getBucket(obj->getCenter()), obj);
				delete obj;
				
				continue;
			}

			else if (obj->getTag() == "powerup") {
				Powerup* powerup = ((Powerup*)obj);
				if (powerup->getType() == 1) {
					ship->setFillColor(Color::Green);
					ship->setPowerup(1);
				}
				else if (powerup->getType() == 2) {
					ship->setFillColor(Color::Yellow);
					ship->setPowerup(2);
				}
				else if (powerup->getType() == 3) {
					laser_upgrade = true;
					ship->setPowerup(3);
				}

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
		ship->setFillColor(Color::Black);
		gameover_score.setString(to_string(score));
		bounds = gameover_score.getLocalBounds();
		gameover_score.setOrigin(bounds.left + bounds.width/2.f, bounds.top + bounds.height/2.f);

		gameover_flag = true;
		toggle_menu = true;
	}
	else if (numAsteroids == 0) {
		cout << "level cleared" << endl;
		create_objects(++level + initial_asteroids);
		level_text.setString("Level " + to_string(level));
	}
	else if (!ship->isEnabled()) {
		if (ship->getPowerup() == 0 || ship->getPowerup() == 3) {
			lives = ship->getLives();
			lives_text.setString("Lives: x" + to_string(lives));
			ship->setPowerup(0);
		}

		if (ship->getPowerup() != 2 && respawnTimer < 3.f || ship->getPowerup() == 2 && respawnTimer < 6.f) {
			respawnTimer += dt;
		}
		else {
			respawnTimer = 0.f;
			ship->setFillColor(Color::White);
			ship->setEnabled(true);
			ship->setPowerup(0);
		}
	}
}

void render_frame() {
	window.clear();

	window.draw(separator);
	window.draw(lives_text);
	window.draw(level_text);
	window.draw(score_text);
	for (vector<GameObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		(*it)->draw(window);
	}


	if (gameover_flag) {
		window.draw(gameover_outline);
		window.draw(gameover_bg);
		window.draw(gameover);
		window.draw(gameover_score);
	}
	
	if (toggle_menu) {
		window.draw(menu_bg);
		window.draw(menu);
		window.draw(restart);
		window.draw(text_exit);
	}

	window.display();
}