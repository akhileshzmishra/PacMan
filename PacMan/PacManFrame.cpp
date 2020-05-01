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
    mWindow.setVerticalSyncEnabled(true);
}

void PacManFrame::draw(IDisplay* p){
    auto shape = p->getShape();
    if(shape){
        mWindow.draw(*shape);
    }
}


void PacManFrame::run(){
    while (mWindow.isOpen()){
        sf::Event event;
        while (mWindow.pollEvent(event)){
            if ((event.type == sf::Event::Closed) ||
                ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))){
                mWindow.close();
            }
            else{
                
            }
        }
        displayAll();
    }
    destroy();
}

void PacManFrame::addToList(IDisplayPtr ptr){
    mDisplayList.push_back(ptr);
    ptr->setBaseFrame(this);
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
}
