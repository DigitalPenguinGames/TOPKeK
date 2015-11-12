#include "Resources.hpp"

// sf::Texture        Resources::....

sf::Texture            Resources::key;
sf::Texture            Resources::rupia;
sf::Texture            Resources::heart;
sf::Texture            Resources::digPen;
sf::Texture            Resources::portada;
sf::Texture            Resources::credits;
sf::Texture            Resources::tileSet;
sf::Texture            Resources::talkBox;
sf::Texture            Resources::dungeon;
sf::Texture            Resources::linkSet;
sf::Texture            Resources::gameOver;
sf::Texture            Resources::linkSetT;
sf::Texture            Resources::linkSetB;
sf::Texture            Resources::linkSetL;
sf::Texture            Resources::linkSetR;
sf::Texture            Resources::linkSetTR;
sf::Texture            Resources::linkSetTL;
sf::Texture            Resources::linkSetBR;
sf::Texture            Resources::linkSetBL;
sf::Texture            Resources::propsOver;
sf::Texture            Resources::halfHeart;
sf::Texture            Resources::emptyHeart;
sf::Texture            Resources::fairyShoot;
sf::Texture            Resources::linkTalkBox;
sf::Texture            Resources::tileSetCols;
sf::Texture            Resources::dungeonCols;
sf::Texture            Resources::overEnemies;
sf::Texture            Resources::textureTest;
sf::Texture            Resources::shinnyHeart;
sf::Texture            Resources::penguinEnemy;
sf::Texture            Resources::bulletPenguin;
sf::Texture            Resources::penguinEnemyAttack;
sf::Texture            Resources::shinnyHalfHeart;
sf::Texture            Resources::shinnyEmptyHeart;
sf::Texture            Resources::dungeonDecoration0;
sf::Texture            Resources::dungeonDecoration1;
sf::Texture            Resources::dungeonForeground0;
sf::Texture            Resources::dungeonForeground1;
sf::Texture            Resources::dungeonDoorsVertical;
sf::Texture            Resources::dungeonDoorsHorizontal;

sf::Texture            Resources::initialAnimation1;
sf::Texture            Resources::initialAnimation2;
sf::Texture            Resources::initialAnimation3;
sf::Texture            Resources::initialAnimation4;
sf::Texture            Resources::initialAnimation5;

sf::Shader             Resources::DtO;
sf::Shader             Resources::sDying;
sf::Shader             Resources::cInvert;
sf::Shader             Resources::sLighting;
sf::Shader             Resources::fairyShootShader;

sf::Font               Resources::pauseMenuFont;

std::vector<sf::Texture>        Resources::AnimationDeath;
std::vector<float>              Resources::AnimationDeathTimers;
std::vector<std::string>        Resources::AnimationDeathTexts;
std::vector<animationActions>   Resources::AnimationDeathActions;

std::vector<std::string>        Resources::AnimationTexts;
std::vector<sf::Texture>        Resources::AnimationIntro;
std::vector<float>              Resources::AnimationIntroTimers;
std::vector<animationActions>   Resources::AnimationIntroActions;

std::vector<sf::Texture>        Resources:: AnimationInit;
std::vector<std::string>        Resources:: AnimationTextsInit;
std::vector<float>              Resources:: AnimationTimersInit;
std::vector<animationActions>   Resources:: AnimationActionsInit;

std::vector<SpriteSheetDescription> Resources::descriptions;

