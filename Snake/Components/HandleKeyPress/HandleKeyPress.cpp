
#include <SFML/Graphics.hpp>
#include <stdlib.h>

#include "HandleKeyPress.h"
#include "../HandleKeyPress/HandleKeyPress.h"

using namespace FieldParams;

Direction HandleKeyPress::handleKeyboardEvent(
	sf::Event& event,
	Direction initiadDirection,
	bool& isGameOver
) {
	Direction direction = initiadDirection;

	switch (event.key.code) {
		case sf::Keyboard::Up:
			if (initiadDirection != Direction::DOWN) {
				direction = Direction::UP;
			}
			break;
		case sf::Keyboard::Down:
			if (initiadDirection != Direction::UP) {
				direction = Direction::DOWN;
			}
			break;
		case sf::Keyboard::Left:
			if (initiadDirection != Direction::RIGHT) {
				direction = Direction::LEFT;
			}
			break;
		case sf::Keyboard::Right:
			if (initiadDirection != Direction::LEFT) {
				direction = Direction::RIGHT;
			}
			break;
		case sf::Keyboard::Escape:
			isGameOver = true;
			break;
		}

	return direction;
}

