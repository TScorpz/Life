
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

#include <stdlib.h>
#include <time.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "ResourcePath.hpp"
#include "Network.hpp"
#include "Organism.hpp"
#include "map.hpp"
//#include "Engine.hpp"
#include "functions.hpp"

#include "Settings.hpp"

int main(int, char const**)
{
    srand(time(NULL));
    
    //load map
    Map map;
    
    //create creatures
    std::vector<Organism> myPop;
    
    for(int i = 0; i < INIT_POP_SIZE; i++)
    {
        Organism tempOrg(&map);
        myPop.push_back(tempOrg);
    }
    
    /*for(int j = 0; j < 3; j++)
    {
        for(int i = 0; i < BRAIN_SIZE; i++)
        {
            std::cout << myPop[j].getBrainCell(i) << " ";
        }
        std::cout << "\n";
    }*/
    
    //output organism positions
    /*std::cout << "\n\n";
    for(int i = 0; i < INIT_POP_SIZE; i++)
    {
        std::cout << i << ": " << myPop[i].getPos().x << " " << myPop[i].getPos().y << "\n";
    }*/
    
    //output updated map with organisms to console
    /*for(int y = 0; y < MAP_HEIGHT; y++)
    {
        for(int x = 0; x < MAP_WIDTH; x++)
        {
            std::cout << map.getTileType(y * MAP_WIDTH + x) << " ";
        }
        std::cout << "\n";
    }*/
    
    //squar.update();
    
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1000, 650), "SFML window");
    window.setFramerateLimit(20);

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    sf::Text text("Hello SFML", font, 50);
    text.setFillColor(sf::Color::White);

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
        for(int i = 0; i < INIT_POP_SIZE; i++)
        {
            myPop[i].update(&map);
        }
        
        // Clear screen
        window.clear();

        // Draw the string
        //window.draw(text);
        
        //window.draw(map);
        
        for(int i = 0; i < INIT_POP_SIZE; i++)
        {
            if(myPop[i].isAlive())
            {
                window.draw(myPop[i]);
            }
        }

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
