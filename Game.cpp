#include "Game.hpp"

Game::Game() : _window(sf::VideoMode::getDesktopMode(),"TOPKeK", sf::Style::Close | sf::Style::Resize) {
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
	changeScene("ini",nullptr);

	while (_currentScene != nullptr) {
		_currentScene->run();
	}

	exit(0);
}


void Game::changeScene(std::string sceneName,SceneChanger* sC = nullptr) { // This will be called by any scene when something trigers to change to anothe scene
	sf::Vector2f sceneIniCoord(0,0);
	if (_currentScene != nullptr) {
		_lastScene = _currentScene;
		_currentScene->killScene();
	}
	auto it = _scenes.find(sceneName);
	if (it == _scenes.end()) {
		std::cout << "The selected scene does not exist: " << sceneName << std::endl;
		exit(EXIT_FAILURE);
	}
	Scene* aux = (*it).second;
	
	std::cout << "Changing to scene " << sceneName << std::endl;

	// Animations
	if (_lastScene != nullptr && _lastScene->getType() == _currentScene->getType()) {
		if (_currentScene->getType() == sceneTypes::outside) {
			OutsideScene* lastScene = dynamic_cast<OutsideScene*>(_lastScene);
			OutsideScene* currentScene = dynamic_cast<OutsideScene*>(_currentScene);
		}
		// 
	}
	_currentScene = aux;	
	_currentScene->init(sceneIniCoord);
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
	std::cout << sceneName.substr(0,sceneName.length()-sizeof(SCENEEXTENSION)+1) << std::endl;

	std::ifstream t(SCENEPATH + sceneName);
	std::string str((std::istreambuf_iterator<char>(t)),
                 std::istreambuf_iterator<char>());

	std::istringstream description(str);

	std::string sceneType;
	description >> sceneType;
	Scene* aux;
	switch(myStoi(sceneType)) {
		case sceneTypes::outside:
			aux = new OutsideScene(this,&_window,sceneTypes::outside, str);
	}
	
	_scenes.insert(std::make_pair(sceneName.substr(0,sceneName.length()-sizeof(SCENEEXTENSION)+1),aux));
}