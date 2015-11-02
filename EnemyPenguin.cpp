#include "EnemyPenguin.hpp"

EnemyPenguin::EnemyPenguin(ScenePlayable* scene, Map* map, sf::Vector2f pos) : Enemy(scene, map,pos) {

    _description = Resources::descriptions[penguinEnemyDescription];
    _dir = directions::down;
    _action = linkActions::move;

    _elapsedWalking = 0.2;
    _speed = sf::Vector2f(15,15);

    _walkBounds = sf::IntRect(2,2,12,12);
    _bounds = _walkBounds;

    _time = 0;
    _damage = 0.5;
    _preparing = false;
    _attacking = false;
    _sprite.setTexture(Resources::penguinEnemy);
    _sprite.setTextureRect(_description[_action*4+_dir][_currentAnimation%_description[_action*4+_dir].size()]);

}

void EnemyPenguin::setPrep(){
    _moving = 1;
    _elapsedWalking = 1;
    _preparing = true;
    _sprite.setTexture(Resources::penguinEnemyAttack);
    _description = Resources::descriptions[penguinEnemyDescriptionPrep];
}

void EnemyPenguin::setAttack(){
    _moving = 1;
    _attacking = true;
    _preparing = false;
    _sprite.setTexture(Resources::bulletPenguin);
    _description = Resources::descriptions[penguinEnemyDescriptionAttack];
}

void EnemyPenguin::setWalk(){
    _preparing = false;
    _attacking = false;
    _sprite.setTexture(Resources::penguinEnemy);
    _description = Resources::descriptions[penguinEnemyDescription];
}

void EnemyPenguin::update(float deltaTime) {

    _time -= deltaTime;
    if (_time < 0 && !_preparing && !_attacking) {
        _time += 5;
        _dir = directions(std::rand()%4);
        //sf::Vector2f offset;
        //offset.x = getHorizontal(_dir) * (getBounds().left+getBounds().width /2);
        //offset.y = getVertical  (_dir) * (getBounds().top +getBounds().height/2);

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
    else if (_attacking){
        if(_time < 0) {
            _time = 5;
            setWalk();
        }
    }

    if(!_preparing && ! _attacking) _moving = (std::rand()%2 == 0);
    Enemy::update(deltaTime);
}

sf::Vector2f EnemyPenguin::getBotPosition() {
    return sf::Vector2f(_sprite.getPosition().x+_bounds.left+_bounds.width/2, _sprite.getPosition().y);
}
