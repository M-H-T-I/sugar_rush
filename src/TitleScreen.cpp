#include "TitleScreen.hpp"
#include <cmath>

void drawTitleScreen(sf::RenderWindow& window){

    // title text
    sf::Text titleText(globalFont);
    titleText.setString("Sugar Rush");
    titleText.setCharacterSize(60);
    titleText.setFillColor(sf::Color::White);

    // centering the title text
    auto center = titleText.getLocalBounds().size / 2.f;
    titleText.setOrigin(center);
    titleText.setPosition(sf::Vector2f{(window.getSize().x / 2.f), (center.y)});

    cout << titleText.getPosition().x;

    titleText.setFillColor(sf::Color{0x655A7CFF}); 

    window.clear(sf::Color::Black);
    window.draw(titleText);

}