void Resources::load() {
    //...loadFromFile();
    key.loadFromFile                    (TEXTURETPATH+std::string("key.png"));
    rupia.loadFromFile                  (TEXTURETPATH+std::string("Rupia.png"));
    talkBox.loadFromFile                (TEXTURETPATH+std::string("talkBox.png"));
    digPen.loadFromFile                 (TEXTURETPATH+std::string("digPen.png"));
    portada.loadFromFile                (TEXTURETPATH+std::string("portada.png"));
    credits.loadFromFile                (TEXTURETPATH+std::string("credits.png"));
    linkTalkBox.loadFromFile            (TEXTURETPATH+std::string("linkTalkBox.png"));
    tileSet.loadFromFile                (TEXTURETPATH+std::string("OverworldTiles.png"));
    fairyShoot.loadFromFile             (TEXTURETPATH+std::string("fairyShoot.png"));
    tileSetCols.loadFromFile            (TEXTURETPATH+std::string("OverworldTilesColision.png"));
    dungeon.loadFromFile                (TEXTURETPATH+std::string("dungeon.png"));
    dungeonCols.loadFromFile            (TEXTURETPATH+std::string("dungeonCollision.png"));
    propsOver.loadFromFile              (TEXTURETPATH+std::string("OverworldObjects.png"));
    heart.loadFromFile                  (TEXTURETPATH+std::string("heart.png"));
    linkSet.loadFromFile                (TEXTURETPATH+std::string("link.png"));
    linkSetT.loadFromFile               (TEXTURETPATH+std::string("linkTop.png"));
    linkSetB.loadFromFile               (TEXTURETPATH+std::string("linkBot.png"));
    linkSetL.loadFromFile               (TEXTURETPATH+std::string("linkLeft.png"));
    linkSetR.loadFromFile               (TEXTURETPATH+std::string("linkRight.png"));
    linkSetTR.loadFromFile              (TEXTURETPATH+std::string("linkTopRight.png"));
    linkSetTL.loadFromFile              (TEXTURETPATH+std::string("linkTopLeft.png"));
    linkSetBR.loadFromFile              (TEXTURETPATH+std::string("linkBotRight.png"));
    linkSetBL.loadFromFile              (TEXTURETPATH+std::string("linkBotLeft.png"));
    overEnemies.loadFromFile            (TEXTURETPATH+std::string("OverworldEnemies.png"));
    textureTest.loadFromFile            (TEXTURETPATH+std::string("textureTest.png"));
    shinnyHeart.loadFromFile            (TEXTURETPATH+std::string("shinnyHeart.png"));
    halfHeart.loadFromFile              (TEXTURETPATH+std::string("halfHeart.png"));
    shinnyHalfHeart.loadFromFile        (TEXTURETPATH+std::string("shinnyHalfHeart.png"));
    emptyHeart.loadFromFile             (TEXTURETPATH+std::string("emptyHeart.png"));
    shinnyEmptyHeart.loadFromFile       (TEXTURETPATH+std::string("shinnyEmptyHeart.png"));
    dungeonDoorsVertical.loadFromFile   (TEXTURETPATH+std::string("dungeonDoorsVer.png"));
    dungeonDoorsHorizontal.loadFromFile (TEXTURETPATH+std::string("dungeonDoorsHor.png"));
    dungeonDecoration0.loadFromFile     (TEXTURETPATH+std::string("DungeonExtras/dec0.png"));
    dungeonDecoration1.loadFromFile     (TEXTURETPATH+std::string("DungeonExtras/dec1.png"));
    dungeonForeground0.loadFromFile     (TEXTURETPATH+std::string("DungeonExtras/for0.png"));
    dungeonForeground1.loadFromFile     (TEXTURETPATH+std::string("DungeonExtras/for1.png"));
    penguinEnemy.loadFromFile           (TEXTURETPATH+std::string("penguinEnemy.png"));
    bulletPenguin.loadFromFile          (TEXTURETPATH+std::string("bulletPenguin.png"));
    penguinEnemyAttack.loadFromFile     (TEXTURETPATH+std::string("penguinEnemyAttack.png"));
    gameOver.loadFromFile               (TEXTURETPATH+std::string("Animations/gameOver/gameOver.png"));
    initialAnimation1.loadFromFile      (TEXTURETPATH+std::string("Animations/initial/anim1.png"));
    initialAnimation2.loadFromFile      (TEXTURETPATH+std::string("Animations/initial/anim2.png"));
    initialAnimation3.loadFromFile      (TEXTURETPATH+std::string("Animations/initial/anim3.png"));
    initialAnimation4.loadFromFile      (TEXTURETPATH+std::string("Animations/initial/anim4.png"));
    initialAnimation5.loadFromFile      (TEXTURETPATH+std::string("Animations/initial/anim5.png"));


    descriptions = std::vector<SpriteSheetDescription>(spriteDescriptionsQtt);

    descriptions[linkSpritesDescriptions]       = loadDescription("linkSheet");
    descriptions[swordDescriptions]             = loadDescription("swordSheet");
    descriptions[octorokDescriptions]           = loadDescription("Octorok");
    descriptions[rockProjDescription]           = loadDescription("rockProj");
    descriptions[propsOverDescription]          = loadDescription("propsOverworld");
    descriptions[dungeonDoorsHor]               = loadDescription("dungeonDoorsHor");
    descriptions[dungeonDoorsVer]               = loadDescription("dungeonDoorsVer");
    descriptions[objectsDescription]            = loadDescription("objects");
    descriptions[penguinEnemyDescription]       = loadDescription("penguinEnemyReg");
    descriptions[penguinEnemyDescriptionPrep]   = loadDescription("penguinEnemyPrep");
    descriptions[penguinEnemyDescriptionAttack] = loadDescription("penguinEnemyAtack");



    if (!DtO.loadFromFile               (SHADERPATH+std::string("transitionDtO.frag"), sf::Shader::Fragment)) exit(EXIT_FAILURE);
    if (!sLighting.loadFromFile         (SHADERPATH+std::string("lighting.frag"), sf::Shader::Fragment)) exit(EXIT_FAILURE);
    if (!cInvert.loadFromFile           (SHADERPATH+std::string("invert.frag"), sf::Shader::Fragment)) exit(EXIT_FAILURE);
    if (!sDying.loadFromFile           (SHADERPATH+std::string("dying.frag"), sf::Shader::Fragment)) exit(EXIT_FAILURE);
    if (!fairyShootShader.loadFromFile  (SHADERPATH+std::string("fairyShoot.frag"), sf::Shader::Fragment)) exit(EXIT_FAILURE);

    if (!pauseMenuFont.loadFromFile("Resources/Fonts/font.ttf")) exit(EXIT_FAILURE);

    AnimationIntro.push_back(Resources::initialAnimation1);
    AnimationIntroActions.push_back(scrollDown);
    AnimationIntroTimers.push_back(20);
    AnimationTexts.push_back("none");
    AnimationIntro.push_back(Resources::initialAnimation2);
    AnimationIntroTimers.push_back(1);
    AnimationIntroActions.push_back(action_none);
    AnimationTexts.push_back("anim2");
    AnimationIntro.push_back(Resources::initialAnimation3);
    AnimationIntroTimers.push_back(1);
    AnimationIntroActions.push_back(action_none);
    AnimationTexts.push_back("anim3");
    AnimationIntro.push_back(Resources::initialAnimation4);
    AnimationIntroTimers.push_back(1);
    AnimationIntroActions.push_back(action_none);
    AnimationTexts.push_back("anim4");
    AnimationIntro.push_back(Resources::initialAnimation5);
    AnimationIntroTimers.push_back(1);
    AnimationIntroActions.push_back(action_none);
    AnimationTexts.push_back("anim5");

    AnimationDeath.push_back(Resources::gameOver);
    AnimationDeathTimers.push_back(1);
    AnimationDeathActions.push_back(action_none);
    AnimationDeathTexts.push_back("none");

    AnimationInit.push_back(Resources::portada);
    AnimationTimersInit.push_back(3);
    AnimationActionsInit.push_back(action_skip);
    AnimationTextsInit.push_back("none");
    AnimationInit.push_back(Resources::digPen);
    AnimationTimersInit.push_back(3);
    AnimationActionsInit.push_back(action_skip);
    AnimationTextsInit.push_back("none");
    AnimationInit.push_back(Resources::credits);
    AnimationTimersInit.push_back(3);
    AnimationActionsInit.push_back(action_skip);
    AnimationTextsInit.push_back("none");

}



SpriteSheetDescription Resources::loadDescription(std::string fileName) {
    std::string filePath = TEXTURETPATH + fileName + TEXTUREDESCRIPTIONEXTENSION;
    SpriteSheetDescription ret;
    // leer el fichero
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cout << "Error opening file on resources loadDescription " << filePath << std::endl;
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
        }
        else {
            descriptorPosition = positions[key];
        }
        //std::cout << "insertando la key " << key << " en la posicion " << descriptorPosition << std::endl;

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
