#include "GameUtils.hpp"

int COLS = 8, ROWS = 8; // constant
unsigned int length = 400, width = 400;
float cellSize = length / COLS;

bool isActive = false;

int score = 0, requiredScore = 1500;


bool opaqueGrid[8][8]; // tells which cells need to be opaque

// ----------- Grid INfo
int grid[8][8];
sf::Sprite* spriteGrid[8][8]; // will save all the sprites so I dont have to do any calculations


bool isAnimating = false;

// ---------------------------------------------------------- Functions ------------------------------- // 

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
            opaqueGrid[i][j] = true;

        }

    }

}

void initSprites(sf::Sprite* spriteGrid[][8]){

    for (int row = 0; row < ROWS; row++){

        for (int c = 0; c < COLS; c++){
            spriteGrid[row][c] = new sf::Sprite(textureArray[8]);
        }
    }

}


bool isInGrid(sf::Vector2f mousePos, sf::Sprite* spriteGrid[][8]) {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            if (spriteGrid[r][c]->getGlobalBounds().contains(mousePos))
                return true;
        }
    }
    return false;
}

void drawWinScreen(sf::RenderWindow& window, sf::Text& exitBtn){


    sf::RectangleShape rect({500, 300});
    auto center =rect.getLocalBounds().size / 2.f;
    rect.setOrigin(center);
    rect.setPosition({(window.getSize().x / 2.f ), (window.getSize().y/2.f)});
    rect.setFillColor(sf::Color::Black);


    sf::Text txt(globalFont);
    txt.setCharacterSize(52);            
    txt.setStyle(sf::Text::Bold);
    center = txt.getLocalBounds().size / 2.f;
    txt.setFillColor(sf::Color::White);
    txt.setOrigin(center);
    txt.setString("You WON!!!");
    txt.setPosition({(rect.getGlobalBounds().getCenter().x - txt.getLocalBounds().size.x / 2.f), rect.getGlobalBounds().getCenter().y - txt.getLocalBounds().size.y / 2.f});

    exitBtn.setCharacterSize(20);
    exitBtn.setString("[ Go to Level Selector ]");
    exitBtn.setOrigin(exitBtn.getLocalBounds().size / 2.f);
    exitBtn.setPosition({rect.getGlobalBounds().getCenter().x, rect.getGlobalBounds().getCenter().y + txt.getLocalBounds().size.y + 40});

    window.draw(rect);
    window.draw(txt);
    window.draw(exitBtn);

}

void drawLoseScreen(sf::RenderWindow& window, sf::Text& exitBtn){

    sf::RectangleShape rect({500, 300});
    auto center =rect.getLocalBounds().size / 2.f;
    rect.setOrigin(center);
    rect.setPosition({(window.getSize().x / 2.f), (window.getSize().y/2.f)});
    rect.setFillColor(sf::Color::Black);


    sf::Text txt(globalFont);
    txt.setCharacterSize(48);            
    txt.setStyle(sf::Text::Bold);
    center = txt.getLocalBounds().size / 2.f;
    txt.setFillColor(sf::Color::White);
    txt.setOrigin(center);
    txt.setString("You Lost");
    txt.setPosition({(rect.getGlobalBounds().getCenter().x - txt.getLocalBounds().size.x / 2.f), rect.getGlobalBounds().getCenter().y - txt.getLocalBounds().size.y / 2.f});

    exitBtn.setCharacterSize(20);
    exitBtn.setString("[ Go to Level Selector ]");
    exitBtn.setOrigin(exitBtn.getLocalBounds().size / 2.f);
    exitBtn.setPosition({rect.getGlobalBounds().getCenter().x, rect.getGlobalBounds().getCenter().y + txt.getLocalBounds().size.y + 40});

    window.draw(rect);
    window.draw(txt);
    window.draw(exitBtn);

}

bool isLvlEnd(int score, int requiredScore, int moves){

    if(moves <= 0 || score >= requiredScore){

        return true;

    }else {
        return false;
    }




}


bool isWithin1(int grid[][8], int first[2], int second[2]){

    if(first[0] - second[0] > 1 || first[0] - second[0] < -1) return false;
    if(first[1] - second[1] > 1 || first[1] - second[1] < -1) return false;

    // diagonal check
    if (first[0] != second[0] && first[1] != second[1]) return false;

    return true;

}


void rowCandyHandler(int grid[][8], int coord[]){

    int left = coord[1] - 0; // x val
    int right = ROWS - coord[1]; //x val
    grid[coord[0]][coord[1]] = 8;    


    if(left > 0){
        for (int i = 0; i < coord[1]; i++){

            grid[coord[0]][i] = 8;
            opaqueGrid[coord[0]][i] = false;
        }
    }

    if (right > 0){
        
        for (int i = coord[1] + 1; i < COLS; i++){

            grid[coord[0]][i] = 8;
            opaqueGrid[coord[0]][i] = false;

        } 

    }

    popSound.play();
    isAnimating = true;
    return;
}

