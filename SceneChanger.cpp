#include "SceneChanger.hpp"

SceneChanger::SceneChanger() {}

SceneChanger::SceneChanger(sf::Vector2f pos, std::string nextScene, sf::Vector2f nextScenePos) :
	_pos(pos),
	_nextScene(nextScene),
	_nextScenePos(nextScenePos) {

}

SceneChanger::~SceneChanger() {}

std::string SceneChanger::getNextSceneName() {
	return _nextScene;
}

sf::FloatRect SceneChanger::getRect(sf::Vector2f offset) {
	return sf::FloatRect(_pos.x*16+offset.x,_pos.y*16+offset.y,16,16);
}

directions SceneChanger::getChangeDirection() {
	if (_pos.x == 0) return directions::left;
	else if (_pos.y == 0) return directions::up;
	else if (_nextScenePos.x==0) return directions::right;
	else return directions::down;
}