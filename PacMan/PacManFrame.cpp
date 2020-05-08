//
//  PacManFrame.cpp
//  PacMan
//
//  Created by Akhilesh Mishra on 01/05/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#include "PacManFrame.hpp"
#include "Settings.hpp"
#include "ObjectFactory.hpp"
#include "ScoreCardWindow.hpp"

using namespace pacman;
using namespace pacman::impl;

PacManFrame::~PacManFrame(){
    
}

PacManFrame::PacManFrame(){
    Dimension dim = Settings::getInstance()->getWindowDimension();
    mWindow.create(sf::VideoMode(dim.length, dim.width), pacman::PACMAN_TITLE, sf::Style::Titlebar | sf::Style::Close);
    //mWindow.setFramerateLimit(4);
    setTotalSizes();
    SetSubject(Settings::getInstance());
    mCurrentStatString = "";
}

void PacManFrame::setTotalSizes(){
    auto siz = mWindow.getSize();
    Settings::getInstance()->setWindowDimension(Dimension(siz.x, siz.y));
    Settings::getInstance()->calculate();
}

void PacManFrame::run(){
    setTotalSizes();
    mFullDisplay = true;
    goToNextState();
    while (mWindow.isOpen()){
        sf::Event event;
        while (mWindow.pollEvent(event)){
            if ((event.type == sf::Event::Closed) ||
                ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))){
                mGameEnded = true;
                break;
            }
            else if(event.type == sf::Event::Resized){
                setTotalSizes();
                mFullDisplay = true;
            }
            else{
                if(event.type == sf::Event::KeyPressed){
                    mCurrentState->notifyKey(event);
                }
            }
        }
        if(!mGameEnded){
            mCurrentState->play();
            if(mCurrentState->doNeedToChangeState()){
                goToNextState();
            }
        }
        else{
            mWindow.close();
        }
    }
    destroy();
}

void PacManFrame::goToNextState(){
    if(mCurrentState){
        mCurrentState->destroy();
        mCurrentState = nullptr;
    }
    getNextState();
    mCurrentState = createWindow(mCurrentStatString);
}

IWindowStatePtr PacManFrame::createWindow(const std::string& type){
    IWindowStatePtr ptr;
    if(type == MAINWINDOW){
        ptr = std::make_shared<MainGameWindow>();
    }
    else{
        ptr = std::make_shared<ScoreCardWindow>();
    }
    ptr->setDrawableWindow(&mWindow);
    ptr->create();
    return ptr;
}

void PacManFrame::getNextState(){
    if(mCurrentStatString == MAINWINDOW){
        mCurrentStatString = SCOREWINDOW;
    }
    else if(mCurrentStatString == ""){
        mCurrentStatString = MAINWINDOW;
    }
}

void PacManFrame::create(){
    mCurrentState = std::make_shared<MainGameWindow>();
    mCurrentState->setDrawableWindow(&mWindow);
    mCurrentState->create();
}

void PacManFrame::destroy(){
    if(mCurrentState){
        mCurrentState->destroy();
    }
    mCurrentState = nullptr;
}

void PacManFrame::GetNotified(LiftData& data, const SettingsObservation& condition){
    
}
