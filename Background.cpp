#include "Background.hpp"

Background::Background(sf::Vector2f pos) {
    sprite.setTexture(Resources::dungeon);
    sprite.setPosition(pos);
}

Background::~Background(){}

void Background::draw(sf::RenderTarget* w) {
    w->draw(sprite);
}