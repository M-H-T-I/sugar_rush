#pragma once

#include "common.hpp"
#include "GameUtils.hpp"
#include <SFML/System.hpp>



bool initTutorial(); // initializes the grid by assigning values to each cell
void drawTutorialScreen(sf::RenderWindow& window); // draws the screen inclding the grid
void tutorialScreenInputHandling(sf::RenderWindow& window, int& index); 
