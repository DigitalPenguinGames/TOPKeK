#ifndef __RESOURCES_HPP__
#define __RESOURCES_HPP__

#include "utils.hpp"

class Resources {
public:
    static void load();
    //static sf::Texture ...
    static sf::Shader DtO;
    static sf::Shader sDying;
    static sf::Shader cInvert;
    static sf::Shader sLighting;
    static sf::Shader fairyShootShader;


    static sf::Texture key;
    static sf::Texture heart;
    static sf::Texture rupia;
    static sf::Texture digPen;
    static sf::Texture portada;
    static sf::Texture credits;
    static sf::Texture dungeon;
    static sf::Texture talkBox;
    static sf::Texture tileSet;
    static sf::Texture linkSet;
    static sf::Texture linkSetT;
    static sf::Texture linkSetB;
    static sf::Texture linkSetL;
    static sf::Texture linkSetR;
    static sf::Texture linkSetTR;
    static sf::Texture linkSetTL;
    static sf::Texture linkSetBR;
    static sf::Texture linkSetBL;
    static sf::Texture halfHeart;
    static sf::Texture propsOver;
    static sf::Texture fairyShoot;
    static sf::Texture emptyHeart;
    static sf::Texture linkTalkBox;
    static sf::Texture dungeonCols;
    static sf::Texture textureTest;
    static sf::Texture shinnyHeart;
    static sf::Texture overEnemies;
    static sf::Texture tileSetCols;
    static sf::Texture penguinEnemy;
    static sf::Texture bulletPenguin;
    static sf::Texture penguinEnemyAttack;
    static sf::Texture shinnyHalfHeart;
    static sf::Texture shinnyEmptyHeart;
    static sf::Texture dungeonDecoration0;
    static sf::Texture dungeonDecoration1;
    static sf::Texture dungeonForeground0;
    static sf::Texture dungeonForeground1;
    static sf::Texture dungeonDoorsVertical;
    static sf::Texture dungeonDoorsHorizontal;

    static sf::Texture initialAnimation1;
    static sf::Texture initialAnimation2;
    static sf::Texture initialAnimation3;
    static sf::Texture initialAnimation4;
    static sf::Texture initialAnimation5;

    static sf::Texture gameOver;

    static sf::Font pauseMenuFont;

    static std::vector<std::string> AnimationTexts;
    static std::vector<sf::Texture> AnimationIntro;
    static std::vector<float> AnimationIntroTimers;
    static std::vector<animationActions> AnimationIntroActions;

    static std::vector<std::string> AnimationDeathTexts;
    static std::vector<sf::Texture> AnimationDeath;
    static std::vector<float> AnimationDeathTimers;
    static std::vector<animationActions> AnimationDeathActions;

    static std::vector<std::string> AnimationTextsInit;
    static std::vector<sf::Texture> AnimationInit;
    static std::vector<float> AnimationTimersInit;
    static std::vector<animationActions> AnimationActionsInit;

    static std::vector<SpriteSheetDescription> descriptions;
private:
    static SpriteSheetDescription loadDescription(std::string fileName);

};

#endif
