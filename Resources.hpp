#ifndef __RESOURCES_HPP__
#define __RESOURCES_HPP__

#include "utils.hpp"

class Resources {
public:
	static void load();
	//static sf::Texture ...
	static sf::Texture tileSet;
	static sf::Texture textureTest;
	static std::vector<SpriteSheetDescription> descriptions;

private:
	static SpriteSheetDescription loadDescription(std::string fileName);

};

#endif