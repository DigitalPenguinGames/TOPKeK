#ifndef __DUNGEONSCENE_HPP__
#define __DUNGEONSCENE_HPP__

#include "ScenePlayable.hpp"

class DungeonScene : public ScenePlayable {
friend class Game;
public:
	DungeonScene(Game* g, sf::RenderWindow* w, sceneTypes sT, std::string name, std::string description);
	~DungeonScene();

	void init(sf::Vector2f sceneIniCoord);

private:
	void processInput();
	void update(float deltaTime);
	void render();

};




#endif