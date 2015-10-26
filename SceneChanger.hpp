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
    directions getOutsideDirection();

    void setBounds(sf::FloatRect rect);
    void setDirection(directions dir);

    sf::Vector2f _pos;
    std::string _nextScene;
    sf::Vector2f _nextScenePos;
    sf::FloatRect _bound;
    directions _dir;


};


#endif