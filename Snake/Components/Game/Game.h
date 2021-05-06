#pragma once

#include <functional>

#include "../FieldParams/FieldParams.h"
#include "../Textures/Textures.h"

using namespace FieldParams;

struct Game {
	int field[FIELD_SIZE_Y][FIELD_SIZE_X];

	int snakePosX = FIELD_SIZE_X / 2;
	int snakePosY = FIELD_SIZE_Y / 2;
	int snakeLength = 4;

	Direction snakeDirection = Direction::RIGHT;
	bool isGameOver = false;

	void iterateOverField(std::function<void(int, int)> cb);
	void iterateOverField(std::function<void(int, int)> cb, bool condition);

	int getRandomEmptyCell();

	void createFruit();

	void prepareField();

	void render(sf::RenderWindow& window, Textures& textures);

	void growSnake();

	void move();
};