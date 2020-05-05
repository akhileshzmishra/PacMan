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
                    case sf::Keyboard::D:
                        GetSubject()->NotifyToObservers(liftData, KeyPressedRight);
                        break;
                    case sf::Keyboard::W:
                        GetSubject()->NotifyToObservers(liftData, KeyPressedUp);
                        break;
                    case sf::Keyboard::Z:
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
            mPlayBoard->play();
            displayBackground();
            displayForeground();
            displayQueue();
        }
        mWindow.display();
    }
    destroy();
}

void PacManFrame::displayQueue(){
    while(mQueue.size() > 0){
        auto popValue = mQueue.pop();
        if(!popValue.second){
            return;
        }
        auto& first = popValue.first;
        if(!first.ptr || !first.ptr->getShape()){
            continue;
        }
        first.ptr->getShape()->setPosition(first.pos.col, first.pos.row);
        mWindow.draw(*(first.ptr->getShape()));
    }
}

void PacManFrame::displayBackground(){
    for(auto itr = mRenderedList[(int)RenderLayer::Background].begin();
        itr != mRenderedList[(int)RenderLayer::Background].end(); itr++){
        if(itr->first->canBeRendered()){
            auto shape = itr->first->getShape();
            if(shape){
                mWindow.draw(*shape);
            }
            itr->first->renderComplete();
        }
    }
}
void PacManFrame::displayForeground(){
    for(auto itr = mRenderedList[(int)RenderLayer::ForeGround].begin();
        itr != mRenderedList[(int)RenderLayer::ForeGround].end(); itr++){
        if(itr->first->canBeRendered()){
            auto shape = itr->first->getShape();
            if(shape){
                mWindow.draw(*shape);
            }
            itr->first->renderComplete();
        }
    }
}

void PacManFrame::onGameEnded(){
    mWindow.draw(mGameEndedText);
    mWindow.draw(mEndRect);
    mWindow.display();
    std::this_thread::sleep_for(std::chrono::seconds(5));
}

void PacManFrame::create(){
    Settings::getInstance()->setRenderer(shared_from_this());
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

void PacManFrame::addMovable(RenderingJob& p){
    mQueue.push(p);
}


void PacManFrame::destroy(){
    for(int i = 0; i < (int)RenderLayer::MaxLayer; i++){
        mRenderedList[i].clear();
    }
    
}

void PacManFrame::GetNotified(LiftData& data, const SettingsObservation& condition){
    if(condition == GameHasEnded){
        mGameEnded = true;
    }
}

void PacManFrame::addRenderered(IRenderered* ptr, RenderLayer layer){
    mRenderedList[(int)layer][ptr] = RenderedProperty();
    mRenderedList[(int)layer][ptr].active = false;
}
void PacManFrame::clearRendererd(IRenderered* ptr){
    for(int i = 0; i < (int)RenderLayer::MaxLayer; i++){
        mRenderedList[i].erase(ptr);
    }
}
