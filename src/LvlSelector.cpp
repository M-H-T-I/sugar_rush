#include "LvlSelector.hpp"

void drawLvlSelectorScreen(sf::RenderWindow& window){

    float margin = 70.f, prev = margin;

    // title of the page
    sf::Text titleText(globalFont);
    titleText.setString("Level Selector");
    titleText.setCharacterSize(60);
    titleText.setFillColor(sf::Color(191, 78, 48));

    // centering the title text
    auto center = titleText.getLocalBounds().size / 2.f;
    titleText.setOrigin(center);
    titleText.setPosition(sf::Vector2f{(window.getSize().x / 2.f), (center.y)});



    // tutorial button
    sf::Text tutorialBtn(globalFont);
    tutorialBtn.setString("Tutorial");
    tutorialBtn.setCharacterSize(30);
    tutorialBtn.setFillColor(sf::Color::White);

    center = tutorialBtn.getLocalBounds().size / 2.f;
    tutorialBtn.setOrigin(center);

    tutorialBtn.setPosition(sf::Vector2f{(prev), window.getSize().y / 2.f});

    prev += tutorialBtn.getGlobalBounds().size.x + margin;



    // lvl1 button
    sf::Text lvl1Btn(globalFont);
    lvl1Btn.setString("Level 1");
    lvl1Btn.setCharacterSize(30);
    lvl1Btn.setFillColor(sf::Color::White);

    center = lvl1Btn.getLocalBounds().size / 2.f;
    lvl1Btn.setOrigin(center);

    lvl1Btn.setPosition(sf::Vector2f{(prev), window.getSize().y / 2.f});

    prev += lvl1Btn.getGlobalBounds().size.x + margin;



    // lvl2 button
    sf::Text lvl2Btn(globalFont);
    lvl2Btn.setString("Level 2");
    lvl2Btn.setCharacterSize(30);
    lvl2Btn.setFillColor(sf::Color::White);

    center = lvl2Btn.getLocalBounds().size / 2.f;
    lvl2Btn.setOrigin(center);

    lvl2Btn.setPosition(sf::Vector2f{(prev), window.getSize().y / 2.f});

    prev += lvl2Btn.getGlobalBounds().size.x + margin;



    // lvl3 button
    sf::Text lvl3Btn(globalFont);
    lvl3Btn.setString("Level 3");
    lvl3Btn.setCharacterSize(30);
    lvl3Btn.setFillColor(sf::Color::White);

    center = lvl3Btn.getLocalBounds().size / 2.f;
    lvl3Btn.setOrigin(center);

    lvl3Btn.setPosition(sf::Vector2f{(prev), window.getSize().y / 2.f});

    prev += lvl3Btn.getGlobalBounds().size.x + margin;


    // backbtn
    sf::Text backBtn(globalFont);
    backBtn.setString("back");
    backBtn.setCharacterSize(25);
    backBtn.setFillColor(sf::Color::White);

    center = backBtn.getLocalBounds().size / 2.f;
    backBtn.setOrigin(center);

    backBtn.setPosition(sf::Vector2f{30.f , 10.f});




    window.clear(sf::Color(60, 176, 205));
    window.draw(titleText);
    window.draw(tutorialBtn);
    window.draw(lvl1Btn);
    window.draw(lvl2Btn);
    window.draw(lvl3Btn);
    window.draw(backBtn);


}