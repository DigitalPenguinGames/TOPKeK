#include "OutsideScene.hpp"

OutsideScene::OutsideScene(Game* g, sf::RenderWindow* w, std::string description) :
	Scene(g,w),
	_map(description)
{

}

OutsideScene::~OutsideScene() {

}

void OutsideScene::init() {
	initView();
	_map.init();
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
}

void OutsideScene::update(float deltaTime) {

}

void OutsideScene::render() {
	_map.draw(_window);
}