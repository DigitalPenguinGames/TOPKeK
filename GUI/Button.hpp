#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <iostream>
#include <functional>
#include "Widget.hpp"

class Button : public Widget {

    public:
        using FuncType = std::function<void(const sf::Event& event,Button& self)>;

        FuncType onClick;
        static FuncType defaultFunc;

        virtual ~Button();
        Button(Widget* parent=nullptr);


    protected:

        virtual bool processEvent(const sf::Event& event,
                                  const sf::Vector2f& parent_pos)override;
        virtual void onMouseEntered();
        virtual void onMouseLeft();

    private:

        enum Status {None = 0,Hover = 1};
        int _status;
};

#endif // BUTTON_HPP
