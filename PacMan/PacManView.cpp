//
//  PacManView.cpp
//  PacMan
//
//  Created by Akhilesh Mishra on 01/05/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#include "PacManView.hpp"
#include "Settings.hpp"
#include "PlayBoard.hpp"
#include "PacManFrame.hpp"

using namespace pacman;
using namespace pacman::impl;

PacManView::PacManView(){
}

void PacManView::run(){
    mFrame = std::make_shared<PacManFrame>();
    auto frame = std::dynamic_pointer_cast<IBaseFrame>(mFrame);
    if(frame){
        Settings::getInstance()->setBaseFrame(frame);
    }
    createMap();
    if(mFrame){
        mFrame->run();
    }
    destroyMap();
}

void PacManView::createMap(){
    mPlayBoard = std::make_shared<PlayBoard>();
    mPlayBoard->create();
    mFrame->addToList(mPlayBoard);
}

void PacManView::destroyMap(){
    if(mPlayBoard){
        mPlayBoard->destroy();
        mPlayBoard = nullptr;
    }
}


PacManView::~PacManView(){
    mFrame->destroy();
    mPlayBoard = nullptr;
}
