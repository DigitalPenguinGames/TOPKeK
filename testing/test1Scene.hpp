#ifndef __TESTSCENE_HPP__
#define __TESTSCENE_HPP__

#include "../Scene.hpp"

class Game;
class test1Scene : public Scene {
public:
	test1Scene(sf::RenderWindow* w);
	~test1Scene();

	void processInput();
	void update(float deltaTime);
	void render();

private:
	Game* game;
	sf::RectangleShape rectangle;
};