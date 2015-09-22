#include "Game.hpp"

Game::Game() : _window(sf::VideoMode::getDesktopMode(),"TOPKeK", sf::Style::Close) {
	_window.setFramerateLimit(FRAMERATE);
	Resources::load();
	_currentScene = nullptr;
	_lastScene = nullptr;
}

Game::~Game() {
	for (auto it = _scenes.begin(); it != _scenes.end(); ++it) {
		delete it->second;
	}
}

void Game::start() {
	loadScenes();
	changeScene("test1.scene");

	while (_currentScene != nullptr) {
		_currentScene->run();
	}


	exit(0);
}


void Game::changeScene(std::string sceneName) { // This will be called by any scene when something trigers to change to anothe scene
	if (_currentScene != nullptr) {
		_lastScene = _currentScene;
		_currentScene->killScene();
	}
	Scene* aux = _scenes.find(sceneName)->second;
	if (aux == nullptr) {
		perror("The selected scene does not exist");
		exit(EXIT_FAILURE);
	}
	_currentScene = aux;

	
	_currentScene->init();
}


void Game::loadScenes() {
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir (SCENEPATH)) != NULL) {
	  while ((ent = readdir(dir)) != NULL) {
	  	std::string aux = ent->d_name;
	  	if (aux.find(SCENEEXTENSION) != std::string::npos) {
	    	loadScene(aux);
		}
	  }
	  closedir (dir);
	} else {
	  perror ("Could not open directory");
	  exit(EXIT_FAILURE);
	}
}

void Game::loadScene(std::string sceneName) {
	std::cout << sceneName << std::endl;
	Scene* aux = new Scene(&_window);
	_scenes.insert(std::make_pair(sceneName,aux));
}