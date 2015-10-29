#include "TextBox.hpp"
#include "Resources.hpp"

TextBox::TextBox(){

    lecturePointer = 0;

    clicked = false;
    is_clicked = false;
    textFinished = false;

    setPosition(0,0);
    text.setString("");

}

std::string TextBox::getFractionText(std::string text, int ini, int end){
    //std::cout << "text : " << text << std::endl;
    //std::cout << "ini " << ini <<  "  end " << end << std::endl;
    std::string ret = "";
    for(int i = ini; i < end; ++i){
        if(i >= int(text.size())) {
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
    
}

void TextBox::setTextBestFit(std::string s = "Click", float charSize = 100){

    totalText = s;
    lecturePointer = 0;
    textFinished = false;
    text.setCharacterSize(charSize);

    sf::FloatRect totalSpace;
    totalSpace = sprite.getGlobalBounds();

    sf::Vector2f spaces( totalSpace.width/16, totalSpace.height/8);

    sf::IntRect box(totalSpace.left+spaces.x, totalSpace.top+spaces.y,
                    totalSpace.width-spaces.x, totalSpace.height-spaces.y);

    sf::Vector2f writted(box.left,box.top);

    sf::Text aux;
    aux.setCharacterSize(charSize);
    aux.setFont(Resources::pauseMenuFont);
    boxTexts = std::vector<std::string>();
    while(writted.y+charSize < box.top+box.height){

        float maxYsize = 0;
        boxTexts.push_back("");
        while(writted.x+charSize < box.left+box.width){

            int row = writted.y-box.top;
            boxTexts[row] += (totalText[lecturePointer]);

            aux.setString(totalText[lecturePointer]);
                std::cout << aux.getString().toAnsiString() << aux.getGlobalBounds().width << " , " << aux.getGlobalBounds().height << std::endl;
            ++lecturePointer;
            writted.x += aux.getGlobalBounds().width;
            if(aux.getGlobalBounds().height > maxYsize) maxYsize = aux.getGlobalBounds().height;
        }

        aux.setString(boxTexts[writted.y-box.top]);
        //std::cout << aux.getGlobalBounds().width << " , " << aux.getGlobalBounds().height << std::endl;
        writted.y += maxYsize;

    }


}


void TextBox::setText(std::string s = "Click",int qttyWritte, int qttyWhitesEnd, int qttyWhitesFirst){
    std::cout << "set Text : " << s << std::endl;
    totalText = s;

    text.setString("Penguins");

    /*textFinished = false;

    int qttyRows = qttyWhitesFirst + qttyWritte + qttyWhitesEnd;
    sf::Vector2f sizeRow( getSize().x , getSize().y/(qttyRows) );
    //std::cout << "size ROw = " << sizeRow.x << " ; " << sizeRow.y << std::endl;

    int actualRow = 0;
    lecturePointer = 0;
    boxTexts = std::vector < std::string > (qttyRows, " ");

    for(int i = 0; i < qttyWhitesFirst; ++i){
        boxTexts[actualRow] = " ";  ++actualRow;
    }
    //float fraseLength = 2*sizeRow.x/sizeRow.y-2; //-2 is so i can add 2 spaces on beggining and end
    float fraseLength = sizeRow.x/sizeRow.y -2;
    for(int i = 0; i < qttyWritte; ++i){
        boxTexts[actualRow] =  "  "+getFractionText(totalText, lecturePointer, lecturePointer + fraseLength);
        lecturePointer += fraseLength;

        std::cout << boxTexts[actualRow] << std::endl;
        for(int j = boxTexts[actualRow].size()-1; boxTexts[actualRow][j] != ' '; --j){
            boxTexts[actualRow].pop_back();
            --lecturePointer;
        }
        std::cout << "nd " << boxTexts[actualRow] << std::endl;
        boxTexts[actualRow] += " ";
        ++actualRow;
    }
    for(int i = 0; i < qttyWhitesEnd; ++i){
        boxTexts[actualRow] = " ";   ++actualRow;
    }
*/
}

std::string TextBox::getText(){ return text.getString();}

void TextBox::draw(sf::RenderTarget& w){

    w.draw(sprite);

    for(int i = 0; i < int(boxTexts.size()); ++i){
        sf::Vector2f sizeT(
            sprite.getGlobalBounds().width ,
            sprite.getGlobalBounds().height/boxTexts.size()
        );

        text.setString(boxTexts[i]);
 
        sizeT.y = sprite.getGlobalBounds().height/4;

        sf::FloatRect totalSpace;
        totalSpace = sprite.getGlobalBounds();
        sf::Vector2f spaces( totalSpace.width/16, totalSpace.height/8);
        text.setPosition(sprite.getPosition().x+spaces.x/2, sprite.getPosition().y+(i+1)*spaces.y/2 );

        sf::Vector2f textSize(text.getGlobalBounds().width, text.getGlobalBounds().height);
        float oldSize = text.getCharacterSize();
        text.setCharacterSize(50);
        text.setScale(textSize.x/text.getGlobalBounds().width, textSize.y/text.getGlobalBounds().height);
        w.draw(text);
        text.setCharacterSize(oldSize);

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
    texture = tex;
    sprite.setTexture(texture, true);
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
            
            sf::FloatRect totalSpace;
            totalSpace = sprite.getGlobalBounds();

            sf::Vector2f spaces( totalSpace.width/16, totalSpace.height/8);

            sf::IntRect box(totalSpace.left+spaces.x, totalSpace.top+spaces.y,
                            totalSpace.width-spaces.x, totalSpace.height-spaces.y);

            sf::Vector2f writted(box.left,box.top);

            sf::Text aux;
            float charSize = text.getCharacterSize();
            aux.setCharacterSize(charSize);
            aux.setFont(Resources::pauseMenuFont);
            boxTexts = std::vector<std::string>();
            while(writted.y+charSize < box.top+box.height){

                float maxYsize = 0;
                boxTexts.push_back("");
                while(writted.x+charSize < box.left+box.width){

                    int row = writted.y-box.top;
                    boxTexts[row] += (totalText[lecturePointer]);

                    aux.setString(totalText[lecturePointer]);
                        std::cout <<"-------"<< aux.getString().toAnsiString() << aux.getGlobalBounds().width << " , " << aux.getGlobalBounds().height << std::endl;
                    ++lecturePointer;
                    writted.x += aux.getGlobalBounds().width;
                    if(aux.getGlobalBounds().height > maxYsize) maxYsize = aux.getGlobalBounds().height;
                }

                aux.setString(boxTexts[writted.y-box.top]);
                std::cout << aux.getGlobalBounds().width << " , " << aux.getGlobalBounds().height << std::endl;
                writted.y += maxYsize;

            }
        }
    }
    sprite.move(delayx, delayy);
}


void TextBox::setTextColor(sf::Color c){text.setColor(c); }
sf::Color TextBox::getTextColor(){ return text.getColor();}

void TextBox::setCharacterSize(int u){ text.setCharacterSize(u); }
int TextBox::getCharacterSize(){ return text.getCharacterSize(); }

void TextBox::setFont(sf::Font f){ font = f; text.setFont(font); }

sf::Vector2f TextBox::getPosition(){ return sprite.getPosition(); }
void TextBox::setPosition(float x, float y){ setPosition(sf::Vector2f(x, y)); }
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
    setText(getText());
}
