//
//  ConcreteMap.cpp
//  PacMan
//
//  Created by Akhilesh Mishra on 29/04/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#include "PlayBoard.hpp"
#include "MapDisplay.hpp"

using namespace pacman;
using namespace pacman::impl;

PlayBoard::PlayBoard(){
    setUp();
}

void PlayBoard::display(){
    if(mDisplay){
        mDisplay->display();
    }
}

void PlayBoard::setPosition(const Position &p){
    mDimension.centroid = p;
}

void PlayBoard::setUp(){
    if(!mSetup){
        mDisplay = std::make_shared<MapDisplay>(mBluePrint);
        mSetup = true;
    }
}

void PlayBoard::start(){
    
}

void PlayBoard::end(){
    mDisplay = nullptr;
    mSetup = false;
}

void PlayBoard::setBaseFrame(IBaseFrame*  ptr){
    if(mDisplay){
        mDisplay->setBaseFrame(ptr);
    }
    IDisplay::setBaseFrame(ptr);
}
