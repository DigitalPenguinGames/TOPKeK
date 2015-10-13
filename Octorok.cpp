#include "Octorok.hpp"
#include "ScenePlayable.hpp"

Octorok::Octorok(ScenePlayable* scene, Map* map, sf::Vector2f pos) : Enemy(scene, map,pos) {
    _sprite.setTexture(Resources::overEnemies);
    _description = Resources::descriptions[octorokDescriptions];
    _dir = directions::down;
    _action = linkActions::move;

    _elapsedWalking = 0.5;
    _speed = sf::Vector2f(15,15);

    _walkBounds = sf::IntRect(2,2,12,12);
    _bounds = _walkBounds;

    _time = 0;
    _damage = 0.5;

    _sprite.setTextureRect(_description[_action*4+_dir][_currentAnimation%_description[_action*4+_dir].size()]);
}

Octorok::~Octorok() {}

void Octorok::update(float deltaTime) {
    _time -= deltaTime;
    if (_time < 0) {
        _time += 3;
        _dir = directions(std::rand()%4);
        SoundManager::playSound("shootBigBall");
        _scene->addEnemyWeapon(new RockProjectile(_map, getRelativeCenter(_sprite.getPosition(), getBounds(), sf::IntRect(1,2,6,6)), _dir));
    }
    _moving = (std::rand()%2 == 0);
    Enemy::update(deltaTime);
}
