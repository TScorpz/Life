//
//  Organism.cpp
//  Life
//
//  Created by Ogis on 18/02/2018.
//  Copyright © 2018 Ogis. All rights reserved.
//

#include "ResourcePath.hpp"
#include "Organism.hpp"
#include "functions.hpp"

Organism::Organism(Map *map)
{
    body.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    int color = rand() % 150 + 100;
    body.setFillColor(sf::Color(0, 0, color));
    //spawn at random tile
    bool spawned = false;
    do{
        int position = rand() % (MAP_WIDTH * MAP_HEIGHT);
        if(map->getTileType(position) == 0)
        {
            map->setTileType(position, 2);
            body.setPosition(li::itoc(position));
            spawned = true;
        }
    }while(!spawned);
    
    m_alive = true;
    m_life = 30;
    m_fitness = 0;
    
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    fitnessScore.setFont(font);
    fitnessScore.setCharacterSize(12);
    //fitnessScore.setString(sf::String(std::to_string(m_fitness)));
    fitnessScore.setString("lala");
    //center text
    li::center_out(fitnessScore, body);
    
    for(int i = 0; i < BRAIN_SIZE; i++)
    {
        m_brain[i] = rand() % 64;
    }
}

int Organism::getLife()
{
    return m_life;
}

sf::Vector2f Organism::getPos()
{
    return body.getPosition();
}

void Organism::decHealth()
{
    m_life--;
    if(m_life < 1)
    {
        m_alive = false;
    }
}

void Organism::incHealth()
{
    m_life++;
    //add max health
}

void Organism::eat(sf::Vector2f dir)
{
    /*lala
    if(body.getPosition())
    {
    }*/
}

int Organism::tryStepping(sf::Vector2f pos, int tileType)
{
    switch (tileType) {
        //if empty then go
        case 0:
        {
            body.setPosition(pos);
            decHealth();
            return 1;
        }
        //if wall then incr currStep by 2
        case 1:
        {
            return 2;
        }
        //if bot then incr currStep by 3
        case 2:
        {
            return 3;
        }
        //if food then incr currStep by 4
        case 3:
        {
            return 4;
        }
        //if relative bot then incr currStep by 5
        case 4:
        {
            return 5;
        }
    }
}

int Organism::eat(sf::Vector2f dir, int tileType)
{
    switch (tileType) {
        //if wall then incr currStep by 1
        case 0 ... 1:
        {
            return 1;
        }
        //if bot then incr currStep by 2
        case 2:
        {
            return 2;
        }
        //if food then eat it
        case 3:
        {
            m_life += 10;
            decHealth();
            return 3;
        }
        //if relative bot then do smth
        case 4:
        {
            return 4;
        }
    }
}

bool Organism::isAlive()
{
    return m_alive;
}

void Organism::update(Map *map)
{
    //check if alive
    if(!m_alive)
        return;
    
    static int currStep = 0;
    //std::cout << "Life:\t" << m_life << "  Step:\t" << currStep << "\n";
    //std::cout << "currStep = " << currStep << "\n";
    /*std::cout << inspectTile(sf::Vector2f(64, 128)) << "\n";
    std::cout << "Current step: " << currStep++ << "\n";*/
    
    //int dir = rand() % 8;
    sf::Vector2f pos = body.getPosition();
    switch (m_brain[currStep]) {
        //go N
        case 0:
        {
            pos.y -= CELL_SIZE;
            int targetTileType = map->inspectTile(pos);
            int stepInc = tryStepping(pos, targetTileType);
            currStep +=stepInc;
            currStep %= BRAIN_SIZE;
            break;
        }
        //go NE
        case 1:
        {
            pos.x += CELL_SIZE;
            pos.y -= CELL_SIZE;
            int targetTileType = map->inspectTile(pos);
            int stepInc = tryStepping(pos, targetTileType);
            currStep +=stepInc;
            currStep %= BRAIN_SIZE;
            break;
        }
        //go E
        case 2:
        {
            pos.x += CELL_SIZE;
            int targetTileType = map->inspectTile(pos);
            int stepInc = tryStepping(pos, targetTileType);
            currStep +=stepInc;
            currStep %= BRAIN_SIZE;
            break;
        }
        //go SE
        case 3:
        {
            pos.x += CELL_SIZE;
            pos.y += CELL_SIZE;
            int targetTileType = map->inspectTile(pos);
            int stepInc = tryStepping(pos, targetTileType);
            currStep +=stepInc;
            currStep %= BRAIN_SIZE;
            break;
        }
        //go S
        case 4:
        {
            pos.y += CELL_SIZE;
            int targetTileType = map->inspectTile(pos);
            int stepInc = tryStepping(pos, targetTileType);
            currStep +=stepInc;
            currStep %= BRAIN_SIZE;
            break;
        }
        //go SW
        case 5:
        {
            pos.x -= CELL_SIZE;
            pos.y += CELL_SIZE;
            int targetTileType = map->inspectTile(pos);
            int stepInc = tryStepping(pos, targetTileType);
            currStep +=stepInc;
            currStep %= BRAIN_SIZE;
            break;
        }
        //go W
        case 6:
        {
            pos.x -= CELL_SIZE;
            int targetTileType = map->inspectTile(pos);
            int stepInc = tryStepping(pos, targetTileType);
            currStep +=stepInc;
            currStep %= BRAIN_SIZE;
            break;
        }
        //go NW
        case 7:
        {
            pos.x -= CELL_SIZE;
            pos.y -= CELL_SIZE;
            int targetTileType = map->inspectTile(pos);
            int stepInc = tryStepping(pos, targetTileType);
            currStep += stepInc;
            currStep %= BRAIN_SIZE;
            break;
        }
        //eat N
        case 8:
        {
            sf::Vector2f dir = body.getPosition();
            dir.y -= CELL_SIZE;
            int targetTileType = map->inspectTile(dir);
            int result = eat(dir, targetTileType);
            if(result == 3) {//if food then delete it from map
                map->setTileType(li::ctoi(dir), 0);
            }
            currStep += result;
            break;
        }
        //eat NE
        case 9:
        {
            sf::Vector2f dir = body.getPosition();
            dir.y -= CELL_SIZE;
            dir.x += CELL_SIZE;
            int targetTileType = map->inspectTile(dir);
            int result = eat(dir, targetTileType);
            if(result == 3) {//if food then delete it from map
                map->setTileType(li::ctoi(dir), 0);
            }
            currStep += result;
            break;
        }
        //eat E
        case 10:
        {
            sf::Vector2f dir = body.getPosition();
            dir.x += CELL_SIZE;
            int targetTileType = map->inspectTile(dir);
            int result = eat(dir, targetTileType);
            if(result == 3) {//if food then delete it from map
                map->setTileType(li::ctoi(dir), 0);
            }
            currStep += result;
            break;
        }
        //eat SE
        case 11:
        {
            sf::Vector2f dir = body.getPosition();
            dir.x += CELL_SIZE;
            dir.y += CELL_SIZE;
            int targetTileType = map->inspectTile(dir);
            int result = eat(dir, targetTileType);
            if(result == 3) {//if food then delete it from map
                map->setTileType(li::ctoi(dir), 0);
            }
            currStep += result;
            break;
        }
        //eat S
        case 12:
        {
            sf::Vector2f dir = body.getPosition();
            dir.y += CELL_SIZE;
            int targetTileType = map->inspectTile(dir);
            int result = eat(dir, targetTileType);
            if(result == 3) {//if food then delete it from map
                map->setTileType(li::ctoi(dir), 0);
            }
            currStep += result;
            break;
        }
        //eat SW
        case 13:
        {
            sf::Vector2f dir = body.getPosition();
            dir.x -= CELL_SIZE;
            dir.y += CELL_SIZE;
            int targetTileType = map->inspectTile(dir);
            int result = eat(dir, targetTileType);
            if(result == 3) {//if food then delete it from map
                map->setTileType(li::ctoi(dir), 0);
            }
            currStep += result;
            break;
        }
        //eat W
        case 14:
        {
            sf::Vector2f dir = body.getPosition();
            dir.x -= CELL_SIZE;
            int targetTileType = map->inspectTile(dir);
            int result = eat(dir, targetTileType);
            if(result == 3) {//if food then delete it from map
                map->setTileType(li::ctoi(dir), 0);
            }
            currStep += result;
            break;
        }
        //eat NW
        case 15:
        {
            sf::Vector2f dir = body.getPosition();
            dir.x -= CELL_SIZE;
            dir.y -= CELL_SIZE;
            int targetTileType = map->inspectTile(dir);
            int result = eat(dir, targetTileType);
            if(result == 3) {//if food then delete it from map
                map->setTileType(li::ctoi(dir), 0);
            }
            currStep += result;
            break;
        }
        default:
        {
            break;
        }
        //calculate fitness depending on health and steps made
    }
    currStep++;
    if(currStep >= BRAIN_SIZE)
        currStep = 0;
}
