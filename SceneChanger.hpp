#ifndef __SCENECHANGER_HPP__
#define __SCENECHANGER_HPP__

#include "utils.hpp"

class SceneChanger {
public:
    SceneChanger();
    SceneChanger(sf::Vector2f pos, std::string nextScene, sf::Vector2f nextScenePos);
    ~SceneChanger();

    std::string getNextSceneName();
    sf::FloatRect getRect(sf::Vector2f offset);
    directions getChangeDirection();

    sf::Vector2f _pos;
    std::string _nextScene;
    sf::Vector2f _nextScenePos;


};


#endif