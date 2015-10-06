#ifndef LAYOUT_HPP
#define LAYOUT_HPP

#include <stdexcept>
#include "Widget.hpp"

class Layout : protected Widget{

public:
    Layout(Widget* parent=nullptr);
    virtual ~Layout();
    void setSpace(float pixels);

protected:
    friend class Container;
    float _space;
};

#endif // LAYOUT_HPP
