#include "Game.hpp"
#include "SceneCutScene.hpp"

Game::Game() : _window(sf::VideoMode::getDesktopMode(),"TOPKeK", sf::Style::Close | sf::Style::Resize) {
    _window.setFramerateLimit(FRAMERATE);
    _window.setMouseCursorVisible(false);
    DataManager::load();
    Resources::load();
    _currentScene = nullptr;
    _lastScene = nullptr;
    SoundManager::load();
    TextBoxManager::load();
    if (DataManager::getFloat("MasterVolumen",1.0f) == 1.0f) {
        // SoundManager::playMusic("menuMusic");
        SoundManager::playMusic("overWorld");
    }
//    SoundManager::setLoop(true, "menuMusic");
    SoundManager::setLoop(true, "overWorld");
    initInput();


}

Game::~Game() {
    for (auto it = _scenes.begin(); it != _scenes.end(); ++it) {
        delete it->second;
    }
}

void Game::start() {
    loadScenes();
    // ScenePlayable* aux = dynamic_cast<ScenePlayable*>((*_scenes.find("hub")).second);
    // aux->setPlayer(new Player());
    // changeScene(new SceneChanger(sf::Vector2f(0,0),"hub",sf::Vector2f(0,0)));
    
    changeScene(new SceneChanger(sf::Vector2f(0,0),"cutScene",sf::Vector2f(0,0)));
    //changeScene(new SceneChanger(sf::Vector2f(0,0),"menu",sf::Vector2f(0,0)));

    while (_currentScene != nullptr) {
        _currentScene->run();
    }

    exit(0);
}


