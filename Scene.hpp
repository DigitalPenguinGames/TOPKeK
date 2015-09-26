#ifndef __SCENE_HPP__
#define __SCENE_HPP__

#include "utils.hpp"

class Game;

class Scene {
public:
	Scene(Game* g, sf::RenderWindow* w);
	virtual ~Scene();

	virtual void init();
	void run();
	void killScene();
protected:
	Game* _game;
	sf::RenderWindow* _window;
	sf::View _view;

	virtual void processInput();
	virtual void update(float deltaTime);
	virtual void render();
	void initView();

private: 
	//sf::RenderWindow* _window;
	bool _killed;

	void display();

};

#endif