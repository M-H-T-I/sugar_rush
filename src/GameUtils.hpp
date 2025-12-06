/* This file has the funtions required by all the levels in the game as well as important
variables that will be used by those levels as well.*/


#ifndef GAME_UTILS
#define GAME_UTILS

#include "common.hpp"


extern unsigned int length, width;
extern int COLS, ROWS, score, requiredScore;
extern float cellSize;

extern int grid[8][8];
extern sf::Sprite* spriteGrid[8][8];
extern bool opaqueGrid [8][8], isAnimating, isActive;

// swaps cells using the indexes given
void swapCells(int coord1[], int coord2[], int grid[][8]);

// called after shifting the array to fill empty slots
void populateGrid(int grid[][8], int rows);

void updateGrid(int grid[][8], int rows);

void makeMove(int grid[][8], int rows);

bool isMoveValid(int grid[][8]);

bool findAndReplaceMatches(int grid[][8]);

// removes any matches to be used after init grid and after every move
void prepareGrid(int grid[][8], int rows, int cols);

bool isWithin1(int grid[][8], int first[2], int second[2]);

void explodingCandyHandler(int grid[][8], int coords[]);
void rowCandyHandler(int grid[][8], int coord[]);

void initGrid(int grid[][8], int rows); // initializes the grid with random values

int generateRandom(); // generates a random number between 1-5 (all candies exxcept the special ones)

bool isLvlEnd(int score, int requiredScore, int moves); // tells if a level is won or lost

void drawWinScreen(sf::RenderWindow& window, sf::Text& exitBtn);
void drawLoseScreen(sf::RenderWindow& window, sf::Text& exitBtn);

bool isInGrid(sf::Vector2f mousePos, sf::Sprite* spriteGrid[][8]);

void initSprites(sf::Sprite* spriteGrid[][8]);

void createGridTexture(int grid[][8], sf::RenderTexture& gridTexture, sf::Sprite* spriteGrid[][8]);


#endif