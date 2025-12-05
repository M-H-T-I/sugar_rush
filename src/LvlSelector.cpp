#include "LvlSelector.hpp"
#include "Lvl1.hpp"
#include "Lvl2.hpp"
#include "Lvl3.hpp"

sf::Text titleTextLvlSelector(globalFont);
sf::Text tutorialBtn(globalFont);
sf::Text lvl1Btn(globalFont);
sf::Text lvl2Btn(globalFont);
sf::Text lvl3Btn(globalFont);
sf::Text backBtn(globalFont);


void drawLvlSelectorScreen(sf::RenderWindow& window){

    float margin = 70.f, prev = margin;

    // title of the page
    titleTextLvlSelector.setString("Level Selector");
    titleTextLvlSelector.setCharacterSize(60);
    titleTextLvlSelector.setFillColor(sf::Color(191, 78, 48));

    // centering the title text
    auto center = titleTextLvlSelector.getLocalBounds().size / 2.f;
    titleTextLvlSelector.setOrigin(center);
    titleTextLvlSelector.setPosition(sf::Vector2f{(window.getSize().x / 2.f), (center.y)});



    // tutorial button
    tutorialBtn.setString("Tutorial");
    tutorialBtn.setCharacterSize(30);
    tutorialBtn.setFillColor(sf::Color::White);

    center = tutorialBtn.getLocalBounds().size / 2.f;
    tutorialBtn.setOrigin(center);

    tutorialBtn.setPosition(sf::Vector2f{(prev), window.getSize().y / 2.f});

    prev += tutorialBtn.getGlobalBounds().size.x + margin;

    // lvl1 button
    lvl1Btn.setString("Level 1");
    lvl1Btn.setCharacterSize(30);
    lvl1Btn.setFillColor(sf::Color::White);

    center = lvl1Btn.getLocalBounds().size / 2.f;
    lvl1Btn.setOrigin(center);

    lvl1Btn.setPosition(sf::Vector2f{(prev), window.getSize().y / 2.f});

    prev += lvl1Btn.getGlobalBounds().size.x + margin;



    // lvl2 button
    lvl2Btn.setString("Level 2");
    lvl2Btn.setCharacterSize(30);
    lvl2Btn.setFillColor(sf::Color::White);

    center = lvl2Btn.getLocalBounds().size / 2.f;
    lvl2Btn.setOrigin(center);

    lvl2Btn.setPosition(sf::Vector2f{(prev), window.getSize().y / 2.f});

    prev += lvl2Btn.getGlobalBounds().size.x + margin;



    // lvl3 button
    lvl3Btn.setString("Level 3");
    lvl3Btn.setCharacterSize(30);
    lvl3Btn.setFillColor(sf::Color::White);

    center = lvl3Btn.getLocalBounds().size / 2.f;
    lvl3Btn.setOrigin(center);

    lvl3Btn.setPosition(sf::Vector2f{(prev), window.getSize().y / 2.f});

    prev += lvl3Btn.getGlobalBounds().size.x + margin;


    // backbtn
    backBtn.setString("back");
    backBtn.setCharacterSize(25);
    backBtn.setFillColor(sf::Color::White);

    center = backBtn.getLocalBounds().size / 2.f;
    backBtn.setOrigin(center);

    backBtn.setPosition(sf::Vector2f{30.f , 10.f});




    window.clear(sf::Color(60, 176, 205));
    window.draw(titleTextLvlSelector);
    window.draw(tutorialBtn);
    window.draw(lvl1Btn);
    window.draw(lvl2Btn);
    window.draw(lvl3Btn);
    window.draw(backBtn);


}

void lvlSelectorScreenInputHandling(sf::RenderWindow& window, int& index){

    //get mouse position
    sf::Vector2i temp = sf::Mouse::getPosition(window);

    //convert to proper coord form
    sf::Vector2f mousePos = window.mapPixelToCoords(temp);

    if(backBtn.getGlobalBounds().contains(mousePos)){

        index = 0;
    }else if(lvl1Btn.getGlobalBounds().contains(mousePos)){
        
        index = 2;
        initLevel1();

    }else if(lvl2Btn.getGlobalBounds().contains(mousePos)){

        index = 3;
        initLevel2();

    }else if(lvl3Btn.getGlobalBounds().contains(mousePos)){

        index = 4;
        initLevel3();

    }else if(tutorialBtn.getGlobalBounds().contains(mousePos)){
        index = 5;
    }


}