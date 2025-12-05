#include "common.hpp"
#include "Lvl1.hpp"

// ----------------------------- NECESSARY DATA ----------------------------

// used for input handling 
bool selected = false;
int selectedCell[] = {-1, -1}; // unselected state is -1, -1

// used to tell if game has started. Used in preparing the level
bool isActive = false;

bool lvlEnd;
// imp data
int moves = 20, score = 0, requiredScore = 1500, margin = 50; 

// used to tell if mouse was clicked in the previous frame (input handling ma use hona)
bool mousePressedLastFrame = false;


sf::Text backBtnLvl1(globalFont);
sf::Text movesText(globalFont);
sf::Text scoreText(globalFont);
sf::Sprite gridElement(textureArray[8]);
sf::Text exitBtn(globalFont);

sf::RenderTexture gridRT({length, width});

// ---------------------------------------- GRID INFO ----------------------------------//

int grid[8][8];
sf::Sprite* spriteGrid[8][8]; // will save all the sprites so I dont have to do any calculations



// ------------------ Functions---------------------------- 

void swapWithAnimation(int grid[][8], int coord1[], int coord2[], sf::RenderWindow& window){
    
    // Redraw swapped grid
    createGridTexture(grid, gridRT);
    window.clear();
    drawLvl1Screen(window); // your draw function
    window.display();

    // If move invalid, wait 0.5s and swap back
    if(!isMoveValid(grid)){

        swapCells(coord1, coord2, grid);

        createGridTexture(grid, gridRT);
        window.clear();
        drawLvl1Screen(window);
        window.display();
    }
}



bool isInGrid(sf::Vector2f mousePos) {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            if (spriteGrid[r][c]->getGlobalBounds().contains(mousePos))
                return true;
        }
    }
    return false;
}


void initSprites(){

    for (int row = 0; row < ROWS; row++){

        for (int c = 0; c < COLS; c++){
            spriteGrid[row][c] = new sf::Sprite(textureArray[8]);
        }
    }

}

// called before mainloop is initialized
bool initLevel1(){

    moves = 20;
    score = 0;
    bool valid = true;

    // assign its grid values
    initGrid(grid, 8);

    initSprites(); // no chance for failure really (no exception needed)

    // removes any and all matches
    prepareGrid(grid, ROWS, COLS, isActive, score);

    // level is active
    isActive = true;
    lvlEnd = false;

    cout << "initialized level 1" << endl;

    return valid;
}

