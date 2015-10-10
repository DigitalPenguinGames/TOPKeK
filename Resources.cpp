#include "Resources.hpp"

// sf::Texture        Resources::....
sf::Texture            Resources::tileSet;
sf::Texture            Resources::linkSet;
sf::Texture            Resources::linkSetT;
sf::Texture            Resources::linkSetB;
sf::Texture            Resources::linkSetL;
sf::Texture            Resources::linkSetR;
sf::Texture            Resources::linkSetTR;
sf::Texture            Resources::linkSetTL;
sf::Texture            Resources::linkSetBR;
sf::Texture            Resources::linkSetBL;
sf::Texture            Resources::textureTest;
sf::Texture            Resources::dungeon;
sf::Shader             Resources::DtO;
sf::Shader             Resources::sLighting;
sf::Font               Resources::pauseMenuFont;

std::vector<SpriteSheetDescription> Resources::descriptions;

void Resources::load() {
    //...loadFromFile();
    tileSet.loadFromFile(TEXTURETPATH+std::string("OverworldTiles.png"));
    linkSet.loadFromFile(TEXTURETPATH+std::string("link.png"));
    linkSetT.loadFromFile(TEXTURETPATH+std::string("linkTop.png"));
    linkSetB.loadFromFile(TEXTURETPATH+std::string("linkBot.png"));
    linkSetL.loadFromFile(TEXTURETPATH+std::string("linkLeft.png"));
    linkSetR.loadFromFile(TEXTURETPATH+std::string("linkRight.png"));
    linkSetTR.loadFromFile(TEXTURETPATH+std::string("linkTopRight.png"));
    linkSetTL.loadFromFile(TEXTURETPATH+std::string("linkTopLeft.png"));
    linkSetBR.loadFromFile(TEXTURETPATH+std::string("linkBotRight.png"));
    linkSetBL.loadFromFile(TEXTURETPATH+std::string("linkBotLeft.png"));
    textureTest.loadFromFile(TEXTURETPATH+std::string("textureTest.png"));
    dungeon.loadFromFile(TEXTURETPATH+std::string("dungeon.png"));

    descriptions = std::vector<SpriteSheetDescription>(spriteDescriptionsQtt);
    descriptions[linkSpritesDescriptions] = loadDescription("linkSheet");
    descriptions[swordDescriptions] = loadDescription("swordSheet");

    if (!DtO.loadFromFile(SHADERPATH+std::string("transitionDtO.frag"), sf::Shader::Fragment)) exit(EXIT_FAILURE);
    //if (!sLighting.loadFromFile(SHADERPATH+std::string("lighting.frag"), sf::Shader::Fragment)) exit(EXIT_FAILURE);

    if (!pauseMenuFont.loadFromFile("Resources/Fonts/font.otf")) exit(EXIT_FAILURE);

}



SpriteSheetDescription Resources::loadDescription(std::string fileName) {
    std::string filePath = TEXTURETPATH + fileName + TEXTUREDESCRIPTIONEXTENSION;
    SpriteSheetDescription ret;
    // leer el fichero
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cout << "Error trying to open " << filePath << std::endl;
        exit(EXIT_FAILURE);
    }
    std::vector<std::pair<int, std::string> > v;
    int lineNum = 0;
    std::string line;
    while (getline(file,line)) {
        ++lineNum;
        for (int i = 0; i < int(line.size()-1); ++i) {
            if (line[i] == '/' && line[i+1] == '/') {
                line = line.substr(0,i);
                break;
            }
        }
        std::istringstream aux(line);
        std::string s;
        while(aux >> s) 
            v.push_back(std::make_pair(lineNum,s));
    }
    SpriteSheetDescription ssd;
    std::map<std::string, int> positions;
    for (int  i = 0; i < int(v.size()); ++i) {
        lineNum = v[i].first;
        std::string key = v[i].second;
        int descriptorPosition;
        if (positions.find(key) == positions.end()) {
            descriptorPosition = positions.size();
            positions.insert(std::make_pair(key,descriptorPosition));
            ssd.push_back(std::vector<sf::IntRect>());
            std::cout << "insertando la key " << key << " en la posicion " << descriptorPosition << std::endl;
        }
        else {
            descriptorPosition = positions[key];
            std::cout << "la key " << key << " ya existia" << std::endl;
        }

        if (i+4 >= int(v.size()) || 
            !isInt(v[i+1].second) || 
            !isInt(v[i+2].second) || 
            !isInt(v[i+3].second) || 
            !isInt(v[i+4].second)) {
            std::cout << "Error in line " << lineNum << ": four integers are needed" << std::endl;
            exit(EXIT_FAILURE);
        }
        sf::IntRect intRect(myStoi(v[i+1].second),
            myStoi(v[i+2].second),
            myStoi(v[i+3].second),
            myStoi(v[i+4].second));
        ssd[descriptorPosition].push_back(intRect);
        i += 4;
    }

    return ssd;
}
