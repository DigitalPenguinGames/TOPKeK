#include "DungeonDoor.hpp"

DungeonDoor::DungeonDoor(int gid, sf::Vector2f pos) : Collisionable(pos) { // If gid == 0, its a invisible wall
	_gid = gid;
	_posOriginal = pos;
	if (_gid >= 157 && _gid <= 162) {
    	_sprite.setTexture(Resources::dungeonDoorsHorizontal);
    	_description = Resources::descriptions[dungeonDoorsHor];
    }
    else if (_gid >= 163 && _gid <= 168) {
    	_sprite.setTexture(Resources::dungeonDoorsVertical);
    	_description = Resources::descriptions[dungeonDoorsVer];
    }
    updateSprite();

}
	
DungeonDoor::~DungeonDoor() {}

void DungeonDoor::draw(sf::RenderTarget* window) {
	if (_gid < 157) return;
    window->draw(_sprite);
}

void DungeonDoor::open() {
	if (_gid < 157) return;
	if ((_gid-157)%6 == 2 || (_gid-157)%6 == 3) {
		_gid -= 2;
		updateSprite();
	}
}

void DungeonDoor::openWithKey() {
	if (_gid < 157) return;
	if ((_gid-157)%6 >= 4) {
		_gid -= 4;
		updateSprite();
	}
}

void DungeonDoor::close() {
	if (_gid < 157) return;
	if ((_gid-157)%6 < 2) {
		_gid += 2;
		updateSprite();
	}
}

sf::Vector2f DungeonDoor::getBotPosition() {
    return sf::Vector2f(_sprite.getPosition().x+_bounds.left+_bounds.width/2, _sprite.getPosition().y - TILESIZE*4);
}


void DungeonDoor::updateSprite() {
	if (_gid == 0) {
		_bounds = sf::IntRect(0,0,TILESIZE,TILESIZE);
		return;
	}

	if (_gid >= 157 && _gid <= 162) {
    	_sprite.setTextureRect(_description[dungeonHorDoorTypes(_gid-157)][0]);
    }
    else if (_gid >= 163 && _gid <= 168) {
    	_sprite.setTextureRect(_description[dungeonHorDoorTypes(_gid-163)][0]);
    }
    if ((_gid-157)%6 >= 2) {
    	_bounds = sf::IntRect(0,0,_sprite.getLocalBounds().width, _sprite.getLocalBounds().height);
    }
    else _bounds = sf::IntRect(0,0,0,0);
}


void DungeonDoor::setIniCoord(sf::Vector2f coord) {
	_sprite.setPosition(_posOriginal+coord);
}

bool DungeonDoor::isOpened() {
    return (_gid-157)%6 < 2;
}

bool DungeonDoor::needKey() {
    return (_gid-157)%6 >= 4;
}