#ifndef __MAP_HPP__
#define __MAP_HPP__

#include "utils.hpp"
#include "Tile.hpp"
#include "SceneChanger.hpp"

class Map {
public:
	Map(std::string description);
	~Map();
	void init(sf::Vector2f sceneIniCoord);
	void draw(sf::RenderWindow* w);
	std::pair<bool,SceneChanger*> playerInsideExit(sf::Vector2f pos); // Change to Vector2f
private:
	std::vector<std::vector<int> > _premap;
	std::vector<std::vector<Tile> > _map;
	std::vector<SceneChanger> _sceneChangers;
};

#endif