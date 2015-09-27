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

sf::FloatRect SceneChanger::getRect() {
	return sf::FloatRect(_pos.x*16,_pos.y*16,16,16);
}