#ifndef __MAP_HPP__
#define __MAP_HPP__

#include "utils.hpp"
#include "Tile.hpp"

class Map {
public:
	Map(std::string description);
	~Map();
	void init();
	void draw(sf::RenderWindow* w);
private:
	std::vector<std::vector<int> > _premap;
	std::vector<std::vector<Tile> > _map;
};

#endif