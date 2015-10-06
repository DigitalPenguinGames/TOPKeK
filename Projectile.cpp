#include "Projectile.hpp"

Projectile::Projectile() {
    deltaToDespawn = timeToDespawn;
    _sprite.setTexture(Resources::linkSet);
    _sprite.setTextureRect(Resources::descriptions[swordDescriptions][swordtypes::first][0]);
}

Projectile::~Projectile() {}

void Projectile::init(directions dir, sf::Vector2f pos) {
    _sprite.setPosition(pos);
    switch(dir){
        case directions::down:
            _sprite.setRotation(0);
            break;
        case directions::up:
            _sprite.setRotation(180);
            break;
        case directions::right:
            _sprite.setRotation(270);
            break;
        case directions::left:
            _sprite.setRotation(90);
            break;
        default:
            break;
    }
}

void Projectile::update(float deltaTime) {
    _sprite.move(_speed*deltaTime);
    deltaToDespawn -= timeToDespawn;
}

void Projectile::draw(sf::RenderTarget* w) {
    w->draw(_sprite);
}
