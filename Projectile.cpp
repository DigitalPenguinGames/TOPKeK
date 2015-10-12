#include "Projectile.hpp"

Projectile::Projectile() {
    deltaToDespawn = timeToDespawn;
    _sprite.setTexture(Resources::linkSet);
    _sprite.setTextureRect(Resources::descriptions[swordDescriptions][swordtypes::first][0]);

    std::vector<sf::Texture*> textures(9);
    textures[directions::none]  = &Resources::linkSet;
    textures[directions::up]    = &Resources::linkSetT;
    textures[directions::left]  = &Resources::linkSetL;
    textures[directions::down]  = &Resources::linkSetB;
    textures[directions::right] = &Resources::linkSetR;
    textures[directions::topLeft]  = &Resources::linkSetTL;
    textures[directions::botLeft]  = &Resources::linkSetBL;
    textures[directions::topRight] = &Resources::linkSetTR;
    textures[directions::botRight] = &Resources::linkSetBR;

    _lightSprite = LightSprite(Resources::descriptions[swordDescriptions], textures);

    _bounds = sf::IntRect(0,0,7,16);
}

Projectile::~Projectile() {}

void Projectile::init(directions dir, sf::Vector2f pos) {
    _lightSprite.update(pos,0,0,0);
    _sprite.setPosition(pos);
    switch(dir){
        case directions::down:
            _lightSprite.setRotation(0);
            break;
        case directions::up:
            _lightSprite.setRotation(180);
            break;
        case directions::right:
            _lightSprite.setRotation(270);
            break;
        case directions::left:
            _lightSprite.setRotation(90);
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
    _lightSprite.draw(w);
}

void Projectile::setPosition(sf::Vector2f pos) {
    _sprite.setPosition(pos);
    _lightSprite.setPosition(pos);
}

void Projectile::setLight(Light* light) {
    _lightSprite.setLight(light);
}