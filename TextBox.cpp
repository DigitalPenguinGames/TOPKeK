#include "TextBox.hpp"

TextBox::TextBox(){
    text.setString("");
    clicked = false;
    is_clicked = false;
    textFinished = false;
    setPosition(0,0);
}

std::string TextBox::getFractionText(std::string text, int ini, int end){
    std::string ret = "";
    for(int i = ini; i < end; ++i){
        if(i >= text.size()) {
            textFinished = true;
            ret += " ";
        }
        else ret += text[i];
    }
    return ret;
}

bool TextBox::getTextFinished(){return textFinished;}

TextBox::TextBox(std::string myText, std::string texturePath, std::string fontPath, float sizeX, float sizeY): boxTexts(4, ""){

    totalText = myText;

    text.setString("Penguins");

    clicked = false;
    is_clicked = false;
    textFinished = false;

    if(!texture.loadFromFile(texturePath)) std::cerr << "Failed on load texture from " << texturePath << std::endl;
    else sprite.setTexture(texture);
    setSize(sizeX, sizeY);

    if(!font.loadFromFile(fontPath)){ std::cerr << "Can't find the font file" << std::endl; }
    else setFont(font);  
    setTextColor(sf::Color::Black);
    text.setCharacterSize(100);

    int qttyRows = 4;
    sf::Vector2f sizeRow( sizeX, int(sizeY/qttyRows) ); 
    
    lecturePointer = 0;
    boxTexts[0] = " ";
    float fraseLength = 2* sizeRow.x/sizeRow.y ; //trec dos per poder posar espais

    for(int i = 1; i < qttyRows-1; ++i){
        boxTexts[i] =  " "+getFractionText(totalText, lecturePointer, lecturePointer + fraseLength);
        lecturePointer += fraseLength;
        
        for(int j = boxTexts[i].size()-1; boxTexts[i][j] != ' '; --j){
            boxTexts[i].pop_back();
            --lecturePointer;
        }
            
        boxTexts[i] += " ";
    }
    
    boxTexts[qttyRows-1] = " ";

    setPosition(0,0);
    
}



void TextBox::setText(std::string s = "Click"){

    totalText = s;

    text.setString("Penguins");

    textFinished = false;

    int qttyRows = 4;
    sf::Vector2f sizeRow( getSize().x/ 5, getSize().y/(qttyRows+2) );
    std::cout << "size ROw = " << sizeRow.x << " ; " << sizeRow.y << std::endl;

    lecturePointer = 0;
    boxTexts = std::vector < std::string > (qttyRows, " ");
    boxTexts[0] = " ";
    float fraseLength = 2* sizeRow.x/sizeRow.y ; //trec dos per poder posar espais

    for(int i = 1; i < qttyRows-1; ++i){
        boxTexts[i] =  " "+getFractionText(totalText, lecturePointer, lecturePointer + fraseLength);
        lecturePointer += fraseLength;

        for(int j = boxTexts[i].size()-1; boxTexts[i][j] != ' '; --j){
            boxTexts[i].pop_back();
            --lecturePointer;
        }

        boxTexts[i] += " ";
    }

    boxTexts[qttyRows-1] = " ";


}

std::string TextBox::getText(){ return text.getString();}

void TextBox::draw(sf::RenderTarget& w){

    w.draw(sprite);

    for(int i = 0; i < 4; ++i){
    sf::Vector2f sizeT(
        sprite.getGlobalBounds().width ,
        sprite.getGlobalBounds().height/6
    );    
        text.setScale(1,1);

        text.setString(boxTexts[i]);

        sf::Vector2f scaleRow(1,1);

        if((!text.getGlobalBounds().width < sprite.getGlobalBounds().width || boxTexts[i] != " ")){

            scaleRow = sf::Vector2f(
            sizeT.x/text.getGlobalBounds().width, 
            sizeT.y/text.getGlobalBounds().height );

        }else{

            scaleRow = sf::Vector2f(
            1, 
            sizeT.y/text.getGlobalBounds().height );

        }

        text.setScale(scaleRow);
 
        sizeT.y = sprite.getGlobalBounds().height/4;

        text.setPosition(sprite.getPosition().x, sprite.getPosition().y+i*sizeT.y );        

        w.draw(text);

    }

}

void TextBox::setOrigin(sf::Vector2f origin){
    sprite.setOrigin(origin);
}

void TextBox::setTexture(std::string name){
    float sizeX = getSize().x;
    float sizeY = getSize().y;
    if(!texture.loadFromFile(name)) std::cerr << " texture not loaded on setTexture" << std::endl;
    else sprite.setTexture(texture, true);
    setSize(sizeX, sizeY);
}
void TextBox::setTexture(sf::Texture tex){
    //float sizeX = getSize().x;
    //float sizeY = getSize().y;
    texture = tex;
    sprite.setTexture(texture, true);
    //setSize(sizeX, sizeY);
}

