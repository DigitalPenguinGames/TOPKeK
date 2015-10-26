#ifndef __WEAPON_HPP__
#define __WEAPON_HPP__

#include "utils.hpp"
#include "Collisionable.hpp"
#include "Map.hpp"

class Weapon : public Collisionable {
public:
    Weapon(Map* map, sf::Vector2f pos, directions dir);
    virtual ~Weapon();

    virtual void update(float deltaTime);

    float getDamage();
    bool isAlive();
    directions getDirection();

    virtual void hit(); // Do something when hit
    virtual void intersectsWith(Collisionable* c);
protected:
    Map* _map;
    SpriteSheetDescription _description;
    directions _dir;

    float _damage;
    bool _dead;

    sf::Vector2f _speed;

};

#endif