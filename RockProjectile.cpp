#include "RockProjectile.hpp"

RockProjectile::RockProjectile(Map* map, sf::Vector2f pos, directions dir) : Weapon(map, pos, dir) {
    _sprite.setTexture(Resources::overEnemies);
    _description = Resources::descriptions[rockProjDescription];
    _sprite.setTextureRect(_description[0][0]);
    _bounds = RockProjectile::bounds();
    _damage = 0.5;
    _speed = sf::Vector2f(30,30);
    _angle = 0;
	_transform = sf::Transform::Identity;
}

RockProjectile::~RockProjectile() {}

void RockProjectile::update(float deltaTime) {
    Weapon::update(deltaTime);
    //_transform = _sprite.getTransform();
    _transform = sf::Transform::Identity;
    _angle += 90*deltaTime;
    _transform.rotate(_angle, 
        _sprite.getPosition().x +_bounds.left+_bounds.width/2,
        _sprite.getPosition().y +_bounds.top+_bounds.height/2);
}


void RockProjectile::draw(sf::RenderTarget* target) {
    target->draw(_sprite, _transform);    
}

void RockProjectile::hit() {
    _dead = true;
}

sf::IntRect RockProjectile::bounds() {
    return sf::IntRect(1,2,6,6);
}