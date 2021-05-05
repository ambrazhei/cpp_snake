#pragma once

#include <SFML/Graphics.hpp>
#include "FieldParams/FieldParams.h"

using namespace FieldParams;

class HandleKeyboardEvents
{
	int static handleKeyPress(
		sf::Event& event, 
		FieldParams::Direction& initialDirection,
		bool& isGameOver
	) {
		FieldParams::Direction tempDirection = initialDirection;

		switch (event.key.code) {
			case sf::Keyboard::Up:
				if (initialDirection != Direction::DOWN) {
					tempDirection = Direction::UP;
				}
				break;
			case sf::Keyboard::Down:
				if (initialDirection != Direction::UP) {
					tempDirection = Direction::DOWN;
				}
				break;
			case sf::Keyboard::Left:
				if (initialDirection != Direction::RIGHT) {
					tempDirection = Direction::LEFT;
				}
				break;
			case sf::Keyboard::Right:
				if (initialDirection != Direction::LEFT) {
					tempDirection = Direction::RIGHT;
				}
				break;
			case sf::Keyboard::Escape:
				isGameOver = true;
				break;
			}
		return static_cast<int>(tempDirection);
	}
};
