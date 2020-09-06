//
//  WifiReader.hpp
//  hertzianSpace
//
//  Created by Daniël Korssen on 03/09/2020.
//

#pragma once

#include <stdio.h>
#include "ofMain.h"

struct WifiNetwork
{
    std::string ssid;
    std::string id;
    std::string strength;
    std::string security;
    
     WifiNetwork(std::array<std::string, 4>& _array)
        : ssid(_array[0])
        , id(_array[1])
        , strength(_array[2])
        , security(_array[3])
    {
    }
};

class WifiReader {
public:
    std::vector<WifiNetwork> networks;
    std::string executeCommand(const std::string& command);
    void getNetworks();
    void addNetwork(std::array<std::string, 4> _network);
};
