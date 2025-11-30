#include "GridUtils.hpp"


int generateRandom(){

    int n = std::rand() % 5 + 1; // 1- 5
    return n;

}

void initGrid(int grid[][8], int rows){    
    
    initRandom();

    for (int i = 0; i < rows; i++){

        for (int j = 0; j < 8; j++){
            
            int n = generateRandom();
            grid[i][j] = n;

        }

    }

}

