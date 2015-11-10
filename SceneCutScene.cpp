#include "SceneCutScene.hpp"
#include "Game.hpp"


SceneCutScene::SceneCutScene(Game *g, sf::RenderWindow *w ,
                             std::vector<sf::Texture>& anim, std::vector<float>& animParam, std::vector<animationActions>& actions, std::vector<std::string> animText)
                            : Scene(g,w,sceneTypes::cutScene, "cutScene"),_menu(*w,w->getDefaultView()){
    _game = g;
    _index = 0;
    _window = w;
    _animation = anim;
    _animationText = animText;
    _animationParam = animParam;
    _animationActions = actions;

    _sprite.setTexture(_animation[_index]);

    TextBoxManager::setSize(50,10);
    TextBoxManager::setText(_animationText[_index],4);

    initView(&_view, sf::Vector2i(WINDOWRATIOX, WINDOWRATIOY));
}

SceneCutScene::~SceneCutScene(){

}

void SceneCutScene::init(sf::Vector2f){

}

void SceneCutScene::update(float deltaTime) {
    _elapsed += deltaTime;

    if(_elapsed > 0.5 && InputManager::action(InputAction::action)){
        ++_index;
        initView(&_view, sf::Vector2i(WINDOWRATIOX, WINDOWRATIOY));
        _sprite.setTexture(_animation[_index],true);
        _view.setCenter(_sprite.getPosition().x+_sprite.getGlobalBounds().width/2, _sprite.getPosition().y+_sprite.getGlobalBounds().height/2);
        TextBoxManager::setText(_animationText[_index],5);
        if(_index >= _animation.size()) {
           --_index;
            //_game->changeScene(new SceneChanger(sf::Vector2f(0,0),"menu",sf::Vector2f(0,0)));
        }
        _elapsed = 0;
    }


    if(_animationActions[_index] == animationActions::scrollDown){
        if(_view.getCenter().y + _view.getSize().y/2 < _sprite.getGlobalBounds().height )
            _view.move(0,_animationParam[_index]*deltaTime);
    }
    _view.setSize(70,50);
    _view.setCenter(_sprite.getPosition().x+_sprite.getGlobalBounds().width/2, _view.getCenter().y);

}

void SceneCutScene::processInput(){

    sf::Event event;
    while(_window->pollEvent(event)){
        if (event.type == sf::Event::Closed) {_window->close(); exit(0);}
        TextBoxManager::processEvent(event);
    }
    InputManager::update();

}

void SceneCutScene::render(sf::RenderTarget*) {
    _window->setView(_view);
    _window->draw(_sprite);
    TextBoxManager::drawText(_window,0,0);

}

void SceneCutScene::resizing() {
    initView(&_view, sf::Vector2i(WINDOWRATIOX, WINDOWRATIOY));
}
