#include "Enemy.hpp"
#include "Prop.hpp"
#include "Weapon.hpp"
#include "Object.hpp"
#include "ScenePlayable.hpp"

Enemy::Enemy(ScenePlayable* scene, Map* map, sf::Vector2f pos) : _scene(scene), _map(map) {
    _speed = sf::Vector2f(0,0);
    _hp = 5;
    _dead = false;
    _damage = 0;

    _elapsedWalking = 0;
    _elapsedAnimation = 0;
    _currentAnimation = 0;
    _hitedTimer = 0;

    _moving = false;
    _attacking = false;

    _sprite.setPosition(pos);
}

Enemy::~Enemy() {}


void Enemy::update(float deltaTime) {
    _hitedTimer -= deltaTime;
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
        cmove(_map->getMaxMovement(initial,movement*deltaTime,_walkBounds));
        _moving = false;
    }
}

void Enemy::draw(sf::RenderTarget* window) {
    if (_hitedTimer > 0) {
        Resources::cInvert.setParameter("deltaTime", _hitedTimer);
        window->draw(_sprite,&Resources::cInvert);
    }
    else window->draw(_sprite);
}

void Enemy::setMap(Map* map) {
    _map = map;
}

void Enemy::getHit(float much, sf::Vector2f) {
    if (_hitedTimer > 0) return;
    Resources::cInvert.setParameter("Time", 1.5);
    _hitedTimer = 1.5; // One second of invulneravility;
    _hp -= much;
    _dead = _hp <= 0;
    std::cout << "it hurts " << _hp << std::endl;
    
    if (_dead) drop();
}

void Enemy::drop() {
    _scene->addObject(new Object(objectType(std::rand()%int(objectType::objectsQtty)), 
        sf::Vector2f(_sprite.getPosition().x+_bounds.left+_bounds.width/2, 
                     _sprite.getPosition().y+_bounds.top+_bounds.height/2), _scene));
}

bool Enemy::isAlive() {
    return !_dead;
}

float Enemy::getDamage() {
    return _damage;
}

sf::IntRect Enemy::getWalkBounds() {
    return _walkBounds;
}


sf::IntRect Enemy::getGlobalWalkBounds() {
    return sf::IntRect(_walkBounds.left+_sprite.getPosition().x, _walkBounds.top + _sprite.getPosition().y, _walkBounds.width, _walkBounds.height);
}

void Enemy::intersectsWith(Collisionable* c) {
    Weapon* weapon = dynamic_cast<Weapon*>(c);
    if (weapon != nullptr) {
        getHit(weapon->getDamage(),sf::Vector2f(0,0));
        return;
    }
    Prop* prop = dynamic_cast<Prop*>(c);
    if (prop != nullptr) {
        resetMove();
        return;
    }
}