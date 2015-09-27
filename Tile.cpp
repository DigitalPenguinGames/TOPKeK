#include "Tile.hpp"

Tile::Tile(){}

Tile::Tile(int n,sf::Vector2f pos) {
	sprite.setTexture(Resources::tileSet);
	int x = (n % TILESETWIDTH)*(TILESIZE + TILEOFFSET) + 1;
	int y = (int(n / TILESETWIDTH))*(TILESIZE + TILEOFFSET) + 1;
	//std::cout << n << " " << x << " " << y << std::endl;
	sprite.setTextureRect(sf::IntRect(x,y,TILESIZE,TILESIZE));
	sprite.setPosition(pos.x,pos.y);
}

Tile::~Tile() {}

void Tile::draw(sf::RenderWindow* w) {
	w->draw(sprite);
}