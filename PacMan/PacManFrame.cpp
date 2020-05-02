//
//  PacManFrame.cpp
//  PacMan
//
//  Created by Akhilesh Mishra on 01/05/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#include "PacManFrame.hpp"
#include "Settings.hpp"

using namespace pacman;
using namespace pacman::impl;

PacManFrame::PacManFrame(){
    Dimension dim = Settings::getInstance()->getWindowDimension();
    mWindow.create(sf::VideoMode(dim.length, dim.width), pacman::PACMAN_TITLE);
                   //, sf::Style::Titlebar | sf::Style::Close);
    mWindow.setVerticalSyncEnabled(true);
    setTotalSizes();
}

void PacManFrame::setTotalSizes(){
    auto siz = mWindow.getSize();
    Settings::getInstance()->setWindowDimension(Dimension(siz.x, siz.y));
    Settings::getInstance()->calculate();
}

sf::RenderWindow& PacManFrame::getWindow(){
    return mWindow;
}


void PacManFrame::run(){
    setTotalSizes();
    mFullDisplay = true;
    bool startThread = true;
    while (mWindow.isOpen()){
        sf::Event event;
        while (mWindow.pollEvent(event)){
            if ((event.type == sf::Event::Closed) ||
                ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))){
                mWindow.close();
            }
            else if(event.type == sf::Event::Resized){
                setTotalSizes();
                mFullDisplay = true;
            }
            else{
                
            }
        }
        if(mFullDisplay){
            displayAll();
            setTotalSizes();
            mWindow.display();
            mFullDisplay = false;
        }
        else{
            startThread = false;
            mPlayBoard->startGame();
        }
    }
    destroy();
}

void PacManFrame::create(){
    
}

void PacManFrame::addToList(IDisplayPtr ptr){
    mDisplayList.push_back(ptr);
}

void PacManFrame::destroy(){
    for(int i = 0; i < mDisplayList.size(); i++){
        mDisplayList[i] = nullptr;
    }
    mDisplayList.clear();
}


void PacManFrame::displayAll(){
    for(int i = 0; i < mDisplayList.size(); i++){
        mDisplayList[i]->display();
    }
    mPlayBoard->setupDisplay();
}
