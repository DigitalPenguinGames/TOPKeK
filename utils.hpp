#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#define FRAMERATE 60

#define SCENEPATH "Resources/Scenes/"
#define SCENEEXTENSION ".scene"
#define SCENEEXTENSIONSIZE 6
#define TEXTURETPATH "Resources/Textures/"
#define TEXTUREDESCRIPTIONEXTENSION ".description"
#define SHADERPATH "Resources/Shaders/"
#define DATAPATH "Resources/Data/"

#define TILESIZE 16
#define TILEOFFSET 1
#define TILESETWIDTH 18
#define TILESETHEIGH 8

#define WINDOWRATIOX 256
#define WINDOWRATIOY 176

#define DUNGEONSIZEX 256
#define DUNGEONSIZEY 176


#include <map>
#include <list>
#include <string>
#include <dirent.h> // read directory
#include <iostream>
#include <fstream>
#include <sstream>
#include <cfloat>
#include <queue> // priority queue
#include <functional> // priority queue stuff

#include "DataManager.hpp"
#include "SoundManager.hpp"

#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

//movement dir { down, left, right, up , none };
const int mx[5] = {0,  -1,     1,       0,   0   };
const int my[5] = {1,    0,     0,   -1,   0   };

const float TO_RADIANS = (1 / 180.0f) * (float ) M_PI;
const float TO_DEGREES = (1 / (float ) M_PI) * 180;
// Scene Status
namespace status{
    enum gameStatus {running, onMenu};
}

//Scenes
enum sceneTypes {
    outside = 0,
    dungeon = 1,
    lightedDungeon = 2,
};

// SpriteSheets
typedef std::vector< std::vector < sf::IntRect> > SpriteSheetDescription;

enum spriteSheetsDescriptions {
    linkSpritesDescriptions,
    swordDescriptions,
    octorokDescriptions,
    rockProjDescription,
    propsOverDescription,
    dungeonDoorsHor,
    dungeonDoorsVer,
    spriteDescriptionsQtt
};

// Animations
enum linkActions {
    move            ,
    attack          ,
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

// Props Types
enum propTypes {
    treeGreen   ,
    treeBrown   ,
    treeWhite   ,
    statueGreen ,
    statueBrown ,
    statueWhite ,
    bushGreen   ,
    bushBrown   ,
    grave       ,
    soldierGreen,
    soldierBrown,
    soldierWhite,
    propsQtty
};

enum dungeonHorDoorTypes {
    openTop,
    openBot,
    closTop,
    closBot,
    keysTop,
    keysBot,
    dungeonHorDoorQtty
};

enum dungeonVerDoorTypes {
    openRight,
    openLeft ,
    closRight,
    closLeft,
    keysRight,
    keysLeft,
    dungeonVerDoorQtty
};

// Directions
enum directions {
    down    , // This have
    left    , // to be
    up      , // in this
    right   , // order
    none    ,
    topRight,
    topLeft ,
    botRight,
    botLeft ,

    directionsQtty
};

bool isInt(std::string s);

int myStoi(std::string s);

bool myStob(std::string s);

float radToAngle(float rad);

float difference(float a, float b);

float floatangleToRad(float angle);

float getAngle(const sf::Vector2f &orig,const sf::Vector2f &des);

float getModule(const sf::Vector2f &orig, const sf::Vector2f &des);

bool isCollisioning(sf::Vector2f point1, float radius1, sf::Vector2f point2, float radius2);

directions pointsToDirection(sf::Vector2f pos1, sf::Vector2f pos2, float rotation);

sf::Vector2f getRelativeCenter(sf::Vector2f origen, sf::IntRect boundOr, sf::IntRect boundDest);

bool counterDirection(directions d1, directions d2);

int getHorizontal(directions dir);

int getVertical(directions dir);

#endif
