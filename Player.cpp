#include "Player.hpp"

Player::Player(){

    _sprite.setPosition(70,70); // Hardcoded
    
    _dir = directions::down;
    _action = linkActions::move;
    _description = Resources::descriptions[linkSpritesDescriptions];

    _elapsedAnimation = 0;
    _currentAnimation = 0;

    _moving = false;
    _attacking = false;

    _walkBounds = sf::IntRect(4,13,8,2);
    _bounds = sf::IntRect(4,2,8,12);

    std::vector<sf::Texture*> textures(9);
    textures[directions::none]  = &Resources::linkSet;
    textures[directions::up]    = &Resources::linkSetT;
    textures[directions::left]  = &Resources::linkSetL;
    textures[directions::down]  = &Resources::linkSetB;
    textures[directions::right] = &Resources::linkSetR;
    textures[directions::topLeft]  = &Resources::linkSetTL;
    textures[directions::botLeft]  = &Resources::linkSetBL;
    textures[directions::topRight] = &Resources::linkSetTR;
    textures[directions::botRight] = &Resources::linkSetBR;

    _lightSprite = LightSprite(_description, textures);

    _hp = DataManager::getFloat("linkHp",4.0f);
    _maxHp = DataManager::getFloat("linkMaxHp",4.0f);
    _dead = false;
    _hitedTimer = 0;
}

Player::~Player(){}

void Player::update(float deltaTime) {
    _hitedTimer -= deltaTime;
    if(_moving) {
        _elapsedAnimation -= deltaTime;
        if (_elapsedAnimation < 0) {
            _elapsedAnimation += ELAPSEDWALKING;
            _currentAnimation = (_currentAnimation+1)%_description[_action*directionsQtty+_dir].size();
            if((_currentAnimation % 2) == 0) SoundManager::playSound("stepGround");
        }
    }
    
    if (_attacking) {
        _elapsedAttack -= deltaTime;
        if (_elapsedAttack <= 0) {
            _action = linkActions::move;
            _attacking = false;
        }
    }
    else if (_moving) {
        sf::Vector2f movement, speed(50,50), initial;
        initial = _sprite.getPosition();
        movement.x = getHorizontal(_dir) * speed.x;
        movement.y = getVertical(_dir) * speed.y; 
        cmove(_map->getMaxMovement(initial,movement*deltaTime,_walkBounds));
        _moving = false;
    }
    _lightSprite.update(_sprite.getPosition(),_dir,_action,_currentAnimation);
}

void Player::draw(sf::RenderTarget* w) {
    if (_attacking) {
        _sword.draw(w);
    }
    if (_hitedTimer > 0) {
        Resources::cInvert.setParameter("deltaTime", _hitedTimer);
        _lightSprite.draw(w,&Resources::cInvert);
    }
   else {
        _lightSprite.draw(w);
    }
}

bool Player::isAlive() {
    return !_dead;
}

sf::Vector2f Player::getBotPosition() {
    return sf::Vector2f(_sprite.getPosition().x+_bounds.left+_bounds.width/2, _sprite.getPosition().y + 16);
}

void Player::getHit(float much, sf::Vector2f from) {
    if (_hitedTimer > 0) return;
    Resources::cInvert.setParameter("Time", 1.5);
    _hitedTimer = 1.5; // One second of invulneravility;
    _hp -= much;
    _dead = _hp <= 0;
    std::cout << "it hurts " << _hp << std::endl;
}

void Player::move(directions dir) {
    if (_attacking) return;
    _moving = true;
    _dir = dir;
}
    
void Player::attack() {

    if(!_attacking) {
        SoundManager::playSound("stabSword");
        int n = rand()%10;
        if(n < 4)
        SoundManager::playSound("linkAttack"+std::to_string(n));
        _attacking = true;
        _action = linkActions::attack;
        _sword.init(_dir, _sprite.getPosition());

        _sword.setPosition(sf::Vector2f(        // V posar la posició del player
                        _sword.getPosition().x + ((10)  * (_dir == directions::up   ))
                                               + ((5)   * (_dir == directions::down ))
                                               + ((11)  * (_dir == directions::right))
                                               + (4     * (_dir == directions::left )),
                        _sword.getPosition().y + ((12)  * (_dir == directions::right))
                                               + ((5)   * (_dir == directions::left ))
                                               + ((11)  * (_dir == directions::down ))
                                               + (4     * (_dir == directions::up   ))
                        ));
        _elapsedAttack = ATTACKTIMERANIMATION;
    }
}

sf::Vector2f Player::getPositionTransition() {
    sf::Vector2f pos = _sprite.getPosition();
    pos.x += _walkBounds.left + _walkBounds.width/2;
    pos.y += _walkBounds.top + _walkBounds.height/2;
    return pos;
}

directions Player::getDirection() {
    return _dir;
}

sf::IntRect Player::getSwordRect() {
    sf::Vector2f pos = _sword.getPosition();
    sf::IntRect gSword = _sword.getGlobalBound();
    sf::IntRect sword(pos.x - gSword.left, pos.y - gSword.top, gSword.width, gSword.height);
    switch(_dir){
        case directions::down:
            return sf::IntRect(pos.x+sword.left, pos.y+sword.top, sword.width, sword.height);
        case directions::up:
            return sf::IntRect(pos.x-sword.left, pos.y-sword.top, -sword.width, -sword.height);
        case directions::right:
            return sf::IntRect(pos.x+sword.top, pos.y-sword.left, sword.height, -sword.width);
        case directions::left:
            return sf::IntRect(pos.x-sword.top, pos.y+sword.left, -sword.height, sword.width);
        default:
            return sf::IntRect(0,0,0,0); // This will never be called
    }
}

sf::IntRect Player::getWalkBounds() {
    return _walkBounds;
}


sf::IntRect Player::getGlobalWalkBounds() {
    return sf::IntRect(_walkBounds.left+_sprite.getPosition().x, _walkBounds.top + _sprite.getPosition().y, _walkBounds.width, _walkBounds.height);
}


float Player::getSwordDamage() {
    return 2; //SWORDDAMAGE sword.getDamage()
}

bool Player::isAttacking() {
    return _attacking;
}


void Player::setPosition(sf::Vector2f pos) {
    Collisionable::setPosition(pos);
    _lightSprite.setPosition(pos);
}

void Player::resetMove() {
    Collisionable::resetMove();
    _lightSprite.setPosition(_pastPosition);
}

void Player::setLight(Light* light) {
    _lightSprite.setLight(light);
    _sword.setLight(light);
}

void Player::setMap(Map* map) {
    _map = map;
}
