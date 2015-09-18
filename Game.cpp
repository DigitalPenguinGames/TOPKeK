#include "Game.hpp"

Game::Game() : _window(sf::VideoMode::getDesktopMode(),"TOPKeK", sf::Style::Close) {
	_window.setFramerateLimit(FRAMERATE);
	Resources::load();
}

void Game::start() {
	loadScenes();	

	exit(0);
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

void Game::loadScene(std::string path) {
	std::cout << path << std::endl;
}