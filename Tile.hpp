#ifndef __TILE_HPP__
#define __TILE_HPP__

#include "utils.hpp"
#include "Resources.hpp"

class Tile{ 
public:
    Tile();
    Tile(int n, sf::Vector2f pos, sf::Vector2f offset);
    ~Tile();
    void draw(sf::RenderTarget* w);
    void drawCollision(sf::RenderTarget* target);
    sf::Vector2f getPosition();
private:
    sf::Sprite _sprite;
    sf::Sprite _collision;
};

#endif