#include "SceneCutScene.hpp"


SceneCutScene::SceneCutScene(Game *g, sf::RenderWindow *w ,
                             std::vector<sf::Texture>& anim, std::vector<float>& animParam, std::vector<animationActions>& actions)
                            : Scene(g,w,sceneTypes::cutScene, "cutScene"),_menu(*w,w->getDefaultView()){
    _animation = anim;
    _animationParam = animParam;
    _animationActions = actions;
    _game = g;
    _window = w;
    _index = 0;
    _sprite.setTexture(_animation[_index]);
    initView(&_view, sf::Vector2i(WINDOWRATIOX, WINDOWRATIOY));
}

SceneCutScene::~SceneCutScene(){

}

void SceneCutScene::init(sf::Vector2f){

}

void SceneCutScene::update(float deltaTime) {
    _elapsed += deltaTime;

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
    }
    InputManager::update();
    if(_elapsed > 0.5 && InputManager::action(InputAction::action)){
        initView(&_view, sf::Vector2i(WINDOWRATIOX, WINDOWRATIOY));
        _sprite.setTexture(_animation[_index],true);
        _view.setCenter(_sprite.getPosition().x+_sprite.getGlobalBounds().width/2, _sprite.getPosition().y+_sprite.getGlobalBounds().height/2);
        ++_index;
        if(_index >= _animation.size()) {
           --_index;
        }
        _elapsed = 0;
    }
}

void SceneCutScene::render(sf::RenderTarget*) {
    _window->setView(_view);
    _window->draw(_sprite);

}

void SceneCutScene::resizing() {
    initView(&_view, sf::Vector2i(WINDOWRATIOX, WINDOWRATIOY));
}
