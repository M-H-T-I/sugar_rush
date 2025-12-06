// logic for title screen window
#pragma once

#include "common.hpp"

extern sf::Text titleText, playText, settingsText, newUserText;


void drawTitleScreen(sf::RenderWindow& window);
void titleScreenInputHandling(sf::RenderWindow& window, int& index);