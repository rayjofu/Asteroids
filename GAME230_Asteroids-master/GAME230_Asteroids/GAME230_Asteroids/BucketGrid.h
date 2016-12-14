#pragma once

#include <vector>
#include "GameObject.h"

class BucketGrid {
private:
	const float BUCKET_WIDTH = 200.f;
	const float BUCKET_HEIGHT = 200.f;
	const int COLUMNS = 5;
	const int ROWS = 5;
	std::vector<GameObject*>** grid;
public:
	BucketGrid();
	~BucketGrid();
	sf::Vector2i getBucket(sf::Vector2f pos);
	void bucket_add(sf::Vector2i b, GameObject* obj);
	void bucket_remove(sf::Vector2i b, GameObject* obj);
	void detect_collisions(GameObject* obj, sf::Vector2i b);
};