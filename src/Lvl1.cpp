#include "common.hpp"
#include "GridUtils.hpp"


// ----------------------------- NECESSARY DATA ----------------------------

bool selected = false;
int selectedCell[] = {-1, -1}; // unselected state is -1, -1
int matchType = 0;

int moves = 20, score = 0, requiredScore = 2500, margin = 50; 



sf::Text backBtnLvl1(globalFont);
sf::Text movesText(globalFont);
sf::Text scoreText(globalFont);
sf::Sprite gridElement(textureArray[8]);




// ---------------------------------------- GRID INFO ----------------------------------//

int grid[8][8];
sf::Sprite* spriteGrid[8][8]; // will save all the sprites so I dont have to do any calculations


int cols = 8, rows = 8;
uint length = 400, width = 400;
float cellSize = length / cols;



// ------------------ Functions




void swapCells(int coord1[], int coord2[]){

    int temp = grid[coord1[0]][coord1[1]];
    grid[coord1[0]][coord1[1]] = grid[coord2[0]][coord2[1]];
    grid[coord2[0]][coord2[1]] = temp;

}


bool horizontalCheck(int row, int col, int matchCoords[]){

    bool endRun = false;

    int start = col, c = start;

    while(!endRun){
        
        c++;
        endRun = (c == cols) || (grid[row][c] != grid[row][start]);

    }

    if (endRun && c < cols){

        matchCoords[0] = start;
        matchCoords[1] = c;

        return true; 

    }else {

        return false; // no match found 
    }


}


void replaceMatchedRow(int row, int colCoords[]){

    int matchType = 0, length = colCoords[1]-colCoords[0];

    switch (length)
    {
    
    //replace with empty cell
    case 3:

        matchType = 1;
        grid[row][colCoords[0]] = 8;
        break;
    
    // replace with 2x2 candy
    case 4:

        matchType = 2;
        grid[row][colCoords[0]] = 6;
        break;
    
    // replace with row removing candy
    default:

        matchType = 3;
        grid[row][colCoords[0]] = 7;
        break;

    }

    

    // replace each grid value to that of an empty cell
    for(int c = colCoords[0] + 1; c <= colCoords[1]; c++){
        
        grid[row][c] = 8;

    }

}


// returns true when the first matched is found and replaces it with fresh cells
bool handleAndCheckMatched(){


    int coords[] = {-1, -1}; // used to store the coords of the row to replace 

    bool matched = false, endRun = false;
    int length;

    for(int r = 0; r < rows; r++){

        for (int c = 0; c < cols; c++){

            if(horizontalCheck(r, c, coords)){

                if ((coords[1] - coords[0]) >= 3){
                    
                    replaceMatchedRow(r,coords);
                    return true;
                }

            }

        }

    }

    return false;
}


// tells whether or not move made was valid 
bool validateMove(){

    bool valid = false;
    // continue running until no matches found
    while(bool run = handleAndCheckMatched()){

        valid = true;

    }

    return valid;
}


void makeMove(int cell[], int selectedCell[]){

    //swapping
    swapCells(cell, selectedCell);
    
    if(!validateMove()){

        // return to previous state
        swapCells(cell, selectedCell);

    }else {

        moves--;
        //render screen
        score++;

    }


}


bool isInGrid(sf::Vector2f mousePos){

    return gridElement.getGlobalBounds().contains(mousePos);

}



void inputHandleGrid(sf::Vector2f mousePos){

    for (int i = 0; i < rows; i++){

        for (int j = 0; j < cols; j++){

            if(spriteGrid[i][j]->getGlobalBounds().contains(mousePos)){

                // if first move select the cell
                if (!selected){

                    selected = true;
                    selectedCell[0] = i; // row
                    selectedCell[1] = j; // col

                }else {

                    int cell[] = {i, j};

                    makeMove(cell, selectedCell);

                    // returning to default state
                    selected = false;
                    selectedCell[0] = -1; // row
                    selectedCell[1] = -1; // col

                }
                

            }

        }   

    }

}



void initSprites(){

    for (int row = 0; row < rows; row++){

        for (int c = 0; c < cols; c++){
            spriteGrid[row][c] = new sf::Sprite(textureArray[8]);
        }
    }

}

// called before mainloop is initialized
bool initLevel1(){

    cout << " initialzied level 1" << endl;
    bool valid = true;

    initGrid(grid, 8);
    cout << grid[0][1] << endl;
    initSprites();
    cout << "initialized sprites for level 1" << endl;
    return valid;
}

// creates the inside of my grid
sf::RenderTexture createGridTexture(int grid[8][8]){

    sf::RenderTexture gridRT({length, width}); // the texture

    // using the grid array
    for (int i = 0; i < rows; i++){

        for (int j = 0; j < cols; j++){

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
            
            // spriteGrid[i][j]->setTexture(textureArray[textureNum]);
            // spriteGrid[i][j]->setScale({(cellSize / textureArray[textureNum].getSize().x), (cellSize / textureArray[textureNum].getSize().y)});
            // sf::Vector2f pos {(j*cellSize), (i*cellSize)}; // position vector for the new cell
            // spriteGrid[i][j]->setPosition(pos);

            sf::Sprite temp(textureArray[textureNum]);
            temp.setScale({(cellSize / textureArray[textureNum].getSize().x), (cellSize / textureArray[textureNum].getSize().y)});
            sf::Vector2f pos {(j*cellSize), (i*cellSize)}; // position vector for the new cell
            temp.setPosition(pos);
            *spriteGrid[i][j] = temp;
            gridRT.draw(temp);

        }

    }

    gridRT.display();
    return gridRT;
}

void drawLvl1Screen(sf::RenderWindow& window){
    

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

    sf::RenderTexture gridRT = createGridTexture(grid);
    gridRT.display();
    // drawing the grid
    
    gridElement = sf::Sprite(gridRT.getTexture());

    center = gridElement.getLocalBounds().size / 2.f;
    gridElement.setOrigin(center);
    gridElement.setPosition({(window.getSize().x / 2.f), (prev + margin + center.y)});

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
    string scoreString = "score: " + std::to_string(score);
    scoreText.setString(scoreString);
    scoreText.setCharacterSize(25);
    scoreText.setFillColor(sf::Color::White);

    center = scoreText.getLocalBounds().size / 2.f;
    scoreText.setOrigin(center);

    scoreText.setPosition(sf::Vector2f{50.f , prev});
    sf::Sprite checkCandy = sf::Sprite(gridRT.getTexture());
    checkCandy.setPosition(sf::Vector2f(100.f, 200.f));

    window.draw(title);
    window.draw(backBtnLvl1);
    window.draw(movesText);
    window.draw(scoreText);
    window.draw(gridElement);
    // window.draw(checkCandy);

}

void Lvl1ScreenInputHandling(sf::RenderWindow& window, int& index){

    sf::Vector2i temp = sf::Mouse::getPosition(window);

    //convert that into coords
    sf::Vector2f mousePos = window.mapPixelToCoords(temp);

    // back btn
    if(backBtnLvl1.getGlobalBounds().contains(mousePos)){

        index = 1; // save and exit option later

    }else if(isInGrid(mousePos)){
        
        inputHandleGrid(mousePos);

    }

}   
