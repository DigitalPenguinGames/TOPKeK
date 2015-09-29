#ifndef __OUTSIDESCENE_HPP__
#define __OUTSIDESCENE_HPP__

#include "Scene.hpp"
#include "utils.hpp"
#include "Map.hpp"
#include "SceneChanger.hpp"

class OutsideScene : public Scene {
friend class Game;
public:
	OutsideScene(Game* g, sf::RenderWindow* w, sceneTypes sT, std::string description, std::string name);
	~OutsideScene();

	void init(sf::Vector2f sceneIniCoord);

	sf::Vector2f getSceneCoord();
	sf::Vector2i getMapSize();
private:
	void processInput();
	void update(float deltaTime);
	void render();
	Map _map;
	sf::Vector2f _sceneIniCoord;

};





#endif