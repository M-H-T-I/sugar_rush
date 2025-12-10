#include "common.hpp"
#include "Tutorial.hpp"

// ----------------------------- NECESSARY DATA ----------------------------

// used for input handling 
static bool selected = false;
static int selectedCell[] = {-1, -1}; // unselected state is -1, -1

static bool openGuide = false;
// used to tell if game has started. Used in preparing the level

static bool lvlEnd;
// imp data
static int moves = 20, margin = 50; 

// used to tell if mouse was clicked in the previous frame (input handling ma use hona)
static bool mousePressedLastFrame = false;


static sf::Text backBtntutorial(globalFont);
static sf::Text openGuideBtn(globalFont);
sf::Text exitBtnGuide(globalFont);
static sf::Sprite gridElement(textureArray[8]);
static sf::Text exitBtn(globalFont);

static sf::RenderTexture gridRT({length, width});


// ------------------ Functions---------------------------- 


void drawGuide(sf::RenderWindow& window){

    float prev = 10.f;

    sf::Vector2f tempSize(window.getSize().x , static_cast<float>(window.getSize().y));

    sf::RectangleShape rect(tempSize);
    auto center =rect.getLocalBounds().size / 2.f;
    rect.setOrigin(center);
    rect.setPosition({(window.getSize().x / 2.f ), (window.getSize().y/2.f)});
    rect.setFillColor(sf::Color::Black);

    exitBtnGuide.setCharacterSize(20);
    exitBtnGuide.setString("[ Close Guide ]");
    center = exitBtnGuide.getLocalBounds().size / 2.f;
    exitBtnGuide.setOrigin(center);
    exitBtnGuide.setPosition({center.x , prev});

    prev += margin + exitBtnGuide.getLocalBounds().size.y ;

    sf::Text guideTitle(globalFont);
    guideTitle.setString("Guide");
    guideTitle.setCharacterSize(52.f);
    center = guideTitle.getLocalBounds().size / 2.f;
    guideTitle.setOrigin(center);
    guideTitle.setPosition({center.x , prev});

    prev += margin + guideTitle.getLocalBounds().size.y;

    sf::Text txt(globalFont);
    txt.setCharacterSize(22);            
    txt.setStyle(sf::Text::Bold);
    center = txt.getLocalBounds().size / 2.f;
    txt.setFillColor(sf::Color::White);
    txt.setOrigin(center);
    txt.setString("3 candies: match \n4 candies: match and exploding bomb \n5 candies: match and row bomb \nObjective: get the required score in the other levels. \n( Tutorial is inifinite (; )");

    txt.setPosition({(center.x + 10.f), prev});

    
    window.draw(rect);
    window.draw(exitBtnGuide);
    window.draw(guideTitle);
    window.draw(txt);


}


// called before mainloop is initialized
bool initTutorial(){

    moves = 20;
    bool valid = true;
    isAnimating = false;
    requiredScore = 2500;

    // assign its grid values
    initGrid(grid, 8);

    initSprites(spriteGrid); // no chance for failure really (no exception needed)

    // removes any and all matches
    prepareGrid(grid, ROWS, COLS);

    // level is active
    isActive = true;
    lvlEnd = false;

    score = 0;

    cout << "initialized level 1" << endl;

    return valid;
}


void drawTutorialScreen(sf::RenderWindow& window){
    
    float prev = 0.f;


    // title of the page
    sf::Text title(globalFont);
    title.setString("Tutorial");
    title.setCharacterSize(60);
    title.setFillColor(sf::Color(191, 78, 48)); 

    // centering the title text
    auto center = title.getLocalBounds().size / 2.f;
    title.setOrigin(center);
    title.setPosition(sf::Vector2f{(window.getSize().x / 2.f), (center.y + margin)});

    prev += title.getLocalBounds().size.y + margin;


    // guidebtn

    openGuideBtn.setString("[ Open Guide ] ");
    openGuideBtn.setCharacterSize(20);
    openGuideBtn.setFillColor(sf::Color::White);

    center = openGuideBtn.getLocalBounds().size / 2.f;
    openGuideBtn.setOrigin(center);

    openGuideBtn.setPosition(sf::Vector2f{center.x + 10.f , prev});

    prev += openGuideBtn.getLocalBounds().size.y ;

    createGridTexture(grid, gridRT, spriteGrid);

    // drawing the grid
    gridElement = sf::Sprite(gridRT.getTexture());

    center = gridElement.getLocalBounds().size / 2.f;
    gridElement.setOrigin(center);
    gridElement.setPosition({(window.getSize().x / 2.f), (prev + margin + center.y + 50)});

    prev = margin;

    // backBtntutorial
    backBtntutorial.setString("[ Go Back ]");
    backBtntutorial.setCharacterSize(25);
    backBtntutorial.setFillColor(sf::Color::White);

    center = backBtntutorial.getLocalBounds().size / 2.f;
    backBtntutorial.setOrigin(center);

    backBtntutorial.setPosition(sf::Vector2f{center.x + 10.f , 10.f});

    prev += backBtntutorial.getLocalBounds().size.y + margin;    
   

    window.draw(title);
    window.draw(backBtntutorial);
    window.draw(openGuideBtn);
    window.draw(gridElement);

    if(openGuide){

        drawGuide(window);

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

                    // if(grid[r][c] == 6){
                    //     int coords[] = {r,c};
                    //     explodingCandyHandler(grid, coords);
                    //     moves--;
                    //     return;
                        
                    // }

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

                createGridTexture(grid, gridRT, spriteGrid);
                gridElement = sf::Sprite(gridRT.getTexture());

                if(grid[selectedCell[0]][selectedCell[1]] == 7){
                    rowCandyHandler(grid, selectedCell);
                }else if(grid[cell[0]][cell[1]] == 7){
                    rowCandyHandler(grid,cell);

                }

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



void tutorialScreenInputHandling(sf::RenderWindow& window, int& index){

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

    }else if(backBtntutorial.getGlobalBounds().contains(mousePos) && !openGuide){
        selected = false;
        index = 1; // save and exit option later
        return;

    }else if(openGuideBtn.getGlobalBounds().contains(mousePos)){

        openGuide = true;

    }else if(exitBtnGuide.getGlobalBounds().contains(mousePos)){
        openGuide = false;
    }else {

        sf::Vector2f gridTopLeft = gridElement.getPosition() - gridElement.getOrigin();
        sf::Vector2f local = mousePos - gridTopLeft;

        if(isInGrid(local, spriteGrid) && !openGuide){
            inputHandleGrid(local, window, index);

        }
        
    }

}   


