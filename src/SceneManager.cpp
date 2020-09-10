//
//  SceneManager.cpp
//  hertzian-space
//
//  Created by Daniël Korssen on 05/09/2020.
//

#include "SceneManager.hpp"

SceneManager::SceneManager(){

}

void SceneManager::startScene(int scene){
    activeScene = scene;
    startedAt = ofGetElapsedTimeMillis();
    startedAtF = ofGetElapsedTimef();
}

int SceneManager::getSceneProgress(){
    return ofGetElapsedTimeMillis() - startedAt;
}

float SceneManager::getSceneProgressF(){
    return ofGetElapsedTimef() - startedAtF;
}
