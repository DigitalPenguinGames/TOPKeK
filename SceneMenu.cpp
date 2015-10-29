#include "SceneMenu.hpp"
#include "Game.hpp"

SceneMenu::SceneMenu(Game* g, sf::RenderWindow* w) : Scene(g,w,sceneTypes::menu, "menu"),_menu(*w) {
    _game = g;
    _elapsed = 0;
    _buttonSelected = -1;

    sf::Vector2u targetResolution(640,360);
    initView(sf::Vector2i(targetResolution));
    sf::Vector2u displayResolution(_view.getSize());

    _menuLayout = new VLayout;
    _selectedLayout = _menuLayout;
    _menuLayout->setSpace(5);

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
    _menuLayout->add(resB);
    _menuLayout->add(resB2);
    _menuLayout->add(exitB);
    _menu.setLayout(_menuLayout);

}

SceneMenu::~SceneMenu() {
}

void SceneMenu::processInput() {
    sf::Event event;
    while (_window->pollEvent(event)) {
        _menu.processEvent(event);
        if (event.type == sf::Event::Closed) {_window->close(); exit(0);}
        if(event.type == sf::Event::MouseMoved) {
            _window->setMouseCursorVisible(true);
            if (_buttonSelected >= 0) static_cast<TextButton*>(_selectedLayout->at(_buttonSelected))->onMouseLeft();
            _buttonSelected = -1;

        }

    }
    InputManager::update();

    if (_elapsed < 0.2) return;
    if (InputManager::action(InputAction::menuDown)) {
        _elapsed = 0;
        _window->setMouseCursorVisible(false);

        if (_buttonSelected >= 0) static_cast<TextButton*>(_selectedLayout->at(_buttonSelected))->onMouseLeft();
        _buttonSelected = (((_buttonSelected+1)%_selectedLayout->getNWidgets()+_selectedLayout->getNWidgets())%_selectedLayout->getNWidgets());
        static_cast<TextButton*>(_selectedLayout->at(_buttonSelected))->onMouseEntered();
    }
    if (InputManager::action(InputAction::menuUp)) {
        _elapsed = 0;
        _window->setMouseCursorVisible(false);

        if (_buttonSelected >= 0) static_cast<TextButton*>(_selectedLayout->at(_buttonSelected))->onMouseLeft();
        _buttonSelected = (((_buttonSelected-1)%_selectedLayout->getNWidgets()+_selectedLayout->getNWidgets())%_selectedLayout->getNWidgets());
        static_cast<TextButton*>(_selectedLayout->at(_buttonSelected))->onMouseEntered();
    }
    if (InputManager::action(InputAction::menuEnter)) {
        static_cast<Button*>(_selectedLayout->at(_buttonSelected))->onClick(sf::Event(),*static_cast<Button*>(_selectedLayout->at(_buttonSelected)));
    }
    float axis = InputManager::action(InputAction::menuMovement);
    if (std::abs(axis) > 0.5) {
        _elapsed = 0;
        _window->setMouseCursorVisible(false);
        if (axis < 0) {
            if (_buttonSelected >= 0) static_cast<TextButton*>(_selectedLayout->at(_buttonSelected))->onMouseLeft();
            _buttonSelected = (((_buttonSelected-1)%_selectedLayout->getNWidgets()+_selectedLayout->getNWidgets())%_selectedLayout->getNWidgets());
            static_cast<TextButton*>(_selectedLayout->at(_buttonSelected))->onMouseEntered();
        }
        else {
            if (_buttonSelected >= 0) static_cast<TextButton*>(_selectedLayout->at(_buttonSelected))->onMouseLeft();
            _buttonSelected = (((_buttonSelected+1)%_selectedLayout->getNWidgets()+_selectedLayout->getNWidgets())%_selectedLayout->getNWidgets());
            static_cast<TextButton*>(_selectedLayout->at(_buttonSelected))->onMouseEntered();
        }
    }

}

void SceneMenu::update(float deltaTime) {
    _elapsed += deltaTime;
}

void SceneMenu::render(sf::RenderTarget*) {
    _window->setView(_window->getDefaultView());
    _menu.draw();
}