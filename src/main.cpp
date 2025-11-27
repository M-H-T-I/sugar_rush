#include "common.hpp"
#include "TitleScreen.hpp"


int main(){

    // loading everything
    if(!loadAssets()) return -1;

    int index = 0;

    sf::Music music;

    // main window
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Sugar Rush", sf::Style::Default);

    // music
    if(!music.openFromFile("assets/sound/CandyCrushMusic.mp3")){
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

            cout << "State is: " << states[index] << endl;
            //checking state
            if(index == 0){
                drawTitleScreen(window);
            }

            window.display();

        }
    }

}