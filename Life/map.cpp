//
//  map.cpp
//  Life
//
//  Created by Ogis on 18/02/2018.
//  Copyright © 2018 Ogis. All rights reserved.
//

#include "map.hpp"

Map::Map(){
    for(int i = 0; i < MAP_HEIGHT; i++){
        for(int j = 0; j < MAP_WIDTH; j++){
            if(i == 0 || i == MAP_HEIGHT - 1 || j == 0 || j == MAP_WIDTH - 1){
                m_map[i * MAP_WIDTH + j].setType(1);
            }
            else{
                int wall = rand() % 100;
                if(wall < 10){
                    m_map[i * MAP_WIDTH + j].setType(3);
                }
                else{
                    m_map[i * MAP_WIDTH + j].setType(0);
                }
            }
        }
    }
    
    //output map to console
    /*for(int i = 0; i < MAP_HEIGHT; i++){
        for(int j = 0; j < MAP_WIDTH; j++){
            std::cout << m_map[i * MAP_WIDTH + j].getType() << " ";
        }
        std::cout << "\n";
    }*/
}

int Map::inspectTile(sf::Vector2f pos)
{
    return m_map[li::ctoi(pos)].getType();
}

int Map::getTileType(int index)
{
    return m_map[index].getType();
}

void Map::setTileType(int index, int type)
{
    m_map[index].setType(type);
}

void Map::genFood()
{
    bool ready = false;
    do{
        int pos = rand() % (MAP_WIDTH * MAP_HEIGHT);
        if(m_map[pos].getType() == 0)
        {
            m_map[pos].setType(3);
            ready = true;
        }
    }while(!ready);
    
}
