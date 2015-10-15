#ifndef __PROP_HPP__
#define __PROP_HPP__ 

#include "Resources.hpp"
#include "Collisionable.hpp"

class Prop : public Collisionable {
public:
    Prop( int gid, sf::Vector2f pos);
    ~Prop();
private:
    SpriteSheetDescription _description;
};


#endif