void explodingCandyHandler(int grid[][8], int coord[]){

    int left = coord[1] - 1; // x val
    int right = coord[1] + 1; //x val
    int top = coord[0] -1; // y val
    int bottom = coord[0] + 1;
    grid[coord[0]][coord[1]] = 8;
    opaqueGrid[coord[0]][coord[1]];

    if(left >= 0){
        grid[coord[0]][left] = 8;
        opaqueGrid[coord[0]][left] = false;

    }

    if (right < COLS){
        
        grid[coord[0]][right] = 8;
        opaqueGrid[coord[0]][right] = false;

    }
    
    if (top >= 0){
        grid[top][coord[1]] = 8;
        opaqueGrid[top][coord[1]] = false;

    }


    if(bottom < ROWS){

        grid[bottom][coord[1]] = 8;
        opaqueGrid[bottom][coord[1]] = false;

    }

    isAnimating = true;
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
void prepareGrid(int grid[][8], int rows, int cols){

    findAndReplaceMatches(grid);
    applyGravity(grid, rows, 8);
    populateGrid(grid, rows);
    

}


// ---------------- animated functions
// replace a row
void replaceRowAnimated(int rowNum, int range[], int grid[][8]){

    // different cases
    int length = range[1] - range[0] + 1;

    switch (length)
    {
    case 3:
        
        grid[rowNum][range[0]] = 8; // empty
        score += 30;
        break;
    case 4:
        
        grid[rowNum][range[0]] = 6;
        score += 40;
        break;

    default:
        grid[rowNum][range[0]] = 7;
        score+=50;
        break;
    } 

        opaqueGrid[rowNum][range[0]] = false;


    // rest become empty
    for (int c = range[0] + 1; c <= range[1]; c++){

        grid[rowNum][c] = 8;
        opaqueGrid[rowNum][c] = false; // assigning empty space

    }

    isAnimating  = true;
}

// Replace a vertical match
void replaceColumnAnimated(int col, int range[], int grid[][8]){
    int length = range[1] - range[0] + 1;

    if(length == 3){

        grid[range[0]][col] = 8;

        score += 30;

    }
    else if(length == 4){

        grid[range[0]][col] = 6;
        score += 40;

    } 
    else {
     
        grid[range[0]][col] = 7;
        score += 50;
    }
    
    opaqueGrid[range[0]][col] = false;


    for(int r = range[0] + 1; r <= range[1]; r++) {

        opaqueGrid[r][col] = false;
        grid[r][col] = 8;


    }

    isAnimating = true;

}


// Scan the entire grid and replace all matches
bool findAndReplaceMatchesAnimated(int grid[][8]){
    bool found = false;
    int range[2];

    // Horizontal matches
    for(int r = 0; r < ROWS; r++){
        int c = 0;
        while(c < COLS){
            if(horizontalCheck(r, c, range, grid)){
                replaceRowAnimated(r, range, grid);
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

                replaceColumnAnimated(c, range, grid);
                found = true;
                r = range[1] + 1;

            } else {r++;}
        }
    }

    return found;
}

// creates the inside of my grid
void createGridTexture(int grid[][8], sf::RenderTexture& gridTexture, sf::Sprite* spriteGrid[][8]){

    gridTexture.clear(sf::Color::White);

    if (!isAnimating){

        // using the grid array
        for (int i = 0; i < ROWS; i++){

            for (int j = 0; j < COLS; j++){

                int textureNum;

                // select texture
                switch (grid[i][j]){

                case 1:
                    
                    textureNum = 0;
                    break;

                case 2:

                    textureNum = 1;
                    break;

                case 3:

                    textureNum = 2;
                    break;

                case 4:

                    textureNum = 5;
                    break;

                case 5: 
                    
                    textureNum = 4;
                    break;

                case 6:

                    textureNum = 6;
                    break;
                
                case 7:

                    textureNum = 7;
                    break;

                case 8:

                    textureNum = 8;
                    break;

                };
                
                
                sf::Sprite temp(textureArray[textureNum]);
                temp.setScale({(cellSize / textureArray[textureNum].getSize().x), (cellSize / textureArray[textureNum].getSize().y)});
                sf::Vector2f pos {(j*cellSize), (i*cellSize)}; // position vector for the new cell
                temp.setPosition(pos);
                *spriteGrid[i][j] = temp;
                gridTexture.draw(temp);

            }

        }

    // animated
    }else {

        bool finished = true; // when animation will end;
        
        for (int r = 0; r < ROWS; r++){

            for(int c = 0; c < COLS; c++){

                if(opaqueGrid[r][c] == false){

                    sf::Sprite* temp = spriteGrid[r][c];
                    sf::Color tempColor = temp->getColor();

                    if(tempColor.a > 0){

                        tempColor.a = max(0, (tempColor.a - 15));
                        temp->setColor(tempColor);

                        finished = false;

                    }else {

                        opaqueGrid[r][c] = true;

                    }

                }

                gridTexture.draw(*spriteGrid[r][c]);

            }

        }

        if (finished){

            isAnimating = false;

        }

    }

    gridTexture.display();
}


// updates the grid after making a move
void updateGrid(int grid[][8], int rows){

    findAndReplaceMatchesAnimated(grid);

    if(!isAnimating){

        applyGravity(grid, ROWS, COLS);
        populateGrid(grid, ROWS);

    }

}
