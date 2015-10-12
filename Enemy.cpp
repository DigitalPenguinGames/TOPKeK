#include "Enemy.hpp"

Enemy::Enemy(Map* map, sf::Vector2f pos) : _map(map) {
    _speed = sf::Vector2f(0,0);
    _elapsedWalking = 0;
    _elapsedAnimation = 0;
    _currentAnimation = 0;

    _moving = false;
    _attacking = false;

    _sprite.setPosition(pos);
}

Enemy::~Enemy() {}


void Enemy::update(float deltaTime) {
    if(_moving) {
        _elapsedAnimation -= deltaTime;
        if (_elapsedAnimation < 0) {
            _elapsedAnimation += _elapsedWalking;
            _currentAnimation = (_currentAnimation+1)%_description[_action*4+_dir].size();
        }
    }
    _sprite.setTextureRect(_description[_action*4+_dir][_currentAnimation%_description[_action*4+_dir].size()]);

    if (_attacking) {
        _elapsedAttack -= deltaTime;
        if (_elapsedAttack <= 0) {
            _action = linkActions::move;
            _attacking = false;
        }
    }
    else if (_moving) {
        sf::Vector2f movement, initial;
        initial = _sprite.getPosition();
        movement.x = (_dir == directions::left ? -_speed.x : (_dir == directions::right ? _speed.x : 0));
        movement.y = (_dir == directions::up ? -_speed.y : (_dir == directions::down ? _speed.y : 0));
        _sprite.move(_map->getMaxMovement(initial,movement*deltaTime,_walkBounds));
        _moving = false;
    }
}

void Enemy::draw(sf::RenderTarget* window) {
    window->draw(_sprite);
}

void Enemy::setMap(Map* map) {
    _map = map;
}