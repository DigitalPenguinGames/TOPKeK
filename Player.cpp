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
        movement.x = (_dir == directions::left ? -speed.x : (_dir == directions::right ? speed.x : 0));
        movement.y = (_dir == directions::up ? -speed.y : (_dir == directions::down ? speed.y : 0));
        _sprite.move(movement*deltaTime);
        /*
         if( There is collision on the map with the player ){
            sf::Vector2f fixedMovement = last possible place from initial to _sprite.getPosition();
            sprite.move(fixedMovement);
        }
        */
        _moving = false;
    }
    _lightSprite.update(_sprite.getPosition(),_dir,_action,_currentAnimation);
}

void Player::draw(sf::RenderTarget* w) {
    if (_attacking) {
        // Draw Sword
        _sword.draw(w);
    }
   _lightSprite.draw(w);


}


void Player::move(directions dir) {
    if (_attacking) return;
    _moving = true;
    _dir = dir;
}
    
void Player::attack() {

    SoundManager::playSound("attack");
    _attacking = true;
    _action = linkActions::attack;
    _elapsedAttack = ATTACKTIMERANIMATION;
    _sword.init(_dir, _sprite.getPosition());
    // gd:This code will be at the Sword class (?):D
    // gb:Not a good point, because the player is setting "His" object sword where he decide to do.
    // gb:Sword do not have to know that it is beeing placed on a place or another.
   
    // sf::Vector2f size = sf::Vector2f(_sprite.getGlobalBounds().width,_sprite.getGlobalBounds().height);
   
    _sword.setPosition(sf::Vector2f(        // V posar la posició del player
                    _sword.getPosition().x + ((10) * (_dir == directions::up   ))
                                           + ((5) * (_dir == directions::down ))
                                           + ((11)   * (_dir == directions::right))
                                           + (4            * (_dir == directions::left )),
                    _sword.getPosition().y + ((12) * (_dir == directions::right))
                                           + ((5) * (_dir == directions::left ))
                                           + ((11) * (_dir == directions::down ))
                                           + (4            * (_dir == directions::up   ))
                    ));
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


void Player::setPosition(sf::Vector2f pos) {
    _lightSprite.setPosition(pos);
    _sprite.setPosition(pos);
}

void Player::setLight(Light* light) {
    _lightSprite.setLight(light);
    _sword.setLight(light);
}
