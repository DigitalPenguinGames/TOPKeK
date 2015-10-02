#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#define FRAMERATE 60

#define SCENEPATH "Resources/Scenes/"
#define SCENEEXTENSION ".scene"
#define SCENEEXTENSIONSIZE 6
#define TEXTURETPATH "Resources/Textures/"
#define TEXTUREDESCRIPTIONEXTENSION ".description"

#define TILESIZE 16
#define TILEOFFSET 1
#define TILESETWIDTH 18
#define TILESETHEIGH 8

#define WINDOWRATIOX 256
#define WINDOWRATIOY 176


#include <map>
#include <string>
#include <dirent.h> // read directory
#include <iostream>
#include <fstream>
#include <sstream>
#include <cfloat>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

// Scene Status
namespace status{
    enum gameStatus {running, onMenu};
}

//Scenes
enum sceneTypes {
	outside = 0,
	inside = 1
};

// SpriteSheets
typedef std::vector< std::vector < sf::IntRect> > SpriteSheetDescription;

enum spriteSheetsDescriptions {
	linkSpritesDescriptions,
	swordDescriptions,
	spriteDescriptionsQtt
};

// Animations
enum linkActions {
	moveUp			,
	moveDown		,
	moveSide		,
	attackUp		,
	attackDown		,
	attackSide		, 
	linkActionsQtt
};

// Sword Types
enum swordtypes {
	first,
	second,
	third,
	fourth,
	qttSwordTypes
};

// Directions
enum directions {
	up				,
	down			,
	left 			,
	right
};

bool isInt(std::string s);

int myStoi(std::string s);

#endif