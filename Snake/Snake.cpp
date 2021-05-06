#include <SFML/Graphics.hpp>
#include <windows.h>
#include <stdlib.h>
#include <functional>

#include "Components/Textures/Textures.h"
#include "Components/FieldParams/FieldParams.h"
#include "Components/HandleKeyPress/HandleKeyPress.h"
#include "Components/Game/Game.h"

using namespace FieldParams;

int main()
{
	srand(time(NULL));

	auto game = Game();
	auto textures = Textures("../assets/empty.png", "../assets/snake.png", "../assets/apple.png");

	Direction direction = game.snakeDirection;

	ShowWindow(GetConsoleWindow(), SW_HIDE);
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Snake", sf::Style::Close);

	game.prepareField();

	while (window.isOpen()) 
	{
		sf::Event event;
		while (window.pollEvent(event)) 
		{
			if (event.type == sf::Event::Closed) 
			{
				window.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				direction = HandleKeyPress::handleKeyboardEvent(event, game.snakeDirection, game.isGameOver);
			}
		}
		game.snakeDirection = direction;

		game.move();

		if (game.isGameOver) {
			window.close();
		}

		window.clear(sf::Color(103, 212, 168));
		game.render(window, textures);

		window.display();

		sf::sleep(sf::milliseconds(100));
	}

	return 0;
}
