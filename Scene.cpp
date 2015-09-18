#include "Scene.hpp"

Scene::Scene(sf::RenderWindow* w) : _window(w) {

}

Scene::~Scene(){}

void Scene::init() {

}

void Scene::run() {
	sf::Clock clock;
	sf::Time timeSinceLastUpdate;
	sf::Time timePerFrame = sf::seconds(1.f/FRAMERATE);

	while (_window->isOpen()) {
		processInput();
		timeSinceLastUpdate = clock.restart();
		while (timeSinceLastUpdate > timePerFrame) {
			timeSinceLastUpdate -= timePerFrame;
			update(timePerFrame.asSeconds());
		}
		update(timePerFrame.asSeconds());
		render();
	}
}

void Scene::processInput() {
	sf::Event event;
	while (_window->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {_window->close(); exit(0);}
	}
}

void Scene::update(float deltaTime) {
	(void)deltaTime;
}

void Scene::render() {
	_window->clear();

	_window->display();
}