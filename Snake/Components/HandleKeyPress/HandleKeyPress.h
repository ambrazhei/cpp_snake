#pragma once

#include <SFML/Graphics.hpp>
#include <stdlib.h>

#include "../FieldParams/FieldParams.h"

using namespace FieldParams;

struct HandleKeyPress
{
	Direction static handleKeyboardEvent(
		sf::Event& event,
		Direction initiadDirection,
		bool& isGameOver
	);
};

