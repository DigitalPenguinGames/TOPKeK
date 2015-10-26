#include "Weapon.hpp"
#include "Prop.hpp"
#include "Player.hpp"

Weapon::Weapon(Map* map, sf::Vector2f pos, directions dir) : 
    Collisionable(pos),
    _map(map),
    _dir(dir) {
    _dead = false;
    _damage = 0;
}

Weapon::~Weapon() {}

void Weapon::update(float deltaTime) {
    sf::Vector2f movement, initial;
    initial = _sprite.getPosition();
    movement.x = (_dir == directions::left ? -_speed.x : (_dir == directions::right ? _speed.x : 0));
    movement.y = (_dir == directions::up ? -_speed.y : (_dir == directions::down ? _speed.y : 0));
    sf::Vector2f maxMovement = _map->getMaxMovement(initial,movement*deltaTime,_bounds);
    if (movement*deltaTime != maxMovement) hit();
    cmove(maxMovement);
}

float Weapon::getDamage() {
    return _damage;
}

bool Weapon::isAlive() {
    return !_dead;
}

void Weapon::hit() {

}

directions Weapon::getDirection() {
    return _dir;
}

void Weapon::intersectsWith(Collisionable* c) {
    Prop* prop = dynamic_cast<Prop*>(c);
    if (prop != nullptr) {
        hit();
        return;
    }
    Player* player = dynamic_cast<Player*>(c);
    if (player != nullptr) {
        hit();
        return;
    }
}