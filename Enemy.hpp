#ifndef __ENEMY_HPP__
#define __ENEMY_HPP__

#include "utils.hpp"
#include "Map.hpp"
#include "Collisionable.hpp"

class ScenePlayable;
class Enemy : public Collisionable {
public:
    Enemy(ScenePlayable* scene, Map* map, sf::Vector2f pos);
    virtual ~Enemy();

    virtual void update(float deltaTime);
    virtual void draw(sf::RenderTarget* window);

    void setMap(Map* map);
    void getHit(float much, sf::Vector2f from);
    virtual void drop();

    bool isAlive();
    float getDamage();
    sf::IntRect getWalkBounds();
    sf::IntRect getGlobalWalkBounds();

    virtual void intersectsWith(Collisionable* c);

protected:
    ScenePlayable* _scene;
    Map* _map;
    sf::Vector2f _speed;
    sf::IntRect _walkBounds;

    float _hp;
    bool _dead;
    float _damage;
    float _hitedTimer;

    directions _dir;
    linkActions _action;
    SpriteSheetDescription _description;

    float _elapsedAttack;
    float _elapsedWalking; // Time between frames of walking
    float _elapsedAnimation;

    int _currentAnimation;

    bool _moving;
    bool _attacking;

};

#endif
