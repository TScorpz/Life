//
//  functions.hpp
//  Life
//
//  Created by Ogis on 18/02/2018.
//  Copyright © 2018 Ogis. All rights reserved.
//

#ifndef functions_hpp
#define functions_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

#include "Settings.hpp"

namespace li
{
    //convert map coordinates to array index
    int ctoi(sf::Vector2f pos);
    
    //convert array index to map coordinates
    sf::Vector2f itoc(int index);
    
    //center text
    void center_out(sf::Text &value, sf::RectangleShape &container);
}

#endif /* functions_hpp */
