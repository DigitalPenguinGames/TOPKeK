#ifndef __DUNGEONDOOR_HPP__
#define __DUNGEONDOOR_HPP__

#include "utils.hpp"
#include "Collisionable.hpp"
#include "Resources.hpp"

class DungeonDoor : public Collisionable{
public:
	DungeonDoor(int gid, sf::Vector2f pos);
	~DungeonDoor();
	void draw(sf::RenderTarget* window);
	void open();
	void openWithKey();
	void close();
	sf::Vector2f getBotPosition();
	void setIniCoord(sf::Vector2f coord);
	bool isOpened();
	bool needKey();
private:
    SpriteSheetDescription _description;
	int _gid;
	sf::Vector2f _posOriginal;
	void updateSprite();
};

#endif