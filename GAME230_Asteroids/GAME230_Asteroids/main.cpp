#include <SFML/Graphics.hpp>
#include "Asteroid.h"
#include <vector>

using namespace sf;
using namespace std;

void update_state();
void render_frame();

RenderWindow window(VideoMode(1200, 1200), "Asteroids");
float dt;
vector<GameObject*> objects;
vector<GameObject*> pool;

int main()
{
	Clock clock;
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}

		dt = clock.restart().asSeconds();

		update_state();
		render_frame();
	}

	return 0;
}

void create_objects() {
	for (int i = 0; i < 10; ++i) {
		objects.push_back(new Asteroid());
		objects[i]
	}

	Asteroid asteroid1(30.f);
	asteroid1.setOrigin(asteroid1.getRadius(), asteroid1.getRadius());
	asteroid1.setFillColor(Color::Green);
	asteroid1.setPosition(Vector2f(100.f, 100.f));
	asteroid1.setVelocity(Vector2f(300.f, 300.f));
	objects.push_back(&asteroid1);

	Asteroid asteroid2(30.f);
	asteroid2.setOrigin(asteroid2.getRadius(), asteroid2.getRadius());
	asteroid2.setFillColor(Color::Blue);
	asteroid2.setPosition(Vector2f(200.f, 300.f));
	asteroid2.setVelocity(Vector2f(-300.f, 300.f));
	objects.push_back(&asteroid2);
}

void delete_objects() {
	for (GameObject* obj : objects) {
		delete obj;
	}
	for (GameObject* obj : pool) {
		delete obj;
	}
}

void update_state() {
	for (GameObject* obj : objects) {
		obj->update(window.getSize(), dt);
	}
}

void render_frame() {
	window.clear();
	
	for (GameObject* obj : objects) {
		obj->draw(window);
	}

	window.display();
}