//TODO change it so with a key it can be skiped and not with mouse and so.
void TextBox::handleEvent(sf::Event e){
    
    float delayx, delayy;
    delayx = sprite.getOrigin().x*sprite.getScale().x;
    delayy = sprite.getOrigin().y*sprite.getScale().y;
    sprite.move(-delayx, -delayy);
    if(e.type == sf::Event::MouseButtonPressed){
      /*  if (e.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f click(e.mouseButton.x, e.mouseButton.y);
            if(click.x > sprite.getPosition().x && click.x < sprite.getPosition().x+sprite.getGlobalBounds().width){
                if(click.y > sprite.getPosition().y && click.y < sprite.getPosition().y+sprite.getGlobalBounds().height){
                    clicked = true;
                    is_clicked = true;
                    clock.restart();
//                     if(clickEffect && sprite.getTexture() == &texture) sprite.setTexture(pressed_texture);
                }
            }
        }*/

    }
    if(e.type == sf::Event::MouseButtonReleased){
        if (e.mouseButton.button == sf::Mouse::Left) {
            is_clicked = false;
//             if(clickEffect && sprite.getTexture() != &texture) sprite.setTexture(texture);
        }
    }
    if(e.type == sf::Event::KeyPressed) {
        if(e.key.code == sf::Keyboard::F) {
            clicked = true;
            is_clicked = true;
        }
    }
    if(e.type == sf::Event::KeyReleased) {
        if(e.key.code == sf::Keyboard::F) {
            is_clicked = false;
            
            sf::Vector2f sizeRow( sprite.getGlobalBounds().width, int(sprite.getGlobalBounds().height/4) ); 
            boxTexts[0] = " ";
            float fraseLength = 2* sizeRow.x/sizeRow.y;
    
            for(int i = 1; i < 3; ++i){
                boxTexts[i] =  " " + getFractionText(totalText, lecturePointer, lecturePointer + fraseLength);
                lecturePointer += fraseLength;
            
                for(int j = boxTexts[i].size()-1; boxTexts[i][j] != ' '; --j){
                    boxTexts[i].pop_back();
                    --lecturePointer;
                }
                boxTexts[i] += " " ;
            }
   
            boxTexts[3] = " ";
        }
    }
    sprite.move(delayx, delayy);
}


void TextBox::setTextColor(sf::Color c){text.setColor(c); }
sf::Color TextBox::getTextColor(){ return text.getColor(); }
void TextBox::setCharacterSize(int ){ /*text.setCharacterSize(u);*/ }
int TextBox::getCharacterSize(){ return text.getCharacterSize(); }
void TextBox::setFont(sf::Font f){ font = f; text.setFont(font); }

void TextBox::setPosition(float x, float y){ setPosition(sf::Vector2f(x, y)); }
sf::Vector2f TextBox::getPosition(){ return sprite.getPosition(); }
void TextBox::setPosition(sf::Vector2f position){
    sprite.setPosition(position);
    text.setPosition(position.x - (sprite.getGlobalBounds().width * (sprite.getOrigin().x/sprite.getLocalBounds().width) ) +
                     sprite.getGlobalBounds().width/2 -
                     text.getGlobalBounds().width/2,
        position.y - (sprite.getGlobalBounds().height * (sprite.getOrigin().y/sprite.getLocalBounds().height) ) + sprite.getGlobalBounds().height/2 - (text.getGlobalBounds().height/2));
}


sf::Vector2f TextBox::getSize(){ return sf::Vector2f(sprite.getGlobalBounds().width,sprite.getGlobalBounds().height); }


float TextBox::timeSinceLastClick(){ return clock.getElapsedTime().asSeconds(); }
bool TextBox::isClicked(){ return is_clicked; }
bool TextBox::hasBeenClicked(){
    bool r = clicked;
    if(clicked) clicked = false;
    return r;
}

void TextBox::setSize(float x, float y){ setSize(sf::Vector2f(x,y)); }
void TextBox::setSize(sf::Vector2f size){
    sprite.setScale(size.x/sprite.getLocalBounds().width, size.y/sprite.getLocalBounds().height);
//     this->setText(text.getString());
    float actualCharSize, desiredCharSize;
    float actualTextSize, desiredTextSize;
    actualCharSize = text.getCharacterSize();
    actualTextSize = text.getLocalBounds().width+2;
    desiredTextSize = sprite.getLocalBounds().width;
    desiredCharSize = actualCharSize*desiredTextSize/actualTextSize;
    if(desiredCharSize < 50) desiredCharSize = 50;
    text.setCharacterSize(desiredCharSize);
}
