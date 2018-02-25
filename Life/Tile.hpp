//
//  Tile.hpp
//  Life
//
//  Created by Ogis on 18/02/2018.
//  Copyright © 2018 Ogis. All rights reserved.
//

#ifndef Tile_hpp
#define Tile_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

#include "Settings.hpp"

class Tile
{
public:
    Tile(int type = 0, float size = CELL_SIZE);
    
    int getType();
    float getSize();
    
    void setType(int type);
    void setSize(float size);
private:
protected:
    float m_size;
    int m_type;
    sf::RectangleShape m_shape;
};

#endif /* Tile_hpp */
