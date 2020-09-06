//
//  SceneManager.cpp
//  hertzian-space
//
//  Created by Daniël Korssen on 05/09/2020.
//

#include "SceneManager.hpp"

SceneManager::SceneManager(){
    startScene(2);
}

void SceneManager::startScene(int scene){
    activeScene = scene;
    startedAt = ofGetElapsedTimeMillis();
}

int SceneManager::getSceneProgress(){
    return ofGetElapsedTimeMillis() - startedAt;
}
