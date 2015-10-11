#include "Tile.hpp"

Tile::Tile(){}

Tile::Tile(int n, sf::Vector2f pos, sf::Vector2f offset) {
    _sprite.setTexture(Resources::tileSet);
    _collision.setTexture(Resources::tileSetCols);

    int x = (n % TILESETWIDTH)*(TILESIZE + TILEOFFSET) + 1;
    int y = (int(n / TILESETWIDTH))*(TILESIZE + TILEOFFSET) + 1;
    //std::cout << n << " " << x << " " << y << std::endl;
    _sprite.setTextureRect(sf::IntRect(x,y,TILESIZE,TILESIZE));
    _sprite.setPosition(pos.x + offset.x,pos.y + offset.y);

    _collision.setTextureRect(sf::IntRect(x,y,TILESIZE,TILESIZE));
    _collision.setPosition(pos.x,pos.y);
}

Tile::~Tile() {}

void Tile::draw(sf::RenderTarget* w) {
    w->draw(_sprite);
}


void Tile::drawCollision(sf::RenderTarget* target) {
    target->draw(_collision);
}

sf::Vector2f Tile::getPosition() {
    return _sprite.getPosition();
}