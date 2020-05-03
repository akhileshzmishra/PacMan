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
    if(mFrame){
        mFrame->run();
    }
}

void PacManView::create(){
    mFrame = std::make_shared<PacManFrame>();
    auto frame = std::dynamic_pointer_cast<IBaseFrame>(mFrame);
    if(frame){
        Settings::getInstance()->setBaseFrame(frame);
    }
    mFrame->create();
}

void PacManView::destroy(){
    if(mFrame){
        mFrame->destroy();
        mFrame = nullptr;
    }
}


PacManView::~PacManView(){
    destroy();
}
