#include "common.hpp"
#include "Lvl2.hpp"

// ----------------------------- NECESSARY DATA ----------------------------

// used for input handling 
static bool selected = false;
static int selectedCell[] = {-1, -1}; // unselected state is -1, -1


static bool lvlEnd;
// imp data
static int moves = 20, margin = 50; 

// used to tell if mouse was clicked in the previous frame (input handling ma use hona)
static bool mousePressedLastFrame = false;


static sf::Text backBtnlvl2(globalFont);
static sf::Text movesText(globalFont);
static sf::Text scoreText(globalFont);
static sf::Sprite gridElement(textureArray[8]);
static sf::Text exitBtn(globalFont);

static sf::RenderTexture gridRT({length, width});

// ------------------ Functions---------------------------- 

// called before mainloop is initialized
bool initLevel2(){

    moves = 30;
    bool valid = true;
    requiredScore = 4000;

    // assign its grid values
    initGrid(grid, 8);

    initSprites(spriteGrid); // no chance for failure really (no exception needed)

    // removes any and all matches
    prepareGrid(grid, ROWS, COLS);

    // level is active
    isActive = true;
    lvlEnd = false;
    
    score = 0;
    cout << "initialized level 2" << endl;

    return valid;
}


void drawLvl2Screen(sf::RenderWindow& window){
    
    updateGrid(grid, ROWS);

    float prev = 0.f;


    // title of the page
    sf::Text title(globalFont);
    title.setString("Level 2");
    title.setCharacterSize(60);
    title.setFillColor(sf::Color(191, 78, 48)); 

    // centering the title text
    auto center = title.getLocalBounds().size / 2.f;
    title.setOrigin(center);
    title.setPosition(sf::Vector2f{(window.getSize().x / 2.f), (center.y + margin)});

    prev += title.getLocalBounds().size.y + margin;

    createGridTexture(grid, gridRT, spriteGrid);

    // drawing the grid
    gridElement = sf::Sprite(gridRT.getTexture());

    center = gridElement.getLocalBounds().size / 2.f;
    gridElement.setOrigin(center);
    gridElement.setPosition({(window.getSize().x / 2.f), (prev + margin + center.y + 50)});

    prev = margin;

    // backBtnlvl2
    backBtnlvl2.setString("back");
    backBtnlvl2.setCharacterSize(25);
    backBtnlvl2.setFillColor(sf::Color::White);

    center = backBtnlvl2.getLocalBounds().size / 2.f;
    backBtnlvl2.setOrigin(center);

    backBtnlvl2.setPosition(sf::Vector2f{50.f , 10.f});

    prev += backBtnlvl2.getLocalBounds().size.y + margin;

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
    window.draw(backBtnlvl2);
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


static void inputHandleGrid(sf::Vector2f mousePos, sf::RenderWindow& window, int& index) {

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

                createGridTexture(grid, gridRT,spriteGrid);
                gridElement = sf::Sprite(gridRT.getTexture());

                if(isWithin1(grid, cell, selectedCell)){
                    
                    // if not valid
                    if (!isMoveValid(grid)) {

                        swapCells(cell, selectedCell, grid);

                    } 
                    else {
                        
                        updateGrid(grid, ROWS);

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


void Lvl2ScreenInputHandling(sf::RenderWindow& window, int& index){

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

    }else if(backBtnlvl2.getGlobalBounds().contains(mousePos)){
        selected = false;
        index = 1; // save and exit option later
        return;
    
    }else {

        sf::Vector2f gridTopLeft = gridElement.getPosition() - gridElement.getOrigin();
        sf::Vector2f local = mousePos - gridTopLeft;

        if(isInGrid(local, spriteGrid)){
            inputHandleGrid(local, window, index);

        }
        
        

    }

}   


