#include "TitleScreen.hpp"

void drawTitleScreen(sf::RenderWindow& window){

  
    // title text
    sf::Text titleText(globalFont);
    titleText.setString("Sugar Rush");
    titleText.setCharacterSize(80);

    window.clear();

    window.draw(titleText);

}