#include "common.hpp"
#include "TitleScreen.hpp"
#include "LvlSelector.hpp"
#include "Lvl1.hpp"
#include "Settings.hpp"
#include "Lvl2.hpp"
#include "Lvl3.hpp"
#include "Tutorial.hpp"

int main(){

    // initiaizing everything
    if(!loadAssets()){

        return -1;
        
    }

    initRandom(); // initializing seed

    int index = 0;


    // main window
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Sugar Rush", sf::Style::Default);

    window.setFramerateLimit(80);

    //checking

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>()){
                window.close();
            }

            if(const auto* clicked = event->getIf<sf::Event::MouseButtonPressed>()){

                if(clicked->button == sf::Mouse::Button::Left){

                    // check which state the game is in
                    if(index == 0){
                        titleScreenInputHandling(window, index);

                    }else if(index == 1){
                        lvlSelectorScreenInputHandling(window, index);
                    }else if(index == 2){
                        Lvl1ScreenInputHandling(window, index);
                    }else if(index == 3){

                        Lvl2ScreenInputHandling(window, index);
                    
                    }else if (index == 4){

                        Lvl3ScreenInputHandling(window, index);
                    
                    }else if(index == 5){

                        tutorialScreenInputHandling(window, index);

                    }else if(index == 6){

                        SettingsScreenInputHandling(window, index);
                        
                    }

                }

            }

            // changing view
            if (const auto* resized = event->getIf<sf::Event::Resized>()){

                // fixing the viewport
                sf::FloatRect visibleArea({0.f, 0.f}, sf::Vector2f(resized->size));
                window.setView(sf::View(visibleArea));

            }

        }   

            window.clear(sf::Color(60, 176, 205));


            //checking state
            if(index == 0){
                drawTitleScreen(window);
            }else if(index == 1){
                drawLvlSelectorScreen(window);
            }else if(index == 2){
                drawLvl1Screen(window);

            }else if(index == 3){
                drawLvl2Screen(window);
            
            }else if(index == 4){
                drawLvl3Screen(window);
            }else if(index == 5){
                drawTutorialScreen(window);
            
            }else if(index == 6){
                drawSettingsScreen(window);
            }

            updateGrid(grid, 8);

            window.display();

    }

}