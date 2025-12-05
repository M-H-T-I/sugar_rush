/*Level 1 ka logic sara*/

#include "common.hpp"
#include "GameUtils.hpp"
#include <SFML/System.hpp>



bool initLevel1(); // initializes the grid by assigning values to each cell
void drawLvl1Screen(sf::RenderWindow& window); // draws the screen inclding the grid
void Lvl1ScreenInputHandling(sf::RenderWindow& window, int& index); 
