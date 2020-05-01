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
    mFrame = std::make_shared<PacManFrame>();
}

void PacManView::run(){
    createMap();
    mFrame->run();
}

void PacManView::createMap(){
    mPlayBoard = std::make_shared<PlayBoard>();
    mPlayBoard->setUp();
    mFrame->addToList(mPlayBoard);
}


PacManView::~PacManView(){
    mFrame->destroy();
    mPlayBoard = nullptr;
}
