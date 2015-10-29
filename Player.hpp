#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include "Map.hpp"
#include "utils.hpp"
#include "Resources.hpp"
#include "Projectile.hpp"
#include "LightSprite.hpp"
#include "Collisionable.hpp"
#include "TextBoxManager.hpp"

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
    sf::IntRect getWalkBounds();
    sf::IntRect getGlobalWalkBounds();
    float getSwordDamage();
    bool isAlive();
    sf::Vector2f getBotPosition();
    float getHp();
    float getMaxHp();

    void getHit(float much, sf::Vector2f from);
    void setPosition(sf::Vector2f pos);
    void resetMove();
    void intersectsWith(Collisionable* c);

    void setLight(Light* light);
    void setMap(Map* map);

    bool speaking() const;
    void setSpeaking(bool speaking);
    void setSpeaking(bool speaking, std::string name);

private:
    Map* _map;
    directions _dir;
    linkActions _action;
    LightSprite _lightSprite;
    SpriteSheetDescription _description;

    float _hp;
    float _maxHp;
    float _hitedTimer;
    float _elapsedAttack;
    float _elapsedAnimation;

    int _currentAnimation;

    bool _dead;
    bool _moving;
    bool _attacking;
    bool _speaking;

    Projectile _sword;
    sf::IntRect _walkBounds;



};
#endif
