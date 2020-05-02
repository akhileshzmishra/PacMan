//
//  ConcreteMap.cpp
//  PacMan
//
//  Created by Akhilesh Mishra on 29/04/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#include "GameManager.hpp"
#include "MapDisplay.hpp"
#include "ObjectFactory.hpp"
#include "Settings.hpp"

using namespace pacman;
using namespace pacman::impl;

GameManager::GameManager(){
}

void GameManager::setupDisplay(){
    if(mDisplay){
        mDisplay->display();
    }
}

void GameManager::setPosition(const Position &p){
    mBBox.referencePos = p;
}

void GameManager::create(){
    mBluePrint = ObjectFactory::getNewBluePrint();
    Settings::getInstance()->setBluePrint(mBluePrint);
    mDisplay = ObjectFactory::getMapDisplay(mBluePrint);
    mDisplay->create();
}

void GameManager::destroy(){
    if(mDisplay){
        mDisplay->destroy();
    }
    mDisplay = nullptr;
}

void GameManager::startGame(){
}

