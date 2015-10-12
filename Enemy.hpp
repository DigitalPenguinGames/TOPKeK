#ifndef __ENEMY_HPP__
#define __ENEMY_HPP__

#include "utils.hpp"
#include "Map.hpp"
#include "Collisionable.hpp"

class Enemy : public Collisionable {
public:
    Enemy(Map* map, sf::Vector2f pos);
    ~Enemy();

    virtual void update(float deltaTime);
    virtual void draw(sf::RenderTarget* window);

    void setMap(Map* map);
protected:
    Map* _map;
    sf::Vector2f _speed;
    sf::IntRect _walkBounds;

    directions _dir;
    linkActions _action;
    SpriteSheetDescription _description;

    int _currentAnimation;
    float _elapsedAnimation;
    float _elapsedWalking; // Time between frames of walking

    bool _moving;

    bool _attacking;
    float _elapsedAttack;
};

#endif