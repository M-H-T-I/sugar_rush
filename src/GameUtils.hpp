#ifndef GAME_UTILS
#define GAMR_UTILS

#include "common.hpp"
#include "GridUtils.hpp"


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
#endif