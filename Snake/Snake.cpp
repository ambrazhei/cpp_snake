// Snake.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <SFML/Graphics.hpp>
#include <windows.h>
#include <stdlib.h>


enum FieldType
{
	EMPTY_CELL_TYPE = 0,
	FRUIT_CELL_TYPE = -1,
};

enum Direction
{
	UP, RIGHT, DOWN, LEFT
};


struct FieldParams
{
	static const int FIELD_SIZE_X = 35;
	static const int FIELD_SIZE_Y = 25;
	static const int CELL_SIZE = 32;

	static const int WINDOW_WIDTH = FIELD_SIZE_X * CELL_SIZE;
	static const int WINDOW_HEIGHT = FIELD_SIZE_Y * CELL_SIZE;
};

int field[FieldParams::FIELD_SIZE_Y][FieldParams::FIELD_SIZE_X];

int snakePosX = FieldParams::FIELD_SIZE_X / 2;
int snakePosY = FieldParams::FIELD_SIZE_Y / 2;
int snakeLength = 4;
int snakeDirection = Direction::RIGHT;
bool isGameOver = false;


int getRandomEmptyCell() {
	int counter = 0;

	for (int y = 0; y < FieldParams::FIELD_SIZE_Y; y += 1)
	{
		for (int x = 0; x < FieldParams::FIELD_SIZE_X; x += 1)
		{
			if (field[y][x] == FieldType::EMPTY_CELL_TYPE) {
				counter += 1;
			}
		}
	}

	int targetIndex = rand() % counter;
	int emptyCellIndex = 0;

	for (int y = 0; y < FieldParams::FIELD_SIZE_Y; y += 1) {
		for (int x = 0; x < FieldParams::FIELD_SIZE_X; x += 1) {
			if (field[y][x] == FieldType::EMPTY_CELL_TYPE) {
				if (emptyCellIndex == targetIndex) {
					return y * FieldParams::FIELD_SIZE_X + x;
				}
				emptyCellIndex += 1;
			}
		}
	}
	return FieldType::FRUIT_CELL_TYPE;
}

void renderFruit()
{
	int fruitPos = getRandomEmptyCell();

	if (fruitPos != -1) {
		fruitPos = getRandomEmptyCell();
	}

	field[fruitPos / FieldParams::FIELD_SIZE_X][fruitPos % FieldParams::FIELD_SIZE_X] = FieldType::FRUIT_CELL_TYPE;
}

void prepareField()
{
	for (int y = 0; y < FieldParams::FIELD_SIZE_Y; y += 1)
	{
		for (int x = 0; x < FieldParams::FIELD_SIZE_X; x += 1)
		{
			field[y][x] = FieldType::EMPTY_CELL_TYPE;
		}
	}

	for (int i = 0; i < snakeLength; i++)
	{
		field[snakePosY][snakePosX - 1] = snakeLength - i;
	}

	renderFruit();
}

void render(sf::RenderWindow &window)
{
	sf::Texture emptyTexture;
	emptyTexture.loadFromFile("../assets/empty.png");
	sf::Sprite empty;
	empty.setTexture(emptyTexture);

	sf::Texture snakeTexture;
	snakeTexture.loadFromFile("../assets/snake.png");
	sf::Sprite snake;
	snake.setTexture(snakeTexture);

	sf::Texture fruitTexture;
	fruitTexture.loadFromFile("../assets/apple.png");
	sf::Sprite fruit;
	fruit.setTexture(fruitTexture);

	for (int y = 0; y < FieldParams::FIELD_SIZE_Y; y++) {
		for (int x = 0; x < FieldParams::FIELD_SIZE_X; x++) {
			switch (field[y][x]) {
				case FieldType::EMPTY_CELL_TYPE:
					empty.setPosition(float(x * FieldParams::CELL_SIZE), float(y * (FieldParams::CELL_SIZE)));
					window.draw(empty);
					break;
				case FieldType::FRUIT_CELL_TYPE:
					fruit.setPosition(float(x * FieldParams::CELL_SIZE), float(y * (FieldParams::CELL_SIZE)));
					window.draw(fruit);
					break;
				default:
					snake.setPosition(float(x * FieldParams::CELL_SIZE), float(y * FieldParams::CELL_SIZE));
					window.draw(snake);
			}
		}
	}
}

void growSnake() {
	for (int y = 0; y < FieldParams::FIELD_SIZE_Y; y += 1)	{
		for (int x = 0; x < FieldParams::FIELD_SIZE_X; x += 1)	{
			if (field[y][x] > FieldType::EMPTY_CELL_TYPE) {
				field[y][x] += 1;
			}
		}
	}
}

void move()
{
	switch (snakeDirection)	
	{
		case Direction::UP:
			snakePosY -= 1;
			if (snakePosY < 0) {
				snakePosY = FieldParams::FIELD_SIZE_Y - 1;
			}
			break;
		case Direction::DOWN:
			snakePosY += 1;
			if (snakePosY > FieldParams::FIELD_SIZE_Y - 1) {
				snakePosY = 0;
			}
			break;
		case Direction::RIGHT:
			snakePosX += 1;
			if (snakePosX > FieldParams::FIELD_SIZE_X - 1) {
				snakePosX = 0;
			}
			break;
		case Direction::LEFT:
			snakePosX -= 1;
			if (snakePosX < 0) {
				snakePosX = FieldParams::FIELD_SIZE_X - 1;
			}
			break;

	}

	if (field[snakePosY][snakePosX] != FieldType::EMPTY_CELL_TYPE) {
		switch (field[snakePosY][snakePosX]) {
			case FieldType::FRUIT_CELL_TYPE:
				snakeLength += 1;
				growSnake();
				renderFruit();
				break;
			default:
				isGameOver = true;
		}
	}

	field[snakePosY][snakePosX] = snakeLength + 1;

	for (int y = 0; y < FieldParams::FIELD_SIZE_Y; y += 1)
	{
		for (int x = 0; x < FieldParams::FIELD_SIZE_X; x += 1)
		{
			if (field[y][x] > FieldType::EMPTY_CELL_TYPE) {
				field[y][x] -= 1;
			}
		}
	}
}


void handleKeyPress() 
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		if (snakeDirection != Direction::DOWN) {
			snakeDirection = Direction::UP;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		if (snakeDirection != Direction::RIGHT) {
			snakeDirection = Direction::LEFT;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		if (snakeDirection != Direction::UP) {
			snakeDirection = Direction::DOWN;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		if (snakeDirection != Direction::LEFT) {
			snakeDirection = Direction::RIGHT;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		isGameOver = true;
	}
}

int main()
{
	srand(time(NULL));

	ShowWindow(GetConsoleWindow(), SW_HIDE);
	sf::RenderWindow window(sf::VideoMode(FieldParams::WINDOW_WIDTH, FieldParams::WINDOW_HEIGHT), "Snake", sf::Style::Close);

	prepareField();

	while (window.isOpen()) 
	{
		sf::Event event;
		while (window.pollEvent(event)) 
		{
			if (event.type == sf::Event::Closed) 
			{
				window.close();
			}
		}

		move();

		if (isGameOver) {
			window.close();
		}

		window.clear(sf::Color(103, 212, 168));
		handleKeyPress();

		render(window);
		window.display();

		sf::sleep(sf::milliseconds(150));
	}


	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
