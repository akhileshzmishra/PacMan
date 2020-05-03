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

void GameManager::setPosition(const Position &p){
    mBBox.referencePos = p;
}

void GameManager::create(){
    mBluePrint = ObjectFactory::getNewBluePrint();
    Settings::getInstance()->setBluePrint(mBluePrint);
    mDisplay = ObjectFactory::getMapDisplay(mBluePrint);
    mDisplay->create();
    mGhostWorker = ObjectFactory::getGhostWorker(mBluePrint);

    GameState* st = nullptr;
    for(size_t i = 0; i < mBluePrint->getRow(); i++){
        for(size_t j = 0; j < mBluePrint->getCol(); j++){
            Coordinates coord(i, j);
            auto square = mDisplay->getSquare(coord);
            if(mBluePrint->isGhost(coord) && square){
        
                auto ghost = ObjectFactory::getGhost();
                ghost->create();
                ghost->setCoordinates(coord);
                ghost->setCurrentSquare(square);
                ghost->setBoard(mDisplay);
                mGhostWorker->addGhost(ghost);
                
            }
            if(mBluePrint->isPlayer(coord) && square){
                mPacMan.create();
                mPacMan.setCurrentSquare(square);
                mPacMan.setBoard(mDisplay);
                mPacMan.setCoordinates(coord);
            }
        }
    }
    mGhostWorker->create();
    st = mGhostWorker->getState();
    mPacMan.setState(st);
}

void GameManager::destroy(){
    if(mDisplay){
        mDisplay->destroy();
    }
    if(mGhostWorker){
        mGhostWorker->destroy();
    }
    mGhostWorker = nullptr;
    mDisplay = nullptr;
}

void GameManager::play(){
    mPacMan.work();
    if(mGhostWorker){
        mGhostWorker->work();
    }
}

