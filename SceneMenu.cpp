#include "SceneMenu.hpp"
#include "Game.hpp"

SceneMenu::SceneMenu(Game* g, sf::RenderWindow* w) : Scene(g,w,sceneTypes::menu, "menu"),_menu(*w) {
    _game = g;
    sf::Vector2u targetResolution(640,360);
    initView(sf::Vector2i(targetResolution));
    sf::Vector2u displayResolution(_view.getSize());

    VLayout* layout = new VLayout;
    layout->setSpace(5);

    TextButton* resB;
    resB = new TextButton("     Play", Resources::pauseMenuFont);
    resB->onClick = [this](const sf::Event&, Button&){
        sf::Vector2f playerPos = DataManager::getVector2f("playerPos",sf::Vector2f(5,5));
        std::string nextScene = DataManager::getString("playerScene","hub");
        ScenePlayable* aux = dynamic_cast<ScenePlayable*>( (*_game->_scenes.find(nextScene)).second );
        aux->setPlayer(new Player());
        changeScene(new SceneChanger(sf::Vector2f(0,0), nextScene, playerPos)); 
    };

    TextButton* resB2;
    resB2 = new TextButton("     Options", Resources::pauseMenuFont);
    resB2->onClick = [this](const sf::Event&, Button&) { 
        
    };

    TextButton* exitB;
    exitB = new TextButton("     Exit", Resources::pauseMenuFont);
    exitB->onClick = [this](const sf::Event&, Button&){ exit(0); };
    layout->add(resB);
    layout->add(resB2);
    layout->add(exitB);
    _menu.setLayout(layout);

}

SceneMenu::~SceneMenu() {
}

void SceneMenu::processInput() {
    sf::Event event;
    while (_window->pollEvent(event)) {
        _menu.processEvent(event);
        if(event.type == sf::Event::MouseMoved) {
            _window->setMouseCursorVisible(true);
        }
    }
}

void SceneMenu::update(float ) {
}

void SceneMenu::render(sf::RenderTarget*) {
    _window->setView(_window->getDefaultView());
    _menu.draw();
}