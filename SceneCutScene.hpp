#ifndef SCENECUTSCENE_HPP
#define SCENECUTSCENE_HPP


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

class SceneCutScene: public Scene  {

public:
    SceneCutScene(Game* g, sf::RenderWindow* w,
                  std::vector<sf::Texture>& anim, std::vector<float>& animParam,
                  std::vector<animationActions>& actions, std::vector<std::string> animText);

    ~SceneCutScene();

    void init(sf::Vector2f aux = sf::Vector2f(0,0));

    void update(float deltaTime);

    void processInput();

    void render(sf::RenderTarget* target);

    void resizing();
private:

    int _index;
    float _elapsed;
    int _buttonSelected;

    Game* _game;
    Frame _menu;
    VLayout* _menuLayout;
    VLayout* _selectedLayout;

    sf::Sprite _sprite;
    std::vector<sf::Texture>  _animation;
    std::vector<float>   _animationParam;
    std::vector<animationActions> _animationActions;
    std::vector<std::string> _animationText;


};

#endif // SCENECUTSCENE_HPP
