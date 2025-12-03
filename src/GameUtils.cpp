#include "GameUtils.hpp"

int COLS = 8, ROWS = 8; // constant
unsigned int length = 400, width = 400;
float cellSize = length / COLS;


bool isWithin1(int grid[][8], int first[2], int second[2]){

    if(first[0] - second[0] > 1 || first[0] - second[0] < -1) return false;
    if(first[1] - second[1] > 1 || first[1] - second[1] < -1) return false;

    // diagonal check
    if (first[0] != second[0] && first[1] != second[1]) return false;

    return true;

}

void explodingCandyHandler(int grid[][8], int coord[]){

    int left = coord[1] - 1; // x val
    int right = coord[1] + 1; //x val
    int top = coord[0] -1; // y val
    int bottom = coord[0] + 1;
    grid[coord[0]][coord[1]] = 8;

    if(left >= 0){
        grid[coord[0]][left] = 8;
    }

    if (right < COLS){
        
        grid[coord[0]][right] = 8;

    }
    
    if (top >= 0){
        grid[top][coord[1]] = 8;
    }

    if(bottom >= ROWS){

        grid[bottom][coord[1]] = 8;

    }


    bombSound.play();
    
}

// populates empty spaces
void populateGrid(int grid[][8], int rows){


    for (int r = 0; r < rows; r++){

        for (int c = 0; c < 8; c++){

            if (grid[r][c] == 8){

                grid[r][c] = generateRandom();

            }

        }

    }

}


void swapCells(int coord1[], int coord2[], int grid[][8]){


    int temp = grid[coord1[0]][coord1[1]];
    grid[coord1[0]][coord1[1]] = grid[coord2[0]][coord2[1]];
    grid[coord2[0]][coord2[1]] = temp;

}

//check horizontally for matches
bool horizontalCheck(int rowNum, int col, int range[], int grid[][8]){
    int val = grid[rowNum][col];
    if(val == 8) return false; // skip empty cells

    int start = col;
    int end = col;

    // count consecutive same candies
    for(int c = col + 1; c < COLS; c++){
        if(grid[rowNum][c] == val){
            end = c;
        } else {
            break;
        }
    }

    if(end - start + 1 >= 3){
        range[0] = start;
        range[1] = end;
        return true;
    }

    return false;
}

// Vertical match check
bool verticalCheck(int row, int col, int range[], int grid[][8]){
    int val = grid[row][col];
    if(val == 8) return false;

    int start = row;
    int end = row;

    for(int r = row + 1; r < 8; r++){ // hardcoding 8 rows for now
        if(grid[r][col] == val) end = r;
        else break;
    }

    if(end - start + 1 >= 3){
        range[0] = start;
        range[1] = end;
        return true;
    }
    return false;
}

// replace a row
void replaceRow(int rowNum, int range[], int grid[][8]){

    // different cases
    int length = range[1] - range[0] + 1;

    switch (length)
    {
    case 3:
        
        grid[rowNum][range[0]] = 8; // empty
        break;
    case 4:
        
        grid[rowNum][range[0]] = 6;
        break;

    default:
        grid[rowNum][range[0]] = 7;
        break;
    } 

    // rest become empty
    for (int c = range[0] + 1; c <= range[1]; c++){

        grid[rowNum][c] = 8; // assigning empty space

    }

}

// Replace a vertical match
void replaceColumn(int col, int range[], int grid[][8]){
    int length = range[1] - range[0] + 1;

    if(length == 3) grid[range[0]][col] = 8;
    else if(length == 4) grid[range[0]][col] = 6;
    else grid[range[0]][col] = 7;

    for(int r = range[0] + 1; r <= range[1]; r++) grid[r][col] = 8;
}


// Scan the entire grid and replace all matches
bool findAndReplaceMatches(int grid[][8]){
    bool found = false;
    int range[2];

    // Horizontal matches
    for(int r = 0; r < ROWS; r++){
        int c = 0;
        while(c < COLS){
            if(horizontalCheck(r, c, range, grid)){
                replaceRow(r, range, grid);
                found = true;
                c = range[1] + 1;
            } else c++;
        }
    }

    // Vertical matches
    for(int c = 0; c < COLS; c++){
        int r = 0;
        while(r < ROWS){
            if(verticalCheck(r, c, range, grid)){

                replaceColumn(c, range, grid);
                found = true;
                r = range[1] + 1;

            } else {r++;}
        }
    }

    return found;
}

// Check if swapping two cells creates a valid match
bool isMoveValid(int grid[][8]){

    bool valid = false;
    int range[2];
    for (int r = 0; r < ROWS; r++){

        for (int c = 0; c < COLS; c++){

            if(horizontalCheck(r, c, range, grid)) valid = true;

            if(verticalCheck(r,c,range, grid)) valid = true;

        }

    }

    return valid;
}



// // Check if the grid has any valid moves
// bool validMove(int grid[][COLS], int rows){
//     return isMoveValid(grid, rows);
// }



// Assumes grid is a 2D array where 0 or -1 represents empty space
void applyGravity(int grid[][8], int rows, int cols) {
    // Process each column from bottom to top
    for (int col = 0; col < cols; col++) {
        int writePos = rows - 1;  // Position to write the next candy
        
        // Scan from bottom to top
        for (int row = rows - 1; row >= 0; row--) {
            // If current cell is not empty
            if (grid[row][col] != 8) {

                // Move candy down to writePos
                if (row != writePos) {
                    grid[writePos][col] = grid[row][col];
                    grid[row][col] = 8;  // Mark old position as empty
                }
                writePos--;  // Move write position up
            }
        }
    }
}


// updates the grid after making a move
void updateGrid(int grid[][8], int rows, bool isActive, int score){

    prepareGrid(grid, rows, 8, isActive, score);
}



void prepareGrid(int grid[][8], int rows, int cols, bool isActive, int score){

    while(isMoveValid(grid)){
        if(findAndReplaceMatches(grid) && isActive){
            score+=10;
        }
        applyGravity(grid, rows, 8);
        populateGrid(grid, rows);
    }

}