#include "SceneMenu.hpp"
#include "Game.hpp"

SceneMenu::SceneMenu(Game* g, sf::RenderWindow* w) : 
    Scene(g,w,sceneTypes::menu, "menu"),
    _menu(*w,w->getDefaultView()),
    _options(*w,w->getDefaultView()) {
    _game = g;
    
    sf::Vector2u targetResolution(640,360);
    initView(&_view, sf::Vector2i(targetResolution));

    _buttonSelected = -1;
    _menuLayout = nullptr;
    _optionsLayout = nullptr;
}

SceneMenu::~SceneMenu() {
}

void SceneMenu::init(sf::Vector2f ) {
    _elapsed = 0;
    _selectedLayout = _menuLayout;
    resetMenuPosition();
    initButtons();
}

void SceneMenu::processInput() {
    sf::Event event;
    while (_window->pollEvent(event)) {
        if (_selectedLayout == _menuLayout) _menu.processEvent(event);
        else if(_selectedLayout == _optionsLayout) _options.processEvent(event);
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

        changeButton(+1);
    }
    if (InputManager::action(InputAction::menuUp)) {
        _elapsed = 0;
        _window->setMouseCursorVisible(false);
        changeButton(-1);
        
    }
    if (InputManager::action(InputAction::menuEnter)) {
        if (_buttonSelected == -1) _buttonSelected = 0;
        if (dynamic_cast<Button*>(_selectedLayout->at(_buttonSelected)) != nullptr)
            dynamic_cast<Button*>(_selectedLayout->at(_buttonSelected))->onClick(sf::Event(),*dynamic_cast<Button*>(_selectedLayout->at(_buttonSelected)));
    }
    float axis = InputManager::action(InputAction::menuMovement);
    if (std::abs(axis) > 0.5) {
        _elapsed = 0;
        _window->setMouseCursorVisible(false);
        if (axis < 0) changeButton(-1);
        else changeButton(+1);
        
    }

}

void SceneMenu::update(float deltaTime) {
    _elapsed += deltaTime;
}

void SceneMenu::render(sf::RenderTarget*) {
    _window->setView(_window->getDefaultView());
    if (_selectedLayout == _menuLayout) _menu.draw();
    else if(_selectedLayout == _optionsLayout) _options.draw();
}



void SceneMenu::resetMenuPosition() {
    if (_buttonSelected >= 0 && dynamic_cast<TextButton*>(_selectedLayout->at(_buttonSelected)) != nullptr) dynamic_cast<TextButton*>(_selectedLayout->at(_buttonSelected))->onMouseLeft();
    _buttonSelected = -1;
}

