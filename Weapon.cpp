#include "Weapon.hpp"

Weapon::Weapon() {}

Weapon::~Weapon() {}

float Weapon::getDamage() {
    return _damage;
}

bool Weapon::isAlive() {
    return !_dead;
}

void Weapon::hit() {

}
