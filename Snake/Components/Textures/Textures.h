#pragma once 

#include <SFML/Graphics.hpp>
#include <stdlib.h>

struct Textures
{
	sf::Texture emptyTexture;
	sf::Sprite empty;

	sf::Texture snakeTexture;
	sf::Sprite snake;

	sf::Texture fruitTexture;
	sf::Sprite fruit;

	Textures(std::string emptyPath, std::string snakePath, std::string fruitPath);
};