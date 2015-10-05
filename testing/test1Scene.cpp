#include "test1Scene.hpp"

test1Scene::test1Scene(Game* g, sf::RenderTarget* w) : Scene(w), game(g) {
    rectangle.setSize(sf::Vector2f(float(w->getSize().x-100),float(w->getSize().y-100)));
    rectangle.setPosition(50,50);
    rectangle.setFillColor(sf::Color::Yellow);
    rectangle.setOutlineColor(sf::Color::Red);
    rectangle.setOutlineThickness(50);

    sprite.setTexture(Resources::textureTest);
    sprite.setScale(
        sf::Vector2f(
            WINDOWRATIOX/float(sprite.getGlobalBounds().width),
            WINDOWRATIOY/float(sprite.getGlobalBounds().height)));
}

test1Scene::~test1Scene() {

}

void test1Scene::processInput() {
    sf::Event event;
    while (_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {_window->close(); exit(0);}
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            _window->close(); exit(0);
        }

        //else if (event.type == sf::Event::Resized) initView();
    }
}

void test1Scene::update(float deltaTime) {
    (void)deltaTime;
}

void test1Scene::render() {
    _window->draw(sprite);
    _window->draw(rectangle);
}