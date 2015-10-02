#include "ScenePlayable.hpp"
#include "Game.hpp"

ScenePlayable::ScenePlayable(Game* g, sf::RenderWindow* w, sceneTypes sT, std::string name, std::string description) :
	Scene(g,w,sT,name),
	_map(description) {	
    _status = status::running;
}

ScenePlayable::~ScenePlayable(){}

sf::Vector2f ScenePlayable::getSceneCoord() {
	return _map.getPtrTile(sf::Vector2i(0,0))->getPosition();
}

sf::Vector2i ScenePlayable::getMapSize() {
	return _map.getSize();
}

void ScenePlayable::display() {
	_window->clear();
    switch(_status){
        case status::onMenu:
        	// set the PauseMenú view
        	// render pause menú
        	//break;
        case status::running:
            _window->setView(_view);
            render();
            _window->setView(_window->getDefaultView());
            break;


        default:
            break;
    }
    _window->display();
}