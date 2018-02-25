//
//  Tile.cpp
//  Life
//
//  Created by Ogis on 18/02/2018.
//  Copyright © 2018 Ogis. All rights reserved.
//

#include "Tile.hpp"

Tile::Tile(int type, float size)
{
    m_size = size;
    m_type = type;
    m_shape.setSize(sf::Vector2f(size, size));
    
    switch(type)
    {
        case 0:
        {
            m_shape.setFillColor(sf::Color(30, 30, 30));
            break;
        }
        case 1:
        {
            m_shape.setFillColor(sf::Color(60, 60, 60));
            break;
        }
    };
}

int Tile::getType()
{
    return m_type;
}

float Tile::getSize()
{
    return m_size;
}

void Tile::setType(int type)
{
    m_type = type;
}

void Tile::setSize(float size)
{
    m_size = size;
}
