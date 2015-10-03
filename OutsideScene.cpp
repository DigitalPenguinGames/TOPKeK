#include "OutsideScene.hpp"
#include "Game.hpp"

OutsideScene::OutsideScene(Game* g, sf::RenderWindow* w, sceneTypes sT, std::string name, std::string description) :
	ScenePlayable(g,w,sT,name,description)
{
	_sceneIniCoord = sf::Vector2f(FLT_MAX,FLT_MAX);
}

OutsideScene::~OutsideScene() {

}

void OutsideScene::init(sf::Vector2f sceneIniCoord = sf::Vector2f(0,0)) {
	if (sceneIniCoord == _sceneIniCoord) return;
	_sceneIniCoord = sceneIniCoord;
	_map.init(_sceneIniCoord);
	initView();
}

void OutsideScene::processInput() {
	sf::Event event;
	while (_window->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {_window->close(); exit(0);}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
			_window->close(); exit(0);
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) {
            if(_status == status::running) _status = status::onMenu;
            else _status = status::running;
        }
		//else if (event.type == sf::Event::Resized) initView();
	}
	sf::Vector2f mousePos = _window->mapPixelToCoords(sf::Mouse::getPosition(*_window),_view);
	//std::cout << "mouse position " << mousePos.x << " " << mousePos.y << std::endl;
	std::pair<bool,SceneChanger*> aux = _map.playerInsideExit(mousePos);
	if (aux.first) {
		changeScene(aux.second);
	}
}

void OutsideScene::update(float deltaTime) {
	(void)deltaTime;
}

void OutsideScene::render() {
	_map.draw(_window);
}