#include "Scene.hpp"

Scene::Scene(sf::RenderWindow* w) : window(w) {

}

Scene::~Scene(){}

void Scene::init() {
	
}

void Scene::run() {
	int framerate = 60;
	sf::Clock clock;
	sf::Time timeSinceLastUpdate;
	sf::Time timePerFrame = sf::seconds(1.f/framerate);

	while (window->isOpen()) {
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
	while (window->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {window->close(); exit(0);}
	}
}

void Scene::update(float deltaTime) {
	(void)deltaTime;
}

void Scene::render() {
	window->clear();

	window->display();
}