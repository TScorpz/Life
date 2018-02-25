//
//  Engine.hpp
//  Life
//
//  Created by Ogis on 19/02/2018.
//  Copyright © 2018 Ogis. All rights reserved.
//

#ifndef Engine_hpp
#define Engine_hpp

#include <stdio.h>
#include <vector>

#include "map.hpp"
#include "Organism.hpp"
#include "Settings.hpp"

class Engine
{
public:
    Engine();
    void start();
protected:
    Map map;
    std::vector<Organism> myPop;
};

#endif /* Engine_hpp */
