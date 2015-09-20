#include "Resources.hpp"

// sf::Texture		Resources::....

std::vector<SpriteSheetDescription> Resources::descriptions;

void Resources::load() {
	//...loadFromFile();

	descriptions = std::vector<SpriteSheetDescription>(spriteSheetsQtt);
	descriptions[0] = (loadDescription("linkSheet"));
}

SpriteSheetDescription Resources::loadDescription(std::string fileName) {
	std::string file = fileName + TEXTUREDESCRIPTIONEXTENSION;
	SpriteSheetDescription ret;
	// leer el fichero
}