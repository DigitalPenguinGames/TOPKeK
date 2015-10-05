#include "Projectile.hpp"

Projectile::Projectile() {
    
}

Projectile::~Projectile() {}

void Projectile::update(float deltaTime) {
    _sprite.move(_speed*deltaTime);
}