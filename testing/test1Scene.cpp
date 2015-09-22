#include "test1Scene.hpp"

test1Scene::test1Scene(Game* g, sf::RenderWindow* w) : Scene(w), game(g) {
	rectangle = sf::RectangleShape(sf::Vector2f(int(w->getSize().x)),int(w->getSize().y)));
	rectangle.setPosition(0,0);
	rectangle.setColor(sf::Color::Yellow);
}

void test1Scene::processInput() {
	sf::Event event;
	while (_window->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {_window->close(); exit(0);}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
			game->changeScene("test2Scene");
		}
	}
}

void test1Scene::update(float deltaTime) {
	(void)deltaTime;
}

void test1Scene::render() {
	_window->clear();
	_window->draw(rectangle);
	_window->display();
}