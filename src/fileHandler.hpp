#pragma once
#include <string>
#include "common.hpp"

using namespace std;

bool readSaveFile(string path, int store[][8], int& score, int& moves, int level);
bool deleteSave(const string path);
bool writeSave(string path, int grid[][8], int score, int moves);
bool readmute(bool& mutemusic);
bool savemute(bool muteMusic);
bool readLevel(int& index);