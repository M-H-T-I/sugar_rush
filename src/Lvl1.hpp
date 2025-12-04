/*Level 1 ka logic sara*/

#include "common.hpp"
#include "GameUtils.hpp"
#include <SFML/System.hpp>

extern int moves, score, requiredScore;
extern int grid[8][8];
extern bool isActive;


bool initLevel1(); // initializes the grid by assigning values to each cell
void drawLvl1Screen(sf::RenderWindow& window); // draws the screen inclding the grid
void Lvl1ScreenInputHandling(sf::RenderWindow& window, int& index); 
sf::RenderTexture createGridTexture(int grid[8][8]); // creates the texture of the grid which the drawLvl1Screen function draws onto the window.