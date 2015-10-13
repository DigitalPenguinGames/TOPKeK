#ifndef __RESOURCES_HPP__
#define __RESOURCES_HPP__

#include "utils.hpp"

class Resources {
public:
    static void load();
    //static sf::Texture ...
    static sf::Shader  DtO;
    static sf::Shader sLighting;
    static sf::Shader cInvert;
    static sf::Texture tileSet;
    static sf::Texture tileSetCols;
    static sf::Texture dungeon;
    static sf::Texture dungeonCols;
    static sf::Texture linkSet;
    static sf::Texture linkSetT;
    static sf::Texture linkSetB;
    static sf::Texture linkSetL;
    static sf::Texture linkSetR;
    static sf::Texture linkSetTR;
    static sf::Texture linkSetTL;
    static sf::Texture linkSetBR;
    static sf::Texture linkSetBL;
    static sf::Texture overEnemies;
    static sf::Texture textureTest;
    static sf::Texture heart;
    static sf::Texture shinnyHeart;
    static sf::Texture halfHeart;
    static sf::Texture shinnyHalfHeart;
    static sf::Texture emptyHeart;
    static sf::Texture shinnyEmptyHeart;
    static sf::Font pauseMenuFont;
    static std::vector<SpriteSheetDescription> descriptions;
private:
    static SpriteSheetDescription loadDescription(std::string fileName);

};

#endif
