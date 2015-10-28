#ifndef __SCENEMENU_HPP__
#define __SCENEMENU_HPP__

#include "utils.hpp"
#include "Scene.hpp"
#include "DataManager.hpp"
#include "SceneChanger.hpp"
#include "GUI/Label.hpp"
#include "GUI/Frame.hpp"
#include "GUI/Layout.hpp"
#include "GUI/Widget.hpp"
#include "GUI/Button.hpp"
#include "GUI/VLayout.hpp"
#include "GUI/Container.hpp"
#include "GUI/ImgButton.hpp"
#include "GUI/TextButton.hpp"
#include "GUI/ImgTextButton.hpp"

class Game;
class SceneMenu : public Scene  {

public:
    SceneMenu(Game* g, sf::RenderWindow* w);
    ~SceneMenu();

    void update(float deltaTime);
    void processInput();
    void render(sf::RenderTarget* target);

private:

    float _elapsed;

    Game* _game;

    int _buttonSelected;

    Frame _menu;
    VLayout* _menuLayout;
};



#endif