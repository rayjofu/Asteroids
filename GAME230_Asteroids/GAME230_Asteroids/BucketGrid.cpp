#include <iostream>
#include "BucketGrid.h";
#include "Spaceship.h"

using namespace sf;
using namespace std;

BucketGrid::BucketGrid() {
	grid = new vector<GameObject*>*[COLUMNS];
	for (int i = 0; i < COLUMNS; ++i) {
		grid[i] = new vector<GameObject*>[ROWS];
	}
}

BucketGrid::~BucketGrid() {
	for (int i = 0; i < COLUMNS; ++i) {
		delete[] grid[i];
	}

	delete[] grid;
}

Vector2i BucketGrid::getBucket(sf::Vector2f pos) {
	int col = int(pos.x / BUCKET_WIDTH);
	if (col < 0) {
		col = 0;
	}
	else if (col >= COLUMNS) {
		col = COLUMNS - 1;
	}

	int row = int(pos.y / BUCKET_HEIGHT);
	if (row < 0) {
		row = 0;
	}
	else if (row >= ROWS) {
		row = ROWS - 1;
	}
	return Vector2i(col, row);
}

void BucketGrid::bucket_add(sf::Vector2i b, GameObject* obj) {
	grid[b.x][b.y].push_back(obj);
}

void BucketGrid::bucket_remove(sf::Vector2i b, GameObject* obj) {
	grid[b.x][b.y].erase(remove(grid[b.x][b.y].begin(), grid[b.x][b.y].end(), obj), grid[b.x][b.y].end());
}

void BucketGrid::detect_collisions(GameObject* obj, sf::Vector2i b) {
	int left = max(b.x - 1, 0);
	int right = min(b.x + 1, COLUMNS - 1);
	int top = max(b.y - 1, 0);
	int bot = min(b.y + 1, ROWS - 1);

	for (int bx = left; bx <= right; ++bx) {
		for (int by = top; by <= bot; ++by) {
			vector<GameObject*>& v = grid[bx][by];
			for (GameObject* o : v) {
				if (o != obj) {
					obj->checkCollisionWith(o);
				}
			}
		}
	}
}