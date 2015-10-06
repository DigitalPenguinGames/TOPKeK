#ifndef FRAME_HPP
#define FRAME_HPP

#include "Widget.hpp"
#include "Button.hpp"
#include "Container.hpp"

class Frame : public Container {

public:

    using FuncType = std::function<void(const sf::Event& event,Button& self)>;

    Frame(sf::RenderWindow& window);
    virtual ~Frame();
    void processEvents();

    bool processEvent(const sf::Event& event);
    void draw();
    virtual sf::Vector2f getSize()const override;

private:

    sf::RenderWindow& _window;

    virtual bool processEvent(const sf::Event& event,
                              const sf::Vector2f& parent_pos)override;

    virtual void processEvents(const sf::Vector2f& parent_pos)override;

};

#endif // FRAME_HPP
