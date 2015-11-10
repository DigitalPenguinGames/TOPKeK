#include "SceneMenu.hpp"
#include "Game.hpp"

SceneMenu::SceneMenu(Game* g, sf::RenderWindow* w) : Scene(g,w,sceneTypes::menu, "menu"),_menu(*w,w->getDefaultView()) {
    _game = g;
    
    sf::Vector2u targetResolution(640,360);
    initView(&_view, sf::Vector2i(targetResolution));

    _buttonSelected = -1;
}

SceneMenu::~SceneMenu() {
}

void SceneMenu::init(sf::Vector2f ) {
    _elapsed = 0;
    resetMenuPosition();
    initButtons();
}

void SceneMenu::processInput() {
    sf::Event event;
    while (_window->pollEvent(event)) {
        _menu.processEvent(event);
        if (event.type == sf::Event::Closed) {_window->close(); exit(0);}
        else if (event.type == sf::Event::MouseMoved) {
            _window->setMouseCursorVisible(true);
            resetMenuPosition();
        }
        else if (event.type == sf::Event::LostFocus) _focus = false;
        else if (event.type == sf::Event::Resized) resizing();
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
        if (_buttonSelected == -1) _buttonSelected = 0;
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



void SceneMenu::resetMenuPosition() {
    if (_buttonSelected >= 0) static_cast<TextButton*>(_selectedLayout->at(_buttonSelected))->onMouseLeft();
    _buttonSelected = -1;

    _selectedLayout = _menuLayout;
}

void SceneMenu::initButtons() {
    delete _menuLayout;
    _menuLayout = new VLayout;
    _selectedLayout = _menuLayout;
    _menuLayout->setSpace(5);

    if (DataManager::getBool("game", false)) {
        TextButton* resB;
        resB = new TextButton("     Continue", Resources::pauseMenuFont);
        resB->onClick = [this](const sf::Event&, Button&) {
            sf::Vector2f playerPos = DataManager::getVector2f("playerPos");
            std::string nextScene = DataManager::getString("playerScene");
            ScenePlayable* aux = dynamic_cast<ScenePlayable*>( (*_game->_scenes.find(nextScene)).second );
            aux->setPlayer(new Player());
            aux->getPlayer()->setPosition(playerPos);
            changeScene(new SceneChanger(sf::Vector2f(0,0), nextScene, playerPos)); 
        };
        _menuLayout->add(resB);
    }

    TextButton* resB;
    resB = new TextButton("     New Game", Resources::pauseMenuFont); // New game
    resB->onClick = [this](const sf::Event&, Button&) {
        sf::Vector2f playerPos = sf::Vector2f(50,50); 
        std::string nextScene = "hub";
        ScenePlayable* aux = dynamic_cast<ScenePlayable*>( (*_game->_scenes.find(nextScene)).second );
        aux->setPlayer(new Player());
        aux->getPlayer()->setPosition(playerPos);
        changeScene(new SceneChanger(sf::Vector2f(0,0), nextScene, playerPos)); 
        DataManager::setBool("game", true);
    };

    TextButton* resB2;
    resB2 = new TextButton("     Options", Resources::pauseMenuFont);
    resB2->onClick = [this](const sf::Event&, Button&) { 
        sf::Vector2f playerPos = DataManager::getVector2f("playerPos",sf::Vector2f(100,100));
        std::string nextScene = DataManager::getString("playerScene","test");
        ScenePlayable* aux = dynamic_cast<ScenePlayable*>( (*_game->_scenes.find(nextScene)).second );
        aux->setPlayer(new Player());
        aux->getPlayer()->setPosition(playerPos);
        changeScene(new SceneChanger(sf::Vector2f(0,0), nextScene, playerPos)); 
    };

    TextButton* exitB;
    exitB = new TextButton("     Exit", Resources::pauseMenuFont);
    exitB->onClick = [this](const sf::Event&, Button&){ exit(0); };
    _menuLayout->add(resB);
    _menuLayout->add(resB2);
    _menuLayout->add(exitB);
    _menu.setLayout(_menuLayout);
}