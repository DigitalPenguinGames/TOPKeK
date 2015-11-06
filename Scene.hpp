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

    virtual void init(sf::Vector2f sceneIniCoord = sf::Vector2f(0,0));
    void run();
    void killScene();

    virtual sceneTypes getType();
    sf::View* getPtrView();
    std::string getSceneName();
protected:
    Game* _game;
    sf::RenderWindow* _window;
    sf::View _view;
    std::string _sceneName;
    bool _focus;

    virtual void processInput();
    virtual void update(float deltaTime);
    void render();
    virtual void render(sf::RenderTarget* target);
    void initView(sf::View* view, sf::Vector2i windowSize);
	void initViewExpanded(sf::View* view, sf::Vector2i windowSize);
	virtual void resizing();
    virtual void changeScene(SceneChanger *sC);

    virtual void display();
private: 
    bool _killed;
    sceneTypes _sceneType;
    SceneChanger* _nextSceneChanger;
    void withoutFocus();

};

#endif
