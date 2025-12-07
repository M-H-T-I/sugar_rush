#include "Settings.hpp"


sf::Text muteBtn(globalFont);
sf::Text backBtnSettings(globalFont);
sf::Text deleteSaveBtn(globalFont);

void drawSettingsScreen(sf::RenderWindow& window){


    float margin = 30.f, prev = margin;


    sf::Text settingsTitle(globalFont);
    // title of the page
    settingsTitle.setString("Settings");
    settingsTitle.setCharacterSize(60);
    settingsTitle.setFillColor(sf::Color(191, 78, 48));

    // centering the title text
    auto center = settingsTitle.getLocalBounds().size / 2.f;
    settingsTitle.setOrigin(center);
    settingsTitle.setPosition(sf::Vector2f{(window.getSize().x / 2.f), (center.y)});

    prev += settingsTitle.getLocalBounds().size.y + margin;



    // backbtn
    backBtnSettings.setString("[ Go Back ]");
    backBtnSettings.setCharacterSize(25);
    backBtnSettings.setFillColor(sf::Color::White);

    center = backBtnSettings.getLocalBounds().size / 2.f;
    backBtnSettings.setOrigin(center);

    backBtnSettings.setPosition(sf::Vector2f{center.x , 30.f});

    prev += backBtnSettings.getLocalBounds().size.y + margin;


    // mute button
    if(!muteMusic){

        muteBtn.setString("[ Mute Music ]");


    }else {

        
        muteBtn.setString("[ Unmute Music ]");

    }

    muteBtn.setCharacterSize(20);
    center = muteBtn.getLocalBounds().size / 2.f;
    muteBtn.setOrigin(center);
    muteBtn.setPosition({(center.x + 20), prev});

    prev += muteBtn.getLocalBounds().size.y + margin;


    deleteSaveBtn.setString("[ Delete Save Files ]"); // change functionality later
    center = deleteSaveBtn.getLocalBounds().size / 2.f;
    deleteSaveBtn.setOrigin(center);
    deleteSaveBtn.setCharacterSize(20);
    deleteSaveBtn.setPosition({(center.x + 20), prev});

    window.draw(settingsTitle);
    window.draw(backBtnSettings);
    window.draw(muteBtn);
    window.draw(deleteSaveBtn);

}

void SettingsScreenInputHandling(sf::RenderWindow& window, int& index){
    sf::Vector2i temp = sf::Mouse::getPosition(window);

    // converting to account for screen changes
    sf::Vector2f mousePos = window.mapPixelToCoords(temp);

    if(backBtnSettings.getGlobalBounds().contains(mousePos)){
        index = 0;

    }else if(muteBtn.getGlobalBounds().contains(mousePos)){
        
        muteMusic = !muteMusic;
        
        if (muteMusic){

            music.setVolume(0);

        }else{

            music.setVolume(15.f);

        }


    }else if(deleteSaveBtn.getGlobalBounds().contains(mousePos)){

        deleteSave("src/save-data/lvl1.txt");
        deleteSave("src/save-data/lvl2.txt");
        deleteSave("src/save-data/lvl3.txt");

    }


}

