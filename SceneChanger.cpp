#include "SceneChanger.hpp"

SceneChanger::SceneChanger() {}

SceneChanger::SceneChanger(sf::Vector2f pos, std::string nextScene, sf::Vector2f nextScenePos) :
    _pos(pos),
    _nextScene(nextScene),
    _nextScenePos(nextScenePos) {}

SceneChanger::~SceneChanger() {}

std::string SceneChanger::getNextSceneName() {
    return _nextScene;
}


sf::FloatRect SceneChanger::getRect(sf::Vector2f offset) {
    directions dir = getChangeDirection();
    sf::Vector2f localOffset(TILESIZE-4,TILESIZE-4);
    switch (dir) {
        case directions::left:
            localOffset.x *= -1;
            localOffset.y = 0;
            break;
        case directions::right:
            localOffset.y = 0;
            break;
        case directions::up:
            localOffset.x = 0;
            localOffset.y *= -1;
            break;
        case directions::down:
            localOffset.x = 0;
            break;
        default:
            localOffset.x = localOffset.y = 0;
            break;
    }
    return sf::FloatRect(_pos.x*TILESIZE+offset.x+localOffset.x,_pos.y*TILESIZE+offset.y+localOffset.y,TILESIZE,TILESIZE);
}

directions SceneChanger::getChangeDirection() {
    if (_pos.x == 0) return directions::left;
    else if (_pos.y == 0) return directions::up;
    else if (_nextScenePos.x==0) return directions::right;
    else if (_nextScenePos.y==0) return directions::down;
    else return directions::directionsQtty;
}
