#ifndef __GAME_HPP__
#define __GAME_HPP__

#include "Resources.hpp"
#include "Scene.hpp"
#include "utils.hpp"
#include "testing/test1Scene.hpp"

class Game {
public:
	Game();
	~Game();

	void start();

	void changeScene(std::string sceneName);

private:
	sf::RenderWindow _window;
	std::map<std::string, Scene*> _scenes;
	Scene* _currentScene;
	Scene* _lastScene;

	void loadScenes();
	void loadScene(std::string sceneName);
};

#endif