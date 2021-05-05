#pragma once 

#include <SFML/Graphics.hpp>
#include <stdlib.h>

#include "Textures/Textures.h"

Textures::Textures(std::string emptyPath, std::string snakePath, std::string fruitPath) {
	emptyTexture.loadFromFile(emptyPath);
	empty.setTexture(emptyTexture);

	snakeTexture.loadFromFile(snakePath);
	snake.setTexture(snakeTexture);

	fruitTexture.loadFromFile(fruitPath);
	fruit.setTexture(fruitTexture);
}
