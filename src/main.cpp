#include "common.hpp"
#include "TitleScreen.hpp"
#include "LvlSelector.hpp"

int main(){

    // initiaizing everything
    if(!loadAssets()) return -1;

    int index = 0;

    sf::Music music;

    // main window
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Sugar Rush", sf::Style::Default);

    // music
    if(!music.openFromFile("assets/sound/CandyCrushMusic.mp3") && window.isOpen()){
        cout << "COuld not open audio file" << endl;
        return -1;
    }else {
        music.setLooping(true);
        music.setVolume(20.f);
        music.play();
    }

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
                    titleScreenInputHandling(window, index);

                }

            }

            // changing view
            if (const auto* resized = event->getIf<sf::Event::Resized>()){

                // fixing the viewport
                sf::FloatRect visibleArea({0.f, 0.f}, sf::Vector2f(resized->size));
                window.setView(sf::View(visibleArea));

            }

            //checking state
            if(index == 0){
                drawTitleScreen(window);
            }else if(index == 1){
                drawLvlSelectorScreen(window);
            }

            window.display();

        }
    }

}