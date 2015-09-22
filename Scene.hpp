#ifndef __SCENE_HPP__
#define __SCENE_HPP__

#include "utils.hpp"

class Scene {
public:
	Scene(sf::RenderWindow* w);
	virtual ~Scene();

	virtual void init();
	void run();
	void killScene();
protected:
	sf::RenderWindow* _window;
	sf::View _view;

	virtual void processInput();
	virtual void update(float deltaTime);
	virtual void render();

private: 
	//sf::RenderWindow* _window;
	bool _killed;

	void display();

	void initView();
};

#endif