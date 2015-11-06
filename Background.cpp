#include "Background.hpp"

Background::Background(sf::Vector2f pos) {
    _sprite.setTexture(Resources::dungeon);
    _sprite.setPosition(pos);
    _decoration.setPosition(pos);
    int aux = rand()%5;
    if (aux < 2) {
        _dec = true;
        switch (aux) {
        case 0:
            _decoration.setTexture(Resources::dungeonDecoration0);
            break;
        case 1:
            _decoration.setTexture(Resources::dungeonDecoration1);
            break;
        default:
            break;
        }
    }
}

Background::~Background(){}

void Background::draw(sf::RenderTarget* w) {
    w->draw(_sprite);
    if (_dec) w->draw(_decoration);
}
