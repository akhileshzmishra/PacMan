//
//  PacManView.cpp
//  PacMan
//
//  Created by Akhilesh Mishra on 01/05/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#include "PacManView.hpp"
#include "Settings.hpp"
#include "GameManager.hpp"
#include "PacManFrame.hpp"

using namespace pacman;
using namespace pacman::impl;

PacManView::PacManView(){
}

void PacManView::run(){
    
    create();
    if(mFrame){
        mFrame->setGameManager(mGameManager);
        //mPlayBoard->startGame();
        mFrame->run();
    }
    destroy();
}

void PacManView::createMap(){
    mFrame = std::make_shared<PacManFrame>();
    auto frame = std::dynamic_pointer_cast<IBaseFrame>(mFrame);
    if(frame){
        Settings::getInstance()->setBaseFrame(frame);
    }
    mGameManager = std::make_shared<GameManager>();
    mGameManager->create();
    mFrame->create();
    //mFrame->addToList(mPlayBoard);
}

void PacManView::destroyMap(){
    if(mGameManager){
        mGameManager->destroy();
        mGameManager = nullptr;
    }
    if(mFrame){
        mFrame->destroy();
        mFrame = nullptr;
    }
}

void PacManView::create(){
    createMap();
}

void PacManView::destroy(){
    destroyMap();
}


PacManView::~PacManView(){
    if(mFrame){
        mFrame->destroy();
        mFrame = nullptr;
    }
    mGameManager = nullptr;
}
