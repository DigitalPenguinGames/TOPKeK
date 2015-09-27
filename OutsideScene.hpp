#ifndef __OUTSIDESCENE_HPP__
#define __OUTSIDESCENE_HPP__

#include "Scene.hpp"
#include "utils.hpp"
#include "Map.hpp"
#include "SceneChanger.hpp"

class OutsideScene : public Scene {
public:
	OutsideScene(Game* g, sf::RenderWindow* w, sceneTypes sT, std::string description);
	~OutsideScene();

	void init(sf::Vector2f sceneIniCoord);
	void processInput();
	void update(float deltaTime);
	void render();
private:
	Map _map;
};





#endif