// creates the inside of my grid
void createGridTexture(int grid[8][8], sf::RenderTexture& gridTexture){

    gridTexture.clear(sf::Color::White);

    // using the grid array
    for (int i = 0; i < ROWS; i++){

        for (int j = 0; j < COLS; j++){

            int textureNum;

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
    gridTexture.display();
}


void drawLvl1Screen(sf::RenderWindow& window){
    
    // updateGrid(grid, rows);

    float prev = 0.f;


    // title of the page
    sf::Text title(globalFont);
    title.setString("Level 1");
    title.setCharacterSize(60);
    title.setFillColor(sf::Color(191, 78, 48)); 

    // centering the title text
    auto center = title.getLocalBounds().size / 2.f;
    title.setOrigin(center);
    title.setPosition(sf::Vector2f{(window.getSize().x / 2.f), (center.y + margin)});

    prev += title.getLocalBounds().size.y + margin;

    createGridTexture(grid, gridRT);

    // drawing the grid
    gridElement = sf::Sprite(gridRT.getTexture());

    center = gridElement.getLocalBounds().size / 2.f;
    gridElement.setOrigin(center);
    gridElement.setPosition({(window.getSize().x / 2.f), (prev + margin + center.y + 50)});

    prev = margin;

    // backBtnLvl1
    backBtnLvl1.setString("back");
    backBtnLvl1.setCharacterSize(25);
    backBtnLvl1.setFillColor(sf::Color::White);

    center = backBtnLvl1.getLocalBounds().size / 2.f;
    backBtnLvl1.setOrigin(center);

    backBtnLvl1.setPosition(sf::Vector2f{50.f , 10.f});

    prev += backBtnLvl1.getLocalBounds().size.y + margin;

    // moves
    string movesString = "moves: " + std::to_string(moves);
    movesText.setString(movesString);
    movesText.setCharacterSize(25);
    movesText.setFillColor(sf::Color::White);

    center = movesText.getLocalBounds().size / 2.f;
    movesText.setOrigin(center);

    movesText.setPosition(sf::Vector2f{50.f , prev});

    prev+=movesText.getLocalBounds().size.y + margin;

    // score
    string scoreString = "score: " + std::to_string(score) + " / " + std::to_string(requiredScore);
    scoreText.setString(scoreString);
    scoreText.setCharacterSize(25);
    scoreText.setFillColor(sf::Color::White);

    center = scoreText.getLocalBounds().size / 2.f;
    scoreText.setOrigin(center);

    scoreText.setPosition(sf::Vector2f{center.x , prev - 20.f});

    window.draw(title);
    window.draw(backBtnLvl1);
    window.draw(movesText);
    window.draw(scoreText);
    window.draw(gridElement);

    if(isLvlEnd(score, requiredScore, moves)){
        
        if (score >= requiredScore){

            drawWinScreen(window, exitBtn);

        }else{

            drawLoseScreen(window, exitBtn);
        }
    }

}


void inputHandleGrid(sf::Vector2f mousePos, sf::RenderWindow& window, int& index) {

    // detect single click (not hold)
    bool mousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

    if(mousePressed == false){
        return;
    }

    // find clicked cell
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {

            if (spriteGrid[r][c]->getGlobalBounds().contains(mousePos)) {

                // FIRST SELECTION
                if (!selected) {

                    if(grid[r][c] == 6){
                        int coords[] = {r,c};
                        explodingCandyHandler(grid, coords);
                        moves--;
                        score += 250;
                        return;
                        
                    }else if(grid[r][c] == 7){

                        int coords[] = {r,c};
                        rowCandyHandler(grid, coords);
                        moves--;
                        score += 500;
                        return;

                    }

                    selected = true;
                    selectedCell[0] = r;
                    selectedCell[1] = c;

                    return;
                }

                // SECOND SELECTION
                int cell[2] = {r, c};

                cout << grid[r][c];

                // swap attempt
                swapCells(cell, selectedCell, grid);
                cout << grid[r][c];

                createGridTexture(grid, gridRT);
                gridElement = sf::Sprite(gridRT.getTexture());

                if(isWithin1(grid, cell, selectedCell)){
                    
                    // if not valid
                    if (!isMoveValid(grid)) {

                        swapCells(cell, selectedCell, grid);

                    } 
                    else {
                        
                        updateGrid(grid, ROWS, isActive, score);

                        moves--;
                        score += 20;

                        
                    }
                }else {
                    swapCells(cell,selectedCell, grid);
                }

                

                // reset selection
                selected = false;
                selectedCell[0] = -1;
                selectedCell[1] = -1;

                return;
            }
        }
    }
}


void Lvl1ScreenInputHandling(sf::RenderWindow& window, int& index){

    sf::Vector2i temp = sf::Mouse::getPosition(window);

    //convert that into coords
    sf::Vector2f mousePos = window.mapPixelToCoords(temp);


    if (isLvlEnd(score, requiredScore, moves)){

        lvlEnd = true;

        if(lvlEnd && exitBtn.getGlobalBounds().contains(mousePos)){

            selected = false;
            index = 1;
            return; 
        }

    }else if(backBtnLvl1.getGlobalBounds().contains(mousePos)){
        selected = false;
        index = 1; // save and exit option later
        return;
    
    }else {

        sf::Vector2f gridTopLeft = gridElement.getPosition() - gridElement.getOrigin();
        sf::Vector2f local = mousePos - gridTopLeft;

        if(isInGrid(local)){
            inputHandleGrid(local, window, index);

        }
        
        

    }

}   


