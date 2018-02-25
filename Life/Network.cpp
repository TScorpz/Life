//
//  Network.cpp
//  BPN
//
//  Created by Ogis on 13/02/2018.
//  Copyright © 2018 Ogis. All rights reserved.
//

#include <iostream>
#include <time.h>
#include <math.h>
#include "Network.hpp"

Network::Network()
{
    srand(time(NULL));
    
    inputNum = 2;
    hiddenNum = 3;
    outputNum = 1;
}

void Network::initNetwork()
{
    input_neurons.resize(inputNum);
    hidden_neurons_not_activated.resize(hiddenNum);
    hidden_neurons_activated.resize(hiddenNum);
    output_neurons.resize(outputNum);
    target_neurons.resize(outputNum);
    
    weights_input_hidden.resize(inputNum * hiddenNum);
    weights_hidden_output.resize(hiddenNum * outputNum);
    
    //init weights
    std::cout << "Input->hidden neuron weights:\n";
    int vecSize = (int)weights_input_hidden.size();
    for(int i = 0; i < vecSize; i++)
    {
        weights_input_hidden[i] = rand() / (float)RAND_MAX;
        std::cout << i << "> " << weights_input_hidden[i] << "\n";
    }
    std::cout << "\nHidden->output neuron weights:\n";
    vecSize = (int)weights_hidden_output.size();
    for(int i = 0; i < vecSize; i++)
    {
        weights_hidden_output[i] = rand() / (float)RAND_MAX;
        std::cout << i << "> " <<  weights_hidden_output[i] << "\n";
    }
    
    int i = 1;
    do
    {
        forward();
        back();
        std::cout << "\n***** END OF EPOCH " << i << " *****\n";
        //std::cin.get();
        i++;
    }while(output_neurons[0] > 0.01);
}

void Network::forward()
{
    //input-hidden
    int vecSizeHidden = (int)hidden_neurons_activated.size();
    for(int i = 0; i < vecSizeHidden; i++)
    {
        float sum = 0;
        int vecSizeInput = (int)input_neurons.size();
        for(int j = 0; j < vecSizeInput; j++)
        {
            sum += 1 * weights_input_hidden[i * vecSizeInput + j];
        }
        hidden_neurons_not_activated[i] = sum;
        sum = 1 / (1 + exp(-sum));          //sigmoid function
        //sum = sum / (1 + abs(sum));       //fast sigmoid function(?)
        hidden_neurons_activated[i] = sum;
    }
    
    /*std::cout << "\nCalculated hidden neuron values:\n";
    for(int i = 0; i < vecSizeHidden; i++)
    {
        std::cout << i << "> " <<  hidden_neurons_activated[i] << "\n";
    }*/
    
    //hidden-output
    int vecSizeOutput = (int)output_neurons.size();
    for(int i = 0; i < vecSizeOutput; i++)
    {
        float sum = 0;
        int vecSizehidden = (int)hidden_neurons_activated.size();
        for(int j = 0; j < vecSizehidden; j++)
        {
            sum += hidden_neurons_activated[i] * weights_hidden_output[i * vecSizeOutput + j];
        }
        //sum = 1 / (1 + exp(-sum));          //sigmoid function
        sum = sum / (1 + abs(sum));       //fast sigmoid function(?)
        output_neurons[i] = sum;
    }
    
    std::cout << "\nCalculated output neuron values:\n";
    for(int i = 0; i < vecSizeOutput; i++)
    {
        std::cout << i << "> " <<  output_neurons[i] << "\n";
    }
}

void Network::back()
{
    float sum = 0;
    int vecSizeOutput = (int)output_neurons.size();
    for(int i = 0; i < vecSizeOutput; i++)
    {
        int vecSizehidden = (int)hidden_neurons_activated.size();
        for(int j = 0; j < vecSizehidden; j++)
        {
            sum += hidden_neurons_activated[j] * weights_hidden_output[i * vecSizeOutput + j];
        }
        
        float deltaOutputSum = (1 / (1 + exp(-sum))) * (1 - 1 / (1 + exp(-sum))) * (0 - output_neurons[i]);
        //sum = sum / (1 + abs(sum));           //fast sigmoid function(?)
        //replace "0" with target result
        //float deltaOutputSum = abs(-sum) * (0 - output_neurons[0]);     //fast sigmoid function derivative(?)
        std::cout << "\nDelta output sum:\n" << deltaOutputSum << "\n";
        adjustWeights(deltaOutputSum);
    }
    
    
}

void Network::adjustWeights(float delta)
{
    float *deltaWeights = new float[hiddenNum];
    //std::cout << "\nCalculated new hidden-output weights:";
    for(int i = 0; i < hiddenNum; i++)
    {
        float deltaWeight = 0;
        float deltaHiddenSum = 0;
        deltaHiddenSum = delta / weights_hidden_output[i] * (1 / (1 + exp(-hidden_neurons_not_activated[i]))) * (1 - 1 / (1 + exp(-hidden_neurons_not_activated[i])));
        //deltaHiddenSum = delta / weights_hidden_output[i] * abs(-hidden_neurons_not_activated[i]); //error
        deltaWeight = deltaHiddenSum / 1;
        for(int j = 0; j < inputNum; j++)
        {
            //std::cout << "\ndelta weight: " << deltaWeight << " -- weight: " << weights_input_hidden[i * inputNum + j] << "\t" << weights_hidden_output[i] << "\t" << abs(-hidden_neurons_not_activated[i]) << "\n";
            weights_input_hidden[i * inputNum + j] += deltaWeight;
            //std::cout << weights_input_hidden[i * inputNum + j] << "\n";
        }
        
        deltaWeights[i] = delta * weights_hidden_output[i];
        //std::cout << "\ndelta weight:\t" << deltaWeights[i];
        weights_hidden_output[i] += deltaWeights[i];
        //std::cout << "\nnew weight:\t\t" << weights_hidden_output[i];
    }
    delete []deltaWeights;
    
    
}

void Network::setTarget(float target)
{
    target_neurons[0] = target;
}
