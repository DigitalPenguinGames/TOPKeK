#ifndef __SCENE_HPP__
#define __SCENE_HPP__

#include "utils.hpp"

class Game;

class Scene {
public:
	Scene(Game* g, sf::RenderWindow* w, sceneTypes sT);
	virtual ~Scene();

	virtual void init(sf::Vector2f sceneIniCoord);
	void run();
	void killScene();

	sceneTypes getType();
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
	sceneTypes _sceneType;

	void display();

};

#endif