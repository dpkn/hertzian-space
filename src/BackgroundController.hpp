//
//  backgroundController.hpp
//  hertzianSpace
//

#pragma once

#include <stdio.h>
#include "ofMain.h"

class BackgroundController {
public:
    void setup();
    void reset();
    void update();
    void draw();
    
    int mode;
    int counter;
    int fadeSpeed;
    int brightness;
};
