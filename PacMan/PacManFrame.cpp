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

using namespace pacman;
using namespace pacman::impl;

PacManFrame::PacManFrame(){
    Dimension dim = Settings::getInstance()->getWindowDimension();
    mWindow.create(sf::VideoMode(dim.length, dim.width), pacman::PACMAN_TITLE, sf::Style::Titlebar | sf::Style::Close);
    //mWindow.setFramerateLimit(4);
    setTotalSizes();
    SetSubject(Settings::getInstance());
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
    pacman::impl::LiftData liftData;
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
                switch(event.key.code){
                    case sf::Keyboard::A:
                        GetSubject()->NotifyToObservers(liftData, KeyPressedLeft);
                        break;
                    case sf::Keyboard::S:
                        GetSubject()->NotifyToObservers(liftData, KeyPressedRight);
                        break;
                    case sf::Keyboard::W:
                        GetSubject()->NotifyToObservers(liftData, KeyPressedUp);
                        break;
                    case sf::Keyboard::X:
                        GetSubject()->NotifyToObservers(liftData, KeyPressedDown);
                        break;
                    default:
                        break;
                }
            }
        }
        if(mGameEnded){
            onGameEnded();
            mWindow.close();
            break;
        }
        else{
            displayAll();
            mPlayBoard->play();
        }
        mWindow.display();
    }
    destroy();
}

void PacManFrame::onGameEnded(){
    mWindow.draw(mGameEndedText);
    mWindow.draw(mEndRect);
    mWindow.display();
    std::this_thread::sleep_for(std::chrono::seconds(5));
}

void PacManFrame::create(){
    mPlayBoard = ObjectFactory::getGameManager();
    mPlayBoard->create();
    Register(SettingsObservation::GameHasEnded);
    auto Winpos = Settings::getInstance()->getWindowDimension();
    mGameEndedText.setPosition(0, 0);
    mGameEndedText.setString(GAME_OVER);
    mEndRect.setSize(sf::Vector2f(Winpos.length, Winpos.width));
    mEndRect.setFillColor(sf::Color::Black);
    mGameEndedText.setFillColor(sf::Color::White);
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

void PacManFrame::GetNotified(LiftData& data, const SettingsObservation& condition){
    if(condition == GameHasEnded){
        mGameEnded = true;
    }
}