void Game::changeScene(SceneChanger* sC) { // This will be called by any scene when something trigers to change to anotheR scene
    std::string sceneName = sC->_nextScene;
    sf::Vector2f sceneIniCoord(0,0);
    if (_currentScene != nullptr) {
        _lastScene = _currentScene;
        _currentScene->killScene();
    }
    auto it = _scenes.find(sceneName);
    if (it == _scenes.end()) {
        std::cout << "The selected scene does not exist: " << sceneName << std::endl;
        exit(EXIT_FAILURE);
    }
    
    std::cout << "Changing to scene " << sceneName << std::endl;

    // Animations
    _currentScene = (*it).second;
    if (_lastScene != nullptr) {
        std::cout << _lastScene->getType() << " " << _currentScene->getType() << std::endl;
        if (_lastScene->getType() == _currentScene->getType()) {
            if (_currentScene->getType() == sceneTypes::outside || _currentScene->getType() == sceneTypes::dungeon) {
                if (sC == nullptr) {std::cout << "ERROR: Changing between two outisde scenes without SceneChanger"<< std::endl;exit(EXIT_FAILURE);}
                
                ScenePlayable* lastScene = dynamic_cast<ScenePlayable*>(_lastScene);
                ScenePlayable* currentScene = dynamic_cast<ScenePlayable*>(_currentScene);



                sf::Vector2f offset;
                directions dir = sC->getChangeDirection();
                if (_currentScene->getType() != sceneTypes::outside) {
                    sC->_nextScenePos = sC->_pos; // IM CHANGING THE ORIGINAL. THIS IS NOT A COPY. ATTENTION!!
                }
                switch (dir) {
                    case directions::left:
                        offset.y = TILESIZE * (sC->_pos.y-sC->_nextScenePos.y);
                        offset.x = -currentScene->getMapSize().x*TILESIZE;
                        break;
                    case directions::right:
                        offset.y = TILESIZE * (sC->_pos.y-sC->_nextScenePos.y);
                        offset.x = lastScene->getMapSize().x*TILESIZE;
                        break;
                    case directions::up:
                        offset.x = TILESIZE * (sC->_pos.x-sC->_nextScenePos.x);
                        offset.y = -currentScene->getMapSize().y*TILESIZE;
                        break;
                    case directions::down:
                        offset.x = TILESIZE * (sC->_pos.x-sC->_nextScenePos.x);
                        offset.y = lastScene->getMapSize().y*TILESIZE;
                        break;
                    default:

                        break;
                }

                std::cout << "OFSEEEEEEEEEEEEEEEEET " << offset.x << " " << offset.y << std::endl;
                sceneIniCoord = lastScene->getSceneCoord()+offset;

                //std::cout << "offset: " << offset.x << " " << offset.y << " sceneIniCoord " << sceneIniCoord.x << " " << sceneIniCoord.y << std::endl;
                // std::cout << lastScene->getSceneCoord().x << " " << lastScene->getSceneCoord().y << std::endl;

                currentScene->setPlayer(lastScene->getPlayer());
                _currentScene->init(sceneIniCoord);
                

                // Transition animation:
                sf::View view = *lastScene->getPtrView();
                sf::Vector2f lastViewCenter = view.getCenter();
                //std::cout << view->getCenter().x << " " << view->getCenter().y << std::endl;

                sf::Clock clock;
                sf::Time deltaTime;
                float count=0.f, timer = 1.5f;
                // speed
                sf::Vector2f speed(offset.x/timer,offset.y/timer);
                // zoom
                //float maxzoom = 1.01, originalZoom = 1, speedZoom = (maxzoom - originalZoom)/(timer*2); // cambiar el speed

                //std::cout << "speed: " << speed.x << " " << speed.y << std::endl;

                Player* player = currentScene->getPlayer();

                while (count < timer) {
                    deltaTime = clock.restart();
                    count += deltaTime.asSeconds();
                    view.move(speed*deltaTime.asSeconds());

                    // Moving the player.
                    if ((_currentScene->getType() == sceneTypes::outside && count > timer*(3.5f/4.f)) ||
                        (_currentScene->getType() != sceneTypes::outside && count > timer*(0.8f/4.f))) {
                        player->move(dir);
                        player->update(deltaTime.asSeconds());
                    }

                    // if (count < timer/2.f) view->zoom(1-speedZoom);
                    // else view->zoom(1.f/(1-speedZoom));

                    _window.setView(view);
                    _window.clear();
                    _lastScene->render();
                    _currentScene->render();
                    _window.setView(_window.getDefaultView());
                    _window.display();

                }
                
                _currentScene->getPtrView()->setCenter(lastViewCenter+offset); // Put the center of the camera in his position (like move(speed*(timer-count)))

                //_currentScene->_view = *view;
                player->save();
                DataManager::setString("playerScene",sceneName);
                DataManager::save();
                return;
            }
        }
        else if ((_lastScene->getType() == sceneTypes::outside && sceneTypes::dungeon == _currentScene->getType()) ||
                 (_currentScene->getType() == sceneTypes::outside && sceneTypes::dungeon == _lastScene->getType())) {

            ScenePlayable* lastScene = dynamic_cast<ScenePlayable*>(_lastScene);
            ScenePlayable* currentScene = dynamic_cast<ScenePlayable*>(_currentScene);



            sf::RenderTexture rt1,rt2;
            rt1.create(WINDOWRATIOX,WINDOWRATIOY);
            rt1.clear(sf::Color::White);
            rt2.create(WINDOWRATIOX,WINDOWRATIOY);

            sf::Vector2i ppos = _window.mapCoordsToPixel(lastScene->getPlayer()->getPositionTransition(),*lastScene->getPtrView());
            sf::Vector2f playerPos1(ppos.x,_window.getSize().y - ppos.y); // Fragment Y = 0 is on bottom

            sf::View auxView = *lastScene->getPtrView();
            auxView.setViewport(sf::FloatRect(0,0,1,1)); // Change the viewport to avoid cuttin the scene
            rt1.setView(auxView); // I need the view to draw in the renderTexture correctly
            lastScene->render(&rt1);
            // All of this is not needed with the second RenderTexture because his sceneIniCoord will be (0,0)

            currentScene->setPlayer(lastScene->getPlayer());
            currentScene->getPlayer()->setPosition(sf::Vector2f(sC->_nextScenePos.x*TILESIZE, sC->_nextScenePos.y*TILESIZE));
            
            _currentScene->init();
            auxView = *currentScene->getPtrView();
            auxView.setViewport(sf::FloatRect(0,0,1,1)); // Change the viewport to avoid cuttin the scene
            rt2.setView(auxView); // I need the view to draw in the renderTexture correctly
            currentScene->render(&rt2);

            ppos = _window.mapCoordsToPixel(currentScene->getPlayer()->getPositionTransition(),*currentScene->getPtrView());
            sf::Vector2f playerPos2(ppos.x,_window.getSize().y - ppos.y); // Fragment Y = 0 is on bottom

            rt1.display();
            

            rt2.display();

            sf::Sprite sprite1(rt1.getTexture()), sprite2(rt2.getTexture());

            sf::Clock clock;
            sf::Time deltaTime;
            float count=0.f, timer = 2.f;


            Resources::DtO.setParameter("texture", sf::Shader::CurrentTexture);
            Resources::DtO.setParameter("maxTime",timer/2);
            Resources::DtO.setParameter("maxx", (_window.getSize().x+_window.getSize().y)*0.55);
            Resources::DtO.setParameter("expand", false);

            
            Resources::DtO.setParameter("pos",playerPos1);

             

            //std::cout << playerPos.x << " " << playerPos.y << std::endl;

            sf::View view = *lastScene->getPtrView();
            // view.setCenter(view.getCenter()-lastScene->getSceneCoord());
            view.setCenter(view.getSize().x/2.0f,view.getSize().y/2.0f);

            std::cout << view.getCenter().x << " " << view.getCenter().y << std::endl;

            bool changed = false;

            while (count < timer) {
                deltaTime = clock.restart();
                count += deltaTime.asSeconds();

                Resources::DtO.setParameter("time",count);
                _window.clear();
                if (count < timer/2.f) {
                    _window.setView(view);
                    _window.draw(sprite1,&Resources::DtO);
                }
                else {
                    if (!changed) {
                        changed = true;
                        Resources::DtO.setParameter("expand", true);
                        Resources::DtO.setParameter("pos",playerPos2);
                        view = *currentScene->getPtrView();
                        view.setCenter(view.getSize().x/2.0f,view.getSize().y/2.0f);
                    }
                     Resources::DtO.setParameter("time",count-(timer/2.f));
                    _window.setView(view);
                    _window.draw(sprite2,&Resources::DtO);
                }

                _window.setView(_window.getDefaultView());
                _window.display();

            }
            currentScene->getPlayer()->save();
            DataManager::setString("playerScene",sceneName);
            DataManager::save();
            return;
        }
        if (sceneName == "menu") {
            ScenePlayable* lastScene = dynamic_cast<ScenePlayable*>(_lastScene);
            if (lastScene != nullptr) delete lastScene->getPlayer();
        }



    }
    _currentScene->init();    
}


