#include "common.hpp"


sf::Texture backgroundImageTexture;
sf::Font globalFont;

string states[7] = {"title", "levelSelector", "lvl1", "lvl2", "lvl3", "tutorial", "settings"};

bool loadFont(){

    if(!globalFont.openFromFile("assets/fonts/Jaro-Regular.ttf")){
        cerr << "Error: could not load global font jaro-regular from file" << endl;
        return false;
    }

    return true;
}


bool loadAssets(){

    if (!loadFont()) return false;

    return true;

}