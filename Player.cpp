#include "Player.hpp"

Player::Player(){
    _sprite.setTexture(Resources::linkSet);
    _sprite.setPosition(100,100); // Hardcoded
    _dir = directions::down;
    _action = linkActions::move;
    _description = Resources::descriptions[linkSpritesDescriptions];
    _elapsedAnimation = 0;
    _currentAnimation = 0;
    _attacking = false;
    _moving = false;

    _walkBounds = sf::IntRect(4,13,8,2);
}

Player::~Player(){}

void Player::update(float deltaTime) {
    if(_moving) {
        _elapsedAnimation -= deltaTime;
        if (_elapsedAnimation < 0) {
            _elapsedAnimation += ELAPSEDWALKING;
            _currentAnimation = (_currentAnimation+1)%_description[_action*directionsQtty+_dir].size();
        }
    }
    _sprite.setTextureRect(_description[_action*directionsQtty+_dir][_currentAnimation%_description[_action*directionsQtty+_dir].size()]);

    if (_attacking) {
        _elapsedAttack -= deltaTime;
        if (_elapsedAttack <= 0) {
            _action = linkActions::move;
            _attacking = false;
        }
    }
    else if (_moving) {
        sf::Vector2f movement, speed(50,50);
        movement.x = (_dir == directions::left ? -speed.x : (_dir == directions::right ? speed.x : 0));
        movement.y = (_dir == directions::up ? -speed.y : (_dir == directions::down ? speed.y : 0));
        _sprite.move(movement*deltaTime);
        _moving = false;
    }
}

void Player::draw(sf::RenderTarget* w) {
    // Draw Sword
    if (_attacking) _sword.draw(w);
    w->draw(_sprite);

}


void Player::move(directions dir) {
    if (_attacking) return;
    _moving = true;
    _dir = dir;
}
    
void Player::attack() {
    _attacking = true;
    _elapsedAttack = ATTACKTIMERANIMATION;
    _action = linkActions::attack;
    _sword.init(_dir, _sprite.getPosition());
}

sf::Vector2f Player::getPositionTransition() {
    sf::Vector2f pos = _sprite.getPosition();
    pos.x += _walkBounds.left + _walkBounds.width/2;
    pos.y += _walkBounds.top + _walkBounds.height/2;
    return pos;
}