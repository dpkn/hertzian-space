//
//  backgroundController.hpp
//  hertzianSpace
//

#ifndef BackgroundController_hpp
#define BackgroundController_hpp

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

#endif /* BackgroundController_hpp */
