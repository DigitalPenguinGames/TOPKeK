#include "EnemyPenguin.hpp"

EnemyPenguin::EnemyPenguin(ScenePlayable* scene, Map* map, sf::Vector2f pos) : Enemy(scene, map,pos) {

    _description = Resources::descriptions[penguinEnemyDescription];
    _dir = directions::down;
    _action = linkActions::move;

    _elapsedWalking = 0.2;
    _speed = sf::Vector2f(15,15);

    _walkBounds = sf::IntRect(2,2,12,12);
    _bounds = sf::IntRect(2,8,5,7);

    _time = 0;
    _damage = 0.5;
    _antPos = sf::Vector2f(0,0);
    _sliding = false;
    _isMoving = false;
    _preparing = false;
    _sprite.setTexture(Resources::penguinEnemy);
    _sprite.setTextureRect(_description[_action*4+_dir][_currentAnimation%_description[_action*4+_dir].size()]);

}

void EnemyPenguin::setPrep(){
    _preparing = true;
    _elapsedWalking = 1;
    _currentAnimation = 0;
    _sprite.setTexture(Resources::penguinEnemyAttack);
    _description = Resources::descriptions[penguinEnemyDescriptionPrep];
}

void EnemyPenguin::setAttack(){
    _moving = 1;
    _sliding = true;
    _sprite.move(0,7);
    _preparing = false;
    _currentAnimation = 0;
    if(_dir == directions::up || _dir == directions::down )_bounds = sf::IntRect(4,0,9,7);
    else _bounds = sf::IntRect(2,0,11,5);
    _sprite.setTexture(Resources::bulletPenguin);
    _description = Resources::descriptions[penguinEnemyDescriptionAttack];
}

void EnemyPenguin::setWalk(){
    _preparing = false;
    _sliding = false;
    _sprite.move(0,-7);
    _elapsedWalking = 0.2;
    _currentAnimation = 0;
    _bounds = sf::IntRect(2,8,5,7);
    _sprite.setTexture(Resources::penguinEnemy);
    _description = Resources::descriptions[penguinEnemyDescription];
}

void EnemyPenguin::update(float deltaTime) {

    _time -= deltaTime;
    if (_time < 0 && (!_preparing) && (!_sliding)) {
        _time += 5;
        _dir = directions(std::rand()%4);

        int r = rand()%2;
        if (r == 0) {
            setPrep();
            _time = 3;
        }
    }
    if(_preparing && _time < 0){
        setAttack();
        _time = 6;
    }
    else if (_sliding){
        if(_time < 0) {
            _time = 5;
            setWalk();
        }
    }

    if(_antPos == getPosition() && _isMoving){
        _dir = directions(std::rand()%4);
    }
    _antPos = getPosition();

    if(!_preparing && ! _sliding) {
        _speed = sf::Vector2f(15,15);
        _moving = (std::rand()%2 == 0);
    }
    if(_sliding) {
        _speed = sf::Vector2f(30,30);
        _moving = 1;
    }
    _isMoving = _moving;
    if(_preparing) {
        _speed = sf::Vector2f(0,0);
        _moving = (std::rand()%2 == 0);
        _isMoving = false;
    }
    Enemy::update(deltaTime);
}

sf::Vector2f EnemyPenguin::getBotPosition() {
    return sf::Vector2f(_sprite.getPosition().x+_bounds.left+_bounds.width/2, _sprite.getPosition().y);
}
