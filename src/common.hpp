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




bool loadFont();
bool loadAssets();
void initRandom();

#endif