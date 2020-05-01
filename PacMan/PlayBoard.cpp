//
//  ConcreteMap.cpp
//  PacMan
//
//  Created by Akhilesh Mishra on 29/04/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#include "PlayBoard.hpp"
#include "MapDisplay.hpp"
#include "ObjectFactory.hpp"
#include "Settings.hpp"

using namespace pacman;
using namespace pacman::impl;

PlayBoard::PlayBoard(){
}

void PlayBoard::display(){
    if(mDisplay){
        mDisplay->display();
    }
}

void PlayBoard::setPosition(const Position &p){
    mDimension.centroid = p;
}

void PlayBoard::create(){
    if(!mSetup){
        mBluePrint = ObjectFactory::getNewBluePrint();
        Settings::getInstance()->setBluePrint(mBluePrint);
        mDisplay = ObjectFactory::getMapDisplay(mBluePrint);
        mDisplay->create();
        mSetup = true;
    }
}

void PlayBoard::destroy(){
    if(mDisplay){
        mDisplay->destroy();
    }
    mDisplay = nullptr;
    mSetup = false;
}

