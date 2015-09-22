#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#define FRAMERATE 60
#define SCENEPATH "Resources/Scenes/"
#define SCENEEXTENSION ".scene"
#define TEXTURETPATH "Resources/Textures/"
#define TEXTUREDESCRIPTIONEXTENSION ".description"
#define WINDOWRATIOX 1920
#define WINDOWRATIOY 1080


#include <map>
#include <string>
#include <dirent.h> // read directory
#include <iostream>
#include <fstream>
#include <sstream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

typedef std::vector< std::vector < sf::IntRect> > SpriteSheetDescription;

enum spriteSheetsDescriptions {
	linkSpritesDescriptions,
	spriteDescriptionsQtt
};

enum linkActions {
	moveUp			,
	moveDown		,
	moveSide		,
	attackUp		,
	attackDown		,
	attackSide		, 
	linkActionsQtt
};

bool isInt(std::string s);

int myStoi(std::string s);

#endif