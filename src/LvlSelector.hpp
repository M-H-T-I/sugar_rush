#include "common.hpp"

extern sf::Text titleText, lvl1Btn, tutorialBtn, lvl2Btn, lvl3btn, backBtn;

void drawLvlSelectorScreen(sf::RenderWindow& window);
void lvlSelectorScreenInputHandling(sf::RenderWindow& window, int& index);