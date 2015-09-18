#ifndef __SCENE_HPP__
#define __SCENE_HPP__

#include "utils.hpp"

class Scene {
public:
	Scene(sf::RenderWindow* w);
	~Scene();

	virtual void init();
	void run();
	void killScene();
protected:
	sf::RenderWindow* _window;
	bool _killed;

	virtual void processInput();
	virtual void update(float deltaTime);
	virtual void render();

};

#endif