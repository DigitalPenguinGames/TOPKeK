#ifndef __WEAPON_HPP__
#define __WEAPON_HPP__

#include "Collisionable.hpp"

class Weapon : public Collisionable {
public:
    Weapon();
    virtual ~Weapon();

    float getDamage();
    bool isAlive();
    virtual void hit(); // Do something when hit
private:
    float _damage;
    bool _dead;
};

#endif