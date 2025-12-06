/*Level 1 ka logic sara*/
#pragma once

#include "common.hpp"
#include "GameUtils.hpp"
#include <SFML/System.hpp>



bool initLevel3(); // initializes the grid by assigning values to each cell
void drawLvl3Screen(sf::RenderWindow& window); // draws the screen inclding the grid
void Lvl3ScreenInputHandling(sf::RenderWindow& window, int& index); 
