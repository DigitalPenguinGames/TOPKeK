#ifndef __GAME_HPP__
#define __GAME_HPP__

#include "Resources.hpp"
#include "Scene.hpp"

class Game {
public:
	Game();

	void start();
private:
	sf::RenderWindow _window;
	std::map<int, Scene*> _scenes;

	void loadScenes();
	void loadScene(std::string path);
};

#endif