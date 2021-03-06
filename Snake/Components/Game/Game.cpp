#pragma once

#include <functional>

#include "../FieldParams/FieldParams.h"
#include "../Textures/Textures.h"

#include "Game.h"

void Game::iterateOverField(std::function<void(int, int)> cb) {
	for (int y = 0; y < FIELD_SIZE_Y; y += 1) {
		for (int x = 0; x < FIELD_SIZE_X; x += 1) {
			cb(y, x);
		}
	}
}

void Game::iterateOverField(std::function<void(int, int)> cb, bool condition) {
	for (int y = 0; y < FIELD_SIZE_Y; y += 1) {
		for (int x = 0; x < FIELD_SIZE_X; x += 1) {
			cb(y, x);
			if (condition == true) {
				break;
			}
		}
	}
}

int Game::getRandomEmptyCell() {
	int numberOfEmpty = 0;
	auto& fieldLink = field;

	iterateOverField([&numberOfEmpty, &fieldLink](int y, int x) {
		if (fieldLink[y][x] == FieldType::EMPTY_CELL_TYPE) {
			numberOfEmpty += 1;
		}
		});

	int targetIndex = rand() % numberOfEmpty;
	int emptyCellIndex = 0;
	int emptyCellIndexForReturn = -1;

	iterateOverField([&targetIndex, &fieldLink, &emptyCellIndex, &emptyCellIndexForReturn](int y, int x) {
		if (fieldLink[y][x] == FieldType::EMPTY_CELL_TYPE) {
			if (emptyCellIndex == targetIndex) {
				emptyCellIndexForReturn = y * FIELD_SIZE_X + x;
			}

			emptyCellIndex += 1;
		}
		}, emptyCellIndexForReturn != -1);

	return (emptyCellIndexForReturn != -1) ? emptyCellIndexForReturn : FieldType::FRUIT_CELL_TYPE;
}

void Game::createFruit()
{
	int fruitPos = getRandomEmptyCell();

	if (fruitPos != -1) {
		fruitPos = getRandomEmptyCell();
	}

	field[fruitPos / FIELD_SIZE_X][fruitPos % FIELD_SIZE_X] = FieldType::FRUIT_CELL_TYPE;
}

void Game::prepareField()
{
	auto& fieldLink = field;

	iterateOverField([&fieldLink](int y, int x) {
		fieldLink[y][x] = FieldType::EMPTY_CELL_TYPE;
		});


	for (int i = 0; i < snakeLength; i++) {
		field[snakePosY][snakePosX - 1] = snakeLength - i;
	}

	createFruit();
}

void Game::render(sf::RenderWindow& window, Textures& textures)
{
	for (int y = 0; y < FIELD_SIZE_Y; y++) {
		for (int x = 0; x < FIELD_SIZE_X; x++) {
			switch (field[y][x]) {
			case FieldType::EMPTY_CELL_TYPE:
				textures.empty.setPosition(float(x * CELL_SIZE), float(y * (CELL_SIZE)));
				window.draw(textures.empty);
				break;
			case FieldType::FRUIT_CELL_TYPE:
				textures.fruit.setPosition(float(x * CELL_SIZE), float(y * (CELL_SIZE)));
				window.draw(textures.fruit);
				break;
			default:
				textures.snake.setPosition(float(x * CELL_SIZE), float(y * CELL_SIZE));
				window.draw(textures.snake);
			}
		}
	}
}

void Game::growSnake() {
	auto& fieldLink = field;

	iterateOverField([&fieldLink](int y, int x) {
		if (fieldLink[y][x] > FieldType::EMPTY_CELL_TYPE) {
			fieldLink[y][x] += 1;
		}
		});
}

void Game::move()
{
	switch (snakeDirection) {
	case Direction::UP:
		snakePosY -= 1;
		if (snakePosY < 0) {
			snakePosY = FIELD_SIZE_Y - 1;
		}
		break;
	case Direction::DOWN:
		snakePosY += 1;
		if (snakePosY > FIELD_SIZE_Y - 1) {
			snakePosY = 0;
		}
		break;
	case Direction::RIGHT:
		snakePosX += 1;
		if (snakePosX > FIELD_SIZE_X - 1) {
			snakePosX = 0;
		}
		break;
	case Direction::LEFT:
		snakePosX -= 1;
		if (snakePosX < 0) {
			snakePosX = FIELD_SIZE_X - 1;
		}
		break;
	}

	if (field[snakePosY][snakePosX] != FieldType::EMPTY_CELL_TYPE) {
		switch (field[snakePosY][snakePosX]) {
		case FieldType::FRUIT_CELL_TYPE:
			snakeLength += 1;
			growSnake();
			createFruit();
			break;
		default:
			isGameOver = true;
		}
	}

	field[snakePosY][snakePosX] = snakeLength + 1;

	auto& fieldLink = field;

	iterateOverField([&fieldLink](int y, int x) {
		if (fieldLink[y][x] > FieldType::EMPTY_CELL_TYPE) {
			fieldLink[y][x] -= 1;
		}
		});
}
