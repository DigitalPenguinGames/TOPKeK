#include "RockProjectile.hpp"
#include "Player.hpp"

RockProjectile::RockProjectile(Map* map, sf::Vector2f pos, directions dir) : Weapon(map, pos, dir) {
    _sprite.setTexture(Resources::overEnemies);
    _description = Resources::descriptions[rockProjDescription];
    _sprite.setTextureRect(_description[0][0]);
    _bounds = RockProjectile::bounds();
    _damage = 0.5;
    _speed = sf::Vector2f(40,40);
    _angle = 0;
	_transform = sf::Transform::Identity;
    _timerToDead = -1;
     _collisionMask = collisionMapMask::water | collisionMapMask::ground | collisionMapMask::passage;
}

RockProjectile::~RockProjectile() {}

void RockProjectile::update(float deltaTime) {
    Weapon::update(deltaTime);

    _transform = sf::Transform::Identity;
    _angle += 90*deltaTime;
    sf::IntRect bounds = RockProjectile::bounds();
    _transform.rotate(_angle, 
        _sprite.getPosition().x +bounds.left+bounds.width/2,
        _sprite.getPosition().y +bounds.top+bounds.height/2);

    if (_timerToDead > 0 && _timerToDead < deltaTime) _dead = true;
    _timerToDead -= deltaTime;
}


void RockProjectile::draw(sf::RenderTarget* target) {
    target->draw(_sprite, _transform);    
}

void RockProjectile::hit() {
    _dead = true;
}

void RockProjectile::intersectsWith(Collisionable* c) {
    Player* player = dynamic_cast<Player*>(c);
    if (player != nullptr) {
        if (!counterDirection(getDirection(),player->getDirection()) || player->isAttacking()) hit();
        else {
            _speed = getRandBounce(_speed.x,_dir);
            _dir = directions::none;
            _timerToDead = 0.5;
            _bounds = sf::IntRect(0,0,0,0);
        }
        return;
    }
    Weapon::intersectsWith(c);
}

sf::IntRect RockProjectile::bounds() {
    return sf::IntRect(1,2,6,6);
}
