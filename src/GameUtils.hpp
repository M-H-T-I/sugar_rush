/* This file has the funtions required by all the levels in the game as well as important
variables that will be used by those levels as well.*/


#ifndef GAME_UTILS
#define GAMR_UTILS

#include "common.hpp"


extern unsigned int length, width;
extern int COLS, ROWS;
extern float cellSize;


// swaps cells using the indexes given
void swapCells(int coord1[], int coord2[], int grid[][8]);

// called after shifting the array to fill empty slots
void populateGrid(int grid[][8], int rows);

void updateGrid(int grid[][8], int rows, bool isActive, int score);

void makeMove(int grid[][8], int rows);

bool isMoveValid(int grid[][8]);

bool findAndReplaceMatches(int grid[][8]);

// removes any matches to be used after init grid and after every move
void prepareGrid(int grid[][8], int rows, int cols, bool isActive, int score);

bool isWithin1(int grid[][8], int first[2], int second[2]);

void explodingCandyHandler(int grid[][8], int coords[]);
void rowCandyHandler(int grid[][8], int coord[]);

void initGrid(int grid[][8], int rows); // initializes the grid with random values
int generateRandom(); // generates a random number between 1-5 (all candies exxcept the special ones)

#endif