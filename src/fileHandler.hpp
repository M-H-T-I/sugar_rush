#pragma once

#include "common.hpp"

bool readFile(string path, int store[][8], int& score, int& moves);
bool deleteSave(const string path);
bool writeSave(string path, int grid[][2], int score, int moves);