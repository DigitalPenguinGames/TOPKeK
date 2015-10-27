#include "FairyShoot.hpp"

FairyShoot::FairyShoot(Map* map, sf::Vector2f pos, sf::Vector2f dest, directions dir, float damage) : Weapon(map, pos, dir) {

    _sprite.setTexture(Resources::fairyShoot);
    //_sprite.setOrigin(_sprite.getLocalBounds().width/2,_sprite.getLocalBounds().height/2);
    _sprite.setPosition(pos);

    _destiny = dest;
    _damage = damage;
    _lifeTime =  0.0;
    _maxLifeTime = 10;
    _speed = sf::Vector2f(10,10);
    _bounds = FairyShoot::bounds();

    _shader = &Resources::fairyShootShader;
    Resources::fairyShootShader.setParameter("texture" , sf::Shader::CurrentTexture);
}

FairyShoot::~FairyShoot(){};

void FairyShoot::hit(){
    _dead = true;
}

void FairyShoot::update(float deltaTime){
    _lifeTime += deltaTime;
    // Cambiar la formula para que no esté rota :D
    _speed.x = (0.8*_speed.x + 0.4*(_destiny.x - getPosition().x )) * deltaTime;
    _speed.y = (0.8*_speed.y + 0.4*(_destiny.y - getPosition().y )) * deltaTime;

    /*
     * int signY = _speed.y/std::abs(_speed.y);
    if( std::abs(_speed.y) < 0.2) _speed.y = 0.2 * signY;
    int signX = _speed.x/std::abs(_speed.x);
    if( std::abs(_speed.x) < 0.2) _speed.x = 0.2 * signX;
*/
    float module = getModule(sf::Vector2f(0,0), _speed);
    if(module < 0.2){
        _speed.x = _speed.x/module * 0.3;
        _speed.y = _speed.y/module * 0.3;
    }
    _sprite.move(_speed);
    std::cout << _speed.x << " , " << _speed.y << std::endl;
//    if(std::abs(_speed.x)+std::abs(_speed.y) < 0.2f) _dead = true;

    if( _lifeTime > _maxLifeTime || _sprite.getPosition() == _destiny){
       _dead = true;
    }

}

void FairyShoot::draw(sf::RenderTarget *target){
    Resources::fairyShootShader.setParameter("posF", getPosition());
    Resources::fairyShootShader.setParameter("posS", _destiny);
    Resources::fairyShootShader.setParameter("time",_lifeTime);
    target->draw(_sprite, _shader);
}

sf::IntRect FairyShoot::bounds() {
    return sf::IntRect(1,2,6,6);
}
