//
//  SceneManager.hpp
//  hertzian-space
//
//  Created by Daniël Korssen on 05/09/2020.
//

#pragma once
#include <stdio.h>
#include "ofMain.h"

class SceneManager {
    public:
    SceneManager();
    int activeScene;
    int startedAt;
    int getSceneProgress();
    
    void startScene(int scene);
};