void Game::loadScenes() {
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (SCENEPATH)) != NULL) {
      while ((ent = readdir(dir)) != NULL) {
          std::string aux = ent->d_name;
          if (aux.find(SCENEEXTENSION) != std::string::npos) {
            loadScene(aux);
        }
      }
      closedir (dir);
    } else {
      perror ("Could not open directory");
      exit(EXIT_FAILURE);
    }
    _scenes.insert(std::make_pair("menu",new SceneMenu(this, &_window)));
    _scenes.insert(std::make_pair("cutScene",new SceneCutScene(this, &_window,
                                                               Resources::AnimationIntro,
                                                               Resources::AnimationIntroTimers,
                                                               Resources::AnimationIntroActions,
                                                               Resources::AnimationTexts )));

}

void Game::loadScene(std::string sceneName) {

    std::ifstream t(SCENEPATH + sceneName);
    std::string str((std::istreambuf_iterator<char>(t)),
                 std::istreambuf_iterator<char>());

    std::istringstream description(str);

    std::string sceneType;
    description >> sceneType;
    Scene* aux;

    std::cout << sceneName.substr(0,sceneName.length()-sizeof(SCENEEXTENSION)+1) << " " << sceneType <<  std::endl;

    switch(myStoi(sceneType)) {
        case sceneTypes::outside:
            aux = new ScenePlayable(this,&_window,sceneTypes::outside, sceneName, str);
            break;
        case sceneTypes::dungeon:
            aux = new DungeonScene(this,&_window,sceneTypes::dungeon, sceneName, str);
            break;
        case sceneTypes::lightedDungeon:
            aux = new LightedDungeonScene(this,&_window,sceneTypes::dungeon, sceneName, str);
            break;
    }
    
    _scenes.insert(std::make_pair(sceneName.substr(0,sceneName.length()-sizeof(SCENEEXTENSION)+1),aux));
}

void Game::initInput() {
    InputManager::bind(InputAction::menuUp, sf::Keyboard::Up);
    InputManager::bind(InputAction::menuDown, sf::Keyboard::Down);
    InputManager::bind(InputAction::menuEnter, sf::Keyboard::Return);
    InputManager::bind(InputAction::menuEnter, 0, 0);  // Xbox A
    InputManager::bind(InputAction::menuBack, sf::Keyboard::Escape);
    InputManager::bind(InputAction::menuBack, 0, 1); // Xbox B
    InputManager::bind(InputAction::menuMovement, 0, sf::Joystick::Axis::Y);

    InputManager::bind(InputAction::up, sf::Keyboard::W);
    InputManager::bind(InputAction::down, sf::Keyboard::S);
    InputManager::bind(InputAction::left, sf::Keyboard::A);
    InputManager::bind(InputAction::right, sf::Keyboard::D);
    InputManager::bind(InputAction::pause, sf::Keyboard::Escape);
    InputManager::bind(InputAction::action, sf::Keyboard::Space);
    InputManager::bind(InputAction::action, 0, 0);  // Xbox A
    InputManager::bind(InputAction::p1movementX, 0, sf::Joystick::Axis::X);
    InputManager::bind(InputAction::p2movementX, 1, sf::Joystick::Axis::X);
    InputManager::bind(InputAction::p1movementY, 0, sf::Joystick::Axis::Y);
    InputManager::bind(InputAction::p2movementY, 1, sf::Joystick::Axis::Y);
    InputManager::bind(InputAction::fairyAction, sf::Mouse::Left);
    // InputManager::bind(InputAction::fairyAction, 0, 5); // Xbox RB
    InputManager::bind(InputAction::fairyAction, 1, 0);
    InputManager::bind(InputAction::pause, 0, 7); // Xbox start

	InputManager::bind(InputAction::reset, sf::Keyboard::F5);
}
