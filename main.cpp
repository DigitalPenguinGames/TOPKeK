#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Scene.hpp"

int main() {
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(),"TOPKeK", sf::Style::Close);

	Scene scene(&window);
	scene.run();

	// while (window.isOpen()) {
	// 	sf::Event event;
		
	// 	while (window.pollEvent(event)) {
	// 		if (event.type == sf::Event::Closed) {window.close(); return 0;}
	// 	}

	// 	window.clear();

	// 	window.display();
	// }
	return 0;
}