#include "common.hpp"
#include "Lvl1.hpp"

// ----------------------------- NECESSARY DATA ----------------------------

bool selected = false;
int selectedCell[] = {-1, -1}; // unselected state is -1, -1
int matchType = 0;
bool isActive = false;
int moves = 20, score = 2450, requiredScore = 2500, margin = 50; 

bool mousePressedLastFrame = false;


sf::Text backBtnLvl1(globalFont);
sf::Text movesText(globalFont);
sf::Text scoreText(globalFont);
sf::Sprite gridElement(textureArray[8]);




// ---------------------------------------- GRID INFO ----------------------------------//

int grid[8][8];
sf::Sprite* spriteGrid[8][8]; // will save all the sprites so I dont have to do any calculations




// ------------------ Functions---------------------------- 

void swapWithAnimation(int grid[][8], int coord1[], int coord2[], sf::RenderWindow& window){
    
    // Redraw swapped grid
    createGridTexture(grid);
    window.clear();
    drawLvl1Screen(window); // your draw function
    window.display();

    // If move invalid, wait 0.5s and swap back
    if(!isMoveValid(grid)){
        sf::sleep(sf::seconds(0.5f));

        swapCells(coord1, coord2, grid);

        createGridTexture(grid);
        window.clear();
        drawLvl1Screen(window);
        window.display();
    }
}

bool isWon(sf::RenderWindow& window){

    sf::Text txt(globalFont);
    txt.setCharacterSize(64);               // adjust as needed
    txt.setStyle(sf::Text::Bold);
    txt.setFillColor(sf::Color::White);

    // Measure text and compute box size with padding
    sf::FloatRect tb = txt.getLocalBounds(); // left/top may be non-zero
    float paddingX = 40.f;
    float paddingY = 24.f;
    sf::Vector2f boxSize(tb.size.x + paddingX * 2.f, tb.size.y + paddingY * 2.f);

    // Center of the window
    sf::Vector2u winSize = window.getSize();
    sf::Vector2f center((float)winSize.x / 2.f, (float)winSize.y / 2.f);

    // Create the box
    sf::RectangleShape box(boxSize);
    box.setOrigin({boxSize.x / 2.f, boxSize.y / 2.f});
    box.setPosition(center);
    box.setFillColor(sf::Color(0, 0, 0, 180));      // semi-transparent black
    box.setOutlineColor(sf::Color(240, 200, 30));   // gold outline
    box.setOutlineThickness(4.f);

    // Position text centered inside the box (account for text local bounds)
    txt.setOrigin({(tb.position.x + tb.size.x / 2.f), (tb.position.y + tb.size.y / 2.f)});
    txt.setPosition(center);


    if(requiredScore <= score){
        txt.setString("You win");
        window.draw(box);
        window.draw(txt);
        return true;
    }else{
        txt.setString("You lose");
        window.draw(box);
        window.draw(txt);
        return false;
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

    bool valid = true;

    initGrid(grid, 8);
    initSprites();
    prepareGrid(grid, ROWS, COLS, isActive, score);

    isActive = true;

    cout << "initialized sprites for level 1" << endl;

    return valid;
}

// creates the inside of my grid
sf::RenderTexture createGridTexture(int grid[8][8]){

    sf::RenderTexture gridRT({length, width}); // the texture
    gridRT.clear(sf::Color::White);

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
            gridRT.draw(temp);

        }

    }
    gridRT.display();
    return gridRT;
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

    sf::RenderTexture gridRT = createGridTexture(grid);
    gridRT.display();
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
    string scoreString = "score: " + std::to_string(score);
    scoreText.setString(scoreString);
    scoreText.setCharacterSize(25);
    scoreText.setFillColor(sf::Color::White);

    center = scoreText.getLocalBounds().size / 2.f;
    scoreText.setOrigin(center);

    scoreText.setPosition(sf::Vector2f{50.f , prev});

    window.draw(title);
    window.draw(backBtnLvl1);
    window.draw(movesText);
    window.draw(scoreText);
    window.draw(gridElement);

}

// void outlineShape(sf::RenderWindow& window, sf::Vector2f mousePos){

//     for(int r = 0; r < rows; r++){

//         for (int c = 0; c < cols; c++){

//             if(spriteGrid[r][c]->getGlobalBounds().contains(mousePos)){

//                 sf::FloatRect rect = spriteGrid[r][c]->getGlobalBounds();
//                 sf::RectangleShape sel;
//                 sel.setPosition({rect.position.x, rect.position.y});
//                 sel.setSize({rect.size.x, rect.size.y});
//                 sel.setFillColor(sf::Color::Transparent);
//                 sel.setOutlineColor(sf::Color::Yellow);
//                 sel.setOutlineThickness(3.f);

//                 window.draw(sel);
//                 return;
                
//             }

//         }

//     }

// }

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
                        // explodingCandyHandler(grid, coords);
                        score += 250;
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

                sf::RenderTexture newRt = createGridTexture(grid);
                gridElement = sf::Sprite(newRt.getTexture());

                if(isWithin1(grid, cell, selectedCell)){
                    
                    // if not valid
                    if (!isMoveValid(grid)) {
                        cout << "invalid move";
                        // sf::sleep(sf::seconds(0.5f));
                        swapCells(cell, selectedCell, grid);
                    } 
                    else {
                        
                        updateGrid(grid, ROWS, isActive, score);

                        moves--;
                        score += 20;

                        if (isWon(window)){

                            window.display();
                            sf::sleep(sf::seconds(1.5f));
                            index = 2;

                        }
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


    // back btn
    if(backBtnLvl1.getGlobalBounds().contains(mousePos)){
        selected = false;
        index = 1; // save and exit option later

    }else {

        sf::Vector2f gridTopLeft = gridElement.getPosition() - gridElement.getOrigin();
        sf::Vector2f local = mousePos - gridTopLeft;

        if(isInGrid(local)){
            inputHandleGrid(local, window, index);

        }
        

    }

}   


