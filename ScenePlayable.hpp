#ifndef __SCENEPLAYABLE_HPP__
#define __SCENEPLAYABLE_HPP__

#include "Scene.hpp"
#include "utils.hpp"
#include "Map.hpp"

class Game;
class ScenePlayable : public Scene {
public:
	ScenePlayable(Game *g, sf::RenderWindow* w, sceneTypes sT, std::string name, std::string description);
	~ScenePlayable();

	void init(sf::Vector2f sceneIniCoord) = 0;

	sf::Vector2f getSceneCoord();
	sf::Vector2i getMapSize();
protected:
	Map _map;
	sf::Vector2f _sceneIniCoord;
    status::gameStatus _status;

private:
	void display();

};



#endif