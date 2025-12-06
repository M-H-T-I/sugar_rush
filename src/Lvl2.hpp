/*Level 1 ka logic sara*/
#pragma once

#include "common.hpp"
#include "GameUtils.hpp"
#include <SFML/System.hpp>



bool initLevel2(); // initializes the grid by assigning values to each cell
void drawLvl2Screen(sf::RenderWindow& window); // draws the screen inclding the grid
void Lvl2ScreenInputHandling(sf::RenderWindow& window, int& index); 
