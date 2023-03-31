#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    sf::CircleShape shape(50.f);

    // set the shape color to green
    shape.setFillColor(sf::Color(100, 250, 50));

    std::vector<sf::CircleShape> circles;

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;


        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::MouseButtonPressed){
                if(event.mouseButton.button == sf::Mouse::Left){
                    std::cout << "Wcisnieto lewy przycisk myszy" << std::endl;
                    std::cout << "x: " << event.mouseButton.x << std::endl;
                    std::cout << "y: " << event.mouseButton.y << std::endl;
                    shape.setPosition(event.mouseButton.x-50, event.mouseButton.y-50);
                    circles.push_back(shape);

                }
                while(event.mouseButton.button == sf::Mouse::Right){
                   std::cout << "Wcisnieto prawy przycisk myszy" << std::endl;
                   std::cout << "x: " << event.mouseButton.x << std::endl; std::cout << "y: " << event.mouseButton.y << std::endl;
                }
            }
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        for(auto circle:circles){
            window.draw(circle);
        }

        // draw everything here...
        shape.setPosition(0, 0);
        window.draw(shape);

        shape.setPosition(100, 100);
        window.draw(shape);

        // end the current frame
        window.display();
    }

    return 0;
}