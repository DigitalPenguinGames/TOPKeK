#include "SceneCutScene.hpp"
#include "Game.hpp"


SceneCutScene::SceneCutScene(Game *g, sf::RenderWindow *w ,
                             std::vector<sf::Texture>& anim, std::vector<float>& animParam, std::vector<animationActions>& actions, std::vector<std::string> animText)
                            : Scene(g,w,sceneTypes::cutScene, "cutScene"),_menu(*w,w->getDefaultView()){
    _game = g;
    _window = w;
    _animation = anim;
    _animationText = animText;
    _animationParam = animParam;
    _animationActions = actions;

    _elapsed = 0;
}

SceneCutScene::~SceneCutScene(){

}

void SceneCutScene::init(sf::Vector2f){
    _index = 0;

    TextBoxManager::setSize(50,10);
    _sprite.setTexture(_animation[_index]);
    TextBoxManager::setText(_animationText[_index],3);
    TextBoxManager::setTexture(0);
    initView(&_view, sf::Vector2i(70,50));
    _view.setCenter(_sprite.getPosition().x+_sprite.getGlobalBounds().width/2, _view.getCenter().y);
}

void SceneCutScene::update(float deltaTime) {
    _elapsed += deltaTime;

    if(_animationActions[_index] == action_skip & _elapsed > _animationParam[_index]){
        ++_index;
        if(_index >= int(_animation.size())) {
           --_index;
            DataManager::reset();
            sf::Vector2f playerPos = sf::Vector2f(50,50);
            std::string nextScene = "menu";

            changeScene(new SceneChanger(sf::Vector2f(0,0),nextScene,playerPos));
            //ScenePlayable* aux = dynamic_cast<ScenePlayable*>( (*_game->_scenes.find(nextScene)).second );
            //aux->setPlayer(new Player());
            //aux->getPlayer()->setPosition(playerPos);
            DataManager::setBool("game", true);
        }
        _elapsed = 0;
    }
    if(_elapsed > 0.5 && InputManager::action(InputAction::action)
                                              && (_animationText[_index] == "none"
                                                || (_animationText[_index] != "none" && TextBoxManager::getTextFinished()) ) ){
        ++_index;
        if(_index >= int(_animation.size())) {
           --_index;
            if(_animationActions[_index] == action_skip){
                DataManager::reset();
                sf::Vector2f playerPos = sf::Vector2f(50,50);
                std::string nextScene = "menu";

                changeScene(new SceneChanger(sf::Vector2f(0,0),nextScene,playerPos));

            }
            else {

                DataManager::reset();
                sf::Vector2f playerPos = sf::Vector2f(50,50);
                std::string nextScene = "map0";
                changeScene(new SceneChanger(sf::Vector2f(0,0),nextScene,playerPos));
                ScenePlayable* aux = dynamic_cast<ScenePlayable*>( (*_game->_scenes.find(nextScene)).second );
                aux->setPlayer(new Player());
                aux->getPlayer()->setPosition(playerPos);
                DataManager::setBool("game", true);
            }
        }
        _sprite.setTexture(_animation[_index],true);
        _view.setCenter(_sprite.getPosition().x+_sprite.getGlobalBounds().width/2, _sprite.getPosition().y+_sprite.getGlobalBounds().height/2);
        TextBoxManager::setText(_animationText[_index],3);
        _elapsed = 0;
    }


    if(_animationActions[_index] == animationActions::scrollDown){
        if(_view.getCenter().y + _view.getSize().y/2 < _sprite.getGlobalBounds().height )
            _view.move(0,_animationParam[_index]*deltaTime);
    }
//    _view.setSize(70,50);
    _view.setCenter(_sprite.getPosition().x+_sprite.getGlobalBounds().width/2, _view.getCenter().y);

}

void SceneCutScene::processInput(){

    sf::Event event;
    while(_window->pollEvent(event)){
        if (event.type == sf::Event::Closed) {_window->close(); exit(0);}
        if(_elapsed > _animationParam[_index]) TextBoxManager::processEvent(event);
    }
    InputManager::update();

}

void SceneCutScene::render(sf::RenderTarget* target) {
    target->draw(_sprite);
    if(_animationText[_index] != "none") TextBoxManager::drawText(target,0,0);

}

void SceneCutScene::resizing() {
    initView(&_view, sf::Vector2i(70,50));
}
