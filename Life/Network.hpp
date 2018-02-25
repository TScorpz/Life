//
//  Network.hpp
//  BPN
//
//  Created by Ogis on 13/02/2018.
//  Copyright © 2018 Ogis. All rights reserved.
//

#ifndef Network_hpp
#define Network_hpp

#include <stdio.h>
#include <vector>

class Network
{
public:
    Network();
    
    int inputNum;
    int hiddenNum;
    int outputNum;
    
    std::vector<float> input_neurons;
    std::vector<float> hidden_neurons_not_activated;
    std::vector<float> hidden_neurons_activated;
    std::vector<float> output_neurons;
    std::vector<float> target_neurons;
    
    std::vector<float> weights_input_hidden;
    std::vector<float> weights_hidden_output;
    
    void initNetwork();
    void forward();
    void back();
    void adjustWeights(float delta);
    void setTarget(float target);
private:
};

#endif /* Network_hpp */