void SceneMenu::initButtons() {
    delete _menuLayout;
    _menuLayout = new VLayout;
    _selectedLayout = _menuLayout;
    _menuLayout->setSpace(5);

    if (DataManager::getBool("game", false)) {
        TextButton* resB;
        resB = new TextButton("Continue", Resources::pauseMenuFont);
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
    resB = new TextButton("New Game", Resources::pauseMenuFont); // New game
    resB->onClick = [this](const sf::Event&, Button&) {
        changeScene(new SceneChanger(sf::Vector2f(0,0), "cutScene", sf::Vector2f(0,0))); 
    };

    TextButton* resB2;
    resB2 = new TextButton("Options", Resources::pauseMenuFont);
    resB2->onClick = [this](const sf::Event&, Button&) { 
         _selectedLayout = _optionsLayout;
         _buttonSelected = 1;
    };

    TextButton* exitB;
    exitB = new TextButton("Exit", Resources::pauseMenuFont);
    exitB->onClick = [this](const sf::Event&, Button&){ exit(0); };
    _menuLayout->add(resB);
    _menuLayout->add(resB2);
    _menuLayout->add(exitB);
    _menu.setLayout(_menuLayout);

    // Options

    delete _optionsLayout;
    _optionsLayout = new VLayout;
    _options.setLayout(_optionsLayout);
    _optionsLayout->setSpace(10);

    Label* musicLabel;
    musicLabel = new Label("Music Volume", Resources::pauseMenuFont);
    HLayout* musicLayout = new HLayout();
    musicLayout->setSpace(5);

    Label* soundLabel;
    soundLabel = new Label("Sound Volume", Resources::pauseMenuFont);
    HLayout* soundLayout = new HLayout();
    soundLayout->setSpace(5);


    TextButton* returnToMenu = new TextButton("    Return", Resources::pauseMenuFont);
    returnToMenu->onClick = [this](const sf::Event&, Button&) {
        init();
    };

    ImgButton* spacer = new ImgButton(Resources::emptyHeart,Resources::emptyHeart);
    spacer->setSize(sf::Vector2f(0, 330));
    spacer->setPosition(200,0);

    // _optionsLayout->add(musicLabel);
    // _optionsLayout->add(musicLayout);
    // _optionsLayout->add(soundLabel);
    // _optionsLayout->add(soundLayout);
    // _optionsLayout->add(spacer);
    // _optionsLayout->add(returnToMenu);

    TextButton* musicMute;
    musicMute = new TextButton("    Mute", Resources::pauseMenuFont);
    musicMute->onClick = [this](const sf::Event&, Button&) {/*SoundManager::setMusicVolumen(0);*/};
    TextButton* music50;
    music50 = new TextButton("     50%", Resources::pauseMenuFont);
    music50->onClick = [this](const sf::Event&, Button&) {/*SoundManager::setMusicVolumen(50);*/};
    TextButton* music100;
    music100 = new TextButton("    100%", Resources::pauseMenuFont);
    music100->onClick = [this](const sf::Event&, Button&) {/*SoundManager::setMusicVolumen(100);*/};
    // musicLayout->add(musicMute);
    // musicLayout->add(music50);
    // musicLayout->add(music100);

    TextButton* soundMute;
    soundMute = new TextButton("    Mute", Resources::pauseMenuFont);
    soundMute->onClick = [this](const sf::Event&, Button&) {
        /*SoundManager::setSoundVolumen(0);*/
    };
    TextButton* sound50;
    sound50 = new TextButton("     50", Resources::pauseMenuFont);
    sound50->onClick = [this](const sf::Event&, Button&) {
        /*SoundManager::setSoundVolumen(50);*/
    };
    TextButton* sound100;
    sound100 = new TextButton("   100", Resources::pauseMenuFont);
    sound100->onClick = [this](const sf::Event&, Button&) {
        /*SoundManager::setSoundVolumen(100);*/
    };
    // soundLayout->add(soundMute);
    // soundLayout->add(sound50);
    // soundLayout->add(sound100);
    
    _optionsLayout->add(musicLabel);
    _optionsLayout->add(musicMute);
    _optionsLayout->add(music50);
    _optionsLayout->add(music100);
    _optionsLayout->add(soundLabel);
    _optionsLayout->add(soundMute);
    _optionsLayout->add(sound50);
    _optionsLayout->add(sound100);
    _optionsLayout->add(returnToMenu);
    


}

void SceneMenu::changeButton(int offset) {
    if (_buttonSelected >= 0 && dynamic_cast<TextButton*>(_selectedLayout->at(_buttonSelected)) != nullptr) dynamic_cast<TextButton*>(_selectedLayout->at(_buttonSelected))->onMouseLeft();
    _buttonSelected = (((_buttonSelected+offset)%_selectedLayout->getNWidgets()+_selectedLayout->getNWidgets())%_selectedLayout->getNWidgets());
    if (dynamic_cast<TextButton*>(_selectedLayout->at(_buttonSelected)) != nullptr) dynamic_cast<TextButton*>(_selectedLayout->at(_buttonSelected))->onMouseEntered();
    
  
}
