#include "TitleScreen.hpp"
#include <cmath>
#include "Lvl1.hpp"
#include "Lvl2.hpp"
#include "Lvl3.hpp"

sf::Text titleText(globalFont);
sf::Text playText(globalFont);
sf::Text settingsText(globalFont);
sf::Text loadBtn(globalFont);

bool showError = false;

void drawTitleScreen(sf::RenderWindow& window){

    const float margin = 50.f;
    float prev = 100.f;

    // title text
    titleText.setString("Sugar Rush");
    titleText.setCharacterSize(60);
    titleText.setFillColor(sf::Color(191, 78, 48)); 

    // centering the title text
    auto center = titleText.getLocalBounds().size / 2.f;
    titleText.setOrigin(center);
    titleText.setPosition(sf::Vector2f{(window.getSize().x / 2.f), (center.y)});

    prev += titleText.getLocalBounds().size.y;



    // play button
    playText.setString("Play");
    playText.setCharacterSize(30);
    playText.setFillColor(sf::Color::White);

    // center play button:
    center = playText.getLocalBounds().size / 2.f;
    playText.setOrigin(center);
    playText.setPosition(sf::Vector2f{(window.getSize().x / 2.f), ( margin + prev)});

    prev += playText.getLocalBounds().size.y + margin;

    // settings
    settingsText.setString("Settings");
    settingsText.setCharacterSize(30);
    settingsText.setFillColor(sf::Color::White);

    // center settings button:
    center = settingsText.getLocalBounds().size / 2.f;
    settingsText.setOrigin(center);
    settingsText.setPosition(sf::Vector2f{(window.getSize().x / 2.f), ( margin + prev)});

    prev += settingsText.getLocalBounds().size.y + margin;


    // settings
    loadBtn.setString("Load Save");
    loadBtn.setCharacterSize(30);
    loadBtn.setFillColor(sf::Color::White);

    // center settings button:
    center = loadBtn.getLocalBounds().size / 2.f;
    loadBtn.setOrigin(center);
    loadBtn.setPosition(sf::Vector2f{(window.getSize().x / 2.f), ( margin + prev)});

    prev += loadBtn.getLocalBounds().size.y + margin;


    // ERROR TEXT 
    sf::Text errorText(globalFont);
    errorText.setString("NO save file found!");
    errorText.setCharacterSize(20);
    errorText.setFillColor(sf::Color::White);

    // center settings button:
    center = errorText.getLocalBounds().size / 2.f;
    errorText.setOrigin(center);
    errorText.setPosition(sf::Vector2f{(window.getSize().x / 2.f), ( margin + prev)});

    prev += errorText.getLocalBounds().size.y + margin;




    window.clear(sf::Color(60, 176, 205));
    window.draw(titleText);
    window.draw(playText);
    window.draw(settingsText);
    window.draw(loadBtn);
    if(showError == true) window.draw(errorText);

}


void titleScreenInputHandling(sf::RenderWindow& window, int& index){
    
    sf::Vector2i temp = sf::Mouse::getPosition(window);

    // converting to account for screen changes
    sf::Vector2f mousePos = window.mapPixelToCoords(temp);

    if(playText.getGlobalBounds().contains(mousePos)){
        index = 1;
    }else if(settingsText.getGlobalBounds().contains(mousePos)){
        index = 6;
    }else if(loadBtn.getGlobalBounds().contains(mousePos)){

        if(!readLevel(index)){
            showError = true;
        }else if(index == 2){
            initLevel1();
        }else if(index == 3){
            initLevel2();
        }else if(index == 4){
            initLevel3();
        }else {
            index = 0;
        }
    }   


}
