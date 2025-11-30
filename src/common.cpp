#include "common.hpp"


sf::Texture backgroundImageTexture;
sf::Font globalFont;

sf::Texture textureArray[9];

string states[7] = {"title", "levelSelector", "lvl1", "lvl2", "lvl3", "tutorial", "settings"};

bool loadFont(){

    if(!globalFont.openFromFile("assets/fonts/Jaro-Regular.ttf")){
        cerr << "Error: could not load global font jaro-regular from file" << endl;
        return false;
    }

    return true;
}

bool initTextures(){

    int valid = true;

    if (!textureArray[0].loadFromFile("assets/images/Red1.png")) valid =  false;
    if(!textureArray[1].loadFromFile("assets/images/Blue2.png")) valid =  false;
    if(!textureArray[2].loadFromFile("assets/images/Green3.png")) valid = false;
    if(!textureArray[3].loadFromFile("assets/images/Orange4.png")) valid = false;
    if(!textureArray[4].loadFromFile("assets/images/Purple5.png")) valid = false;
    if(!textureArray[5].loadFromFile("assets/images/Yellow6.png")) valid = false;
    if(!textureArray[6].loadFromFile("assets/images/SpecialCandy4.png")) valid = false;
    if(!textureArray[7].loadFromFile("assets/images/SpecialCandy5.png")) valid = false;
    if(!textureArray[8].loadFromFile("assets/images/empty.jpg")) valid = false;

    return valid;

} 

bool loadAssets(){

    if (!loadFont()) return false;
    if(!initTextures()) return false;
    return true;

}

void initRandom(){

    srand(time(nullptr));

}