#include "common.hpp"


sf::Texture backgroundImageTexture;
sf::Font globalFont;
sf::Music bombSound, music, popSound;
sf::Texture textureArray[9];

// represent the states of game
string states[7] = {"title", "levelSelector", "lvl1", "lvl2", "lvl3", "tutorial", "settings"};

//loads the font used within the game.
bool loadFont(){

    if(!globalFont.openFromFile("assets/fonts/Jaro-Regular.ttf")){
        cerr << "Error: could not load global font jaro-regular from file" << endl;
        return false;
    }

    return true;
}

//loads all sound that is used within the game
bool loadSound(){


    
    if(!music.openFromFile("assets/sound/CandyCrushMusic.mp3") || !bombSound.openFromFile("assets/sound/boom.mp3") || !popSound.openFromFile("assets/sound/pop.mp3")){
        cout << "COuld not open audio file" << endl;
        return false;


    }else {
        music.play();
        music.setLooping(true);
        bombSound.setVolume(25.f);
        music.setVolume(20.f);
        music.play();
    }   
    cout << "sound loaded";
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


    for(int i= 0; i < 9;i++){

        textureArray[i].setSmooth(true);

    }


    return valid;

} 

// loads all assets and returns false if any of the loading functions within it fail.
bool loadAssets(){

    if (!loadFont()) return false;
    if(!initTextures()) return false;
    if (!loadSound()) return false;
    return true;

}

// initializes the seed to be used for random num generation.
void initRandom(){

    srand(time(nullptr));

}