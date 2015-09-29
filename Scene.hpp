#ifndef __SCENE_HPP__
#define __SCENE_HPP__

#include "utils.hpp"

namespace status{
    enum gameStatus {running, onMenu};
}

class Game;

class Scene {
friend class Game;
public:
	Scene(Game* g, sf::RenderWindow* w, sceneTypes sT);
	virtual ~Scene();

	virtual void init(sf::Vector2f sceneIniCoord);
	void run();
	void killScene();

	sceneTypes getType();
	sf::View* getPtrView();
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
    status::gameStatus _status;
	void display();

};

#endif
