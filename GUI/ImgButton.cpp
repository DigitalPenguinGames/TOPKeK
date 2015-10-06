#include "ImgButton.hpp"

ImgButton::ImgButton(const sf::Texture & pressedTexture, sf::Texture & releasedTexture, Widget *parent)
    :Button(parent){

    _pressedTexture = pressedTexture;
    _releassedTexture = releasedTexture;

    _sprite.setTexture(_releassedTexture);

}

ImgButton::~ImgButton(){}

void ImgButton::setSize(sf::Vector2f size) {
    _shape.setSize(size);
    updateShape();
}
void ImgButton::setSize(float width, float height){
    setSize(sf::Vector2f(width,height));
}

void ImgButton::setPressedTexture(sf::Texture &pressedTexture){
    _pressedTexture = pressedTexture;
    updateShape();
}

void ImgButton::setReleassedTexture(sf::Texture &releassedTexture){
    _releassedTexture = releassedTexture;
    updateShape();
}

sf::Vector2f ImgButton::getSize() const{
    sf::FloatRect rect = _shape.getGlobalBounds();
    return sf::Vector2f(rect.width, rect.height);
}

void ImgButton::updateShape(){
    /*sf::Vector2f label_size = _label.getSize();
    unsigned int char_size = _label.getCharacterSize();
    _shape.setSize(sf::Vector2f(char_size*2+label_size.x, char_size*2+label_size.y));
    _label.setPosition(char_size,char_size);
*/
    _sprite.setScale(_shape.getSize().x/_sprite.getLocalBounds().width, _shape.getSize().y/_sprite.getLocalBounds().height );
    Widget::updateShape();
}

void ImgButton::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform.translate(_position);
    target.draw(_shape, states);
    target.draw(_sprite, states);
    //target.draw(_label,states);
}

void ImgButton::onMouseEntered() {
    _sprite.setTexture(_pressedTexture, false);
    updateShape();
}

void ImgButton::onMouseLeft() {
    _sprite.setTexture(_releassedTexture, false);
    updateShape();
}
