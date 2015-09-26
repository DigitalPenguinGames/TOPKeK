#ifndef __OUTSIDESCENE_HPP__
#define __OUTSIDESCENE_HPP__

#include "Scene.hpp"
#include "utils.hpp"
#include "Map.hpp"

class OutsideScene : public Scene {
public:
	OutsideScene(Game* g, sf::RenderWindow* w, std::string description);
	~OutsideScene();

	void init();
	void processInput();
	void update(float deltaTime);
	void render();
private:
	Map map;
};





#endif