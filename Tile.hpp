#ifndef __TILE_HPP__
#define __TILE_HPP__

#include "utils.hpp"
#include "Resources.hpp"

class Tile{ 
public:
	Tile();
	Tile(int n, sf::Vector2f pos);
	~Tile();
	void draw(sf::RenderWindow *w);
private:
	sf::Sprite sprite;
};

#endif