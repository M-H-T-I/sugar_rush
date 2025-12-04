/*This file has the common variables and functions which are needed by almost all modules
in our game.*/

#ifndef COMMON
#define COMMON

#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <cstdlib>
#include <ctime> 

using namespace std;

extern string states[7];

extern sf::Font globalFont;
extern sf::Texture backgroundImageTexture; 
extern bool userLevels[4];
extern sf::Texture textureArray[9];
extern sf::Music music, bombSound;

//loads all sound that is used within the game
bool loadSound();

//loads the font used within the game.
bool loadFont();

// loads all assets and returns false if any of the loading functions within it fail.
bool loadAssets();

// initializes the seed to be used for random num generation.
void initRandom();

#endif