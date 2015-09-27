#include "OutsideScene.hpp"
#include "Game.hpp"

OutsideScene::OutsideScene(Game* g, sf::RenderWindow* w, sceneTypes sT, std::string description) :
	Scene(g,w,sT),
	_map(description)
{

}

OutsideScene::~OutsideScene() {

}

void OutsideScene::init(sf::Vector2f sceneIniCoord = sf::Vector2f(0,0)) {
	_map.init(sceneIniCoord);
	initView();
}

void OutsideScene::processInput() {
	sf::Event event;
	while (_window->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {_window->close(); exit(0);}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
			_window->close(); exit(0);
		}

		//else if (event.type == sf::Event::Resized) initView();
	}
	sf::Vector2f mousePos = _window->mapPixelToCoords(sf::Mouse::getPosition(*_window),_view);
	//std::cout << "mouse position " << mousePos.x << " " << mousePos.y << std::endl;
	std::pair<bool,SceneChanger*> aux = _map.playerInsideExit(mousePos);
	if (aux.first) {
		_game->changeScene(aux.second->getNextSceneName(),aux.second);
	}
}

void OutsideScene::update(float deltaTime) {

}

void OutsideScene::render() {
	_map.draw(_window);
}

sf::Vector2f OutsideScene::getSceneCoord() {
	return _map.getPtrTile(sf::Vector2i(0,0))->getPosition();
}

sf::Vector2i OutsideScene::getMapSize() {
	return _map.getSize();
}