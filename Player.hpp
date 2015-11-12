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
    void setHp(float hp);
    float getMaxHp();

    void getHit(float much, sf::Vector2f from);
    void setPosition(sf::Vector2f pos);
    void resetMove();
    void intersectsWith(Collisionable* c);

    void setLight(Light* light);
    void setMap(Map* map);
    void setDirection(directions dir);

    bool speaking() const;
    void setSpeaking(bool speaking);
    void setSpeaking(bool speaking, std::string name);


    int keys() const;
    int bombs() const;
    int rupias() const;
    void setKeys(int keys);
    void setBombs(int bombs);
    void setRupias(int rupias);

    void save();


private:
    Map* _map;
    directions _dir;
    linkActions _action;
    LightSprite _lightSprite;
    SpriteSheetDescription _description;

    float _hitedTimer;
    float _elapsedAttack;
    int _currentAnimation;
    float _elapsedAnimation;

    float _hp;
    float _maxHp;
    int _keys;
    int _bombs;
    int _rupias;

    bool _dead;
    bool _moving;
    bool _attacking;
    bool _speaking;

    Projectile _sword;
    sf::IntRect _walkBounds;



};
#endif
