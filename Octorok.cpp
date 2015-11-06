#include "Octorok.hpp"
#include "ScenePlayable.hpp"
#include "Prop.hpp"

Octorok::Octorok(ScenePlayable* scene, Map* map, sf::Vector2f pos) : Enemy(scene, map,pos) {
    _sprite.setTexture(Resources::overEnemies);
    _description = Resources::descriptions[octorokDescriptions];
    _dir = directions(std::rand()%4);
    _action = linkActions::move;

    _elapsedWalking = 0.5;
    _speed = sf::Vector2f(7,7);

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
        _time += 2;
        directions dirAux = directions(pointsToDirection4(getPosition(),_scene->getPlayer()->getPosition()));
        if (dirAux == _dir && _blocked) dirAux = directions(rand()%4);
        _dir = dirAux;
    }
    if (std::rand()%(FRAMERATE*3) == 0) shot();
    _moving = true;
    Enemy::update(deltaTime);
    _blocked = false;
}

sf::Vector2f Octorok::getBotPosition() {
    return sf::Vector2f(_sprite.getPosition().x+_bounds.left+_bounds.width/2, _sprite.getPosition().y);
}

void Octorok::resetMove() {
    _blocked = true;
    Collisionable::resetMove();
}

void Octorok::shot() {
    SoundManager::playSound("shootBigBall");
    sf::Vector2f offset;
    offset.x = getHorizontal(_dir) * (getBounds().left+getBounds().width /2);
    offset.y = getVertical  (_dir) * (getBounds().top +getBounds().height/2);
    _scene->addEnemyWeapon(new RockProjectile(_map, getRelativeCenter(_sprite.getPosition(), getBounds(), RockProjectile::bounds()) + offset, _dir));
}

void Octorok::drop() {
    int r = std::rand()%10;
    objectType dropType;
    bool droping = true;
    if (r == 0) dropType = objectType::bomb;
    else if (r <= 1) dropType = objectType::fullHeal;
    else if (r <= 3) dropType = objectType::rupee;
    else if (r <= 6) dropType = objectType::halfHeal;
    else droping = false;
    if (droping) _scene->addObject(new Object(dropType, 
        sf::Vector2f(_sprite.getPosition().x+_bounds.left+_bounds.width/2, 
                     _sprite.getPosition().y+_bounds.top+_bounds.height/2),
        _scene));
}