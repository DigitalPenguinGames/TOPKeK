#ifndef __SCENE_HPP__
#define __SCENE_HPP__

#include "utils.hpp"
#include "SceneChanger.hpp"

class Game;

class Scene {
friend class Game;
public:
	Scene(Game* g, sf::RenderWindow* w, sceneTypes sT, std::string name);
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
	std::string _sceneName;

	virtual void processInput();
	virtual void update(float deltaTime);
	virtual void render();
	void initView();
	void changeScene(SceneChanger *sC);

	virtual void display();
private: 
	bool _killed;
	sceneTypes _sceneType;
    SceneChanger* _nextSceneChanger;

};

#endif
