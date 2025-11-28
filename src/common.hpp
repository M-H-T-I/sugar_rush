#ifndef COMMON
#define COMMON

#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>

using namespace std;

extern string states[7];

extern sf::Font globalFont;
extern sf::Texture backgroundImageTexture; 

bool loadFont();
bool loadAssets();

#endif