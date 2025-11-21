#include <SFML/Window.hpp>

int main()
{

    // test to see if sfml is working
    sf::Window window(sf::VideoMode({800, 600}), "Sugar Rush", sf::Style::Default, sf::State::Fullscreen);
    window.setFramerateLimit(60);

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


            window.display();
            

        }
    }
}