#include "StatsBar.hpp"

StatsBar::StatsBar(int maxHP, sf::Texture heart, sf::Texture halfHeart, sf::Texture emptyHeart){

    _space = 0;
    size.x = maxHP;
    size.y = maxHP;

    _maxHP = maxHP;
    _actualHP = maxHP;

    _heart = new ImgButton(heart, heart, this);
    _halfHeart = new ImgButton(halfHeart, halfHeart, this);;
    _emptyHeart = new ImgButton(emptyHeart, emptyHeart, this);;
}


StatsBar::~StatsBar(){
    delete _heart;
    delete _halfHeart;
    delete _emptyHeart;
}

void StatsBar::updateShape(){

    sf::Vector2f butSize((size.x)/_maxHP, size.y);
    _heart->setSize(butSize);
    _halfHeart->setSize(butSize);
    _emptyHeart->setSize(butSize);

    _widgets.empty();
    for(int i  = 0; i < _maxHP; ++i ){
        if(i < _actualHP){
            _widgets.emplace_back(_heart);
        }
        else {
            if( _actualHP > i && _actualHP < i+1){
                _widgets.emplace_back(_halfHeart);
            }
            else {
                _widgets.emplace_back(_emptyHeart);
            }
        }
    }

    float max_y = (_parent?_parent->getSize().y:0);
    for(Widget* widget : _widgets) {
        sf::Vector2f size = widget->getSize();
        float widget_y = size.y;
        if(widget_y > max_y)
        max_y = widget_y;
    }

    float pos_x = _space;
    if(_parent)
        pos_x = (_parent->getSize().x - getSize().x)/2.f;

    for(Widget* widget : _widgets) {
        sf::Vector2f size = widget->getSize();
        widget->setPosition(pos_x,(max_y-size.y)/2.0);
        pos_x += size.x + _space;
    }

    Widget::updateShape();
}

void StatsBar::setMaxHP(int value){
    _maxHP = value;
    updateShape();
}

void StatsBar::setActualHP(float value){
    _actualHP = value;
    updateShape();
}
sf::Vector2f StatsBar::getSize() const{
    return size;
}

void StatsBar::setSize(const sf::Vector2f &value){
    size = value;
    updateShape();
}

