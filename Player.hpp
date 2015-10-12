#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include "utils.hpp"
#include "Collisionable.hpp"
#include "Resources.hpp"
#include "Projectile.hpp"
#include "LightSprite.hpp"
#include "Map.hpp"

#define ATTACKTIMERANIMATION 0.5
#define ELAPSEDWALKING 0.18

class Player : public Collisionable {
public:
    Player();
    ~Player();

    void update(float deltaTime);
    void draw(sf::RenderTarget* w);

    void attack();
    void move(directions dir);

    directions getDirection();
    sf::Vector2f getPositionTransition();
    bool isAttacking();
    sf::IntRect getSwordRect();
    float getSwordDamage();
    bool isAlive();


    void getHit(float much, sf::Vector2f from);
    void setPosition(sf::Vector2f pos);
    void setLight(Light* light);
    void setMap(Map* map);

private:
    Map* _map;
    directions _dir;
    linkActions _action;
    LightSprite _lightSprite;
    SpriteSheetDescription _description;

    float _hp;
    float _maxHp;
    bool _dead;
    float _hitedTimer;

    int _currentAnimation;
    float _elapsedAnimation;

    bool _moving;

    bool _attacking;
    float _elapsedAttack;

    Projectile _sword;
    sf::IntRect _walkBounds;



};
#endif
