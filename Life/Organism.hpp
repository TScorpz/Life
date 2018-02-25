//
//  Organism.hpp
//  Life
//
//  Created by Ogis on 18/02/2018.
//  Copyright © 2018 Ogis. All rights reserved.
//

#ifndef Organism_hpp
#define Organism_hpp

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "map.hpp"
#include "Settings.hpp"

#endif /* Organism_hpp */

class Organism : public sf::Drawable, public sf::Transformable//, protected Map
{
public:
    Organism(Map *map);
    int getLife();
    sf::Vector2f getPos();
    void decHealth();
    void incHealth();
    void eat(sf::Vector2f dir);
    int tryStepping(sf::Vector2f pos, int tileType);
    int eat(sf::Vector2f dir, int tileType);
    bool isAlive();
    void update(Map *map);
protected:
    bool m_alive;
    int m_life;
    int m_fitness;
    int m_brain[BRAIN_SIZE];
    
    sf::Font font;
    sf::Text fitnessScore;
    
    sf::RectangleShape body;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        target.draw(body, states);
        //target.draw(fitnessScore, states);
    }
};
