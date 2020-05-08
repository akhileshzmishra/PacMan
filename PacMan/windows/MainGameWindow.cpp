//
//  Windows.cpp
//  PacMan
//
//  Created by Akhilesh Mishra on 07/05/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#include "MainGameWindow.hpp"
#include "ObjectFactory.hpp"

using namespace pacman;
using namespace pacman::impl;

static pacman::impl::LiftData liftData;

MainGameWindow::MainGameWindow(){
    mType.type = MAINWINDOW;
    
}

void MainGameWindow::notifyKey(sf::Event& event){
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

void MainGameWindow::displayQueue(){
    while(mQueue.size() > 0){
        auto popValue = mQueue.pop();
        if(!popValue.second){
            return;
        }
        auto& first = popValue.first;
        if(!first.ptr || !first.ptr->getShape()){
            continue;
        }
        auto drawable = first.ptr->getShape();
        auto shapee = dynamic_cast<sf::Shape*>(drawable);
        if(!shapee){
            continue;
        }
        if(first.steps > 0){
            auto currentPositionV = shapee->getPosition();
            Position currentP;
            currentP.row = currentPositionV.y;
            currentP.col = currentPositionV.x;
            float deltaRow = (first.pos.row - currentP.row)/first.steps;
            float deltaCol = (first.pos.col - currentP.col)/first.steps;
            for(int i = 0; i < first.steps; i++){
                currentP.row += deltaRow;
                currentP.col += deltaCol;
                shapee->setPosition(currentP.col, currentP.row);
                mWindow->draw(*shapee);
                //std::this_thread::sleep_for(std::chrono::milliseconds(20));
            }
        }
        shapee->setPosition(first.pos.col, first.pos.row);
        mWindow->draw(*shapee);
    }
}

void MainGameWindow::displayBackground(){
    for(auto itr = mRenderedList[(int)RenderLayer::Background].begin();
        itr != mRenderedList[(int)RenderLayer::Background].end(); itr++){
        if(itr->first->canBeRendered()){
            auto shape = itr->first->getShape();
            if(shape){
                mWindow->draw(*shape);
            }
            itr->first->renderComplete();
        }
    }
}
void MainGameWindow::displayForeground(){
    for(auto itr = mRenderedList[(int)RenderLayer::ForeGround].begin();
        itr != mRenderedList[(int)RenderLayer::ForeGround].end(); itr++){
        if(itr->first->canBeRendered()){
            auto shape = itr->first->getShape();
            if(shape){
                mWindow->draw(*shape);
            }
            itr->first->renderComplete();
        }
    }
}

void MainGameWindow::displayMiddleground(){
    for(auto itr = mRenderedList[(int)RenderLayer::Middleground].begin();
        itr != mRenderedList[(int)RenderLayer::Middleground].end(); itr++){
        if(itr->first->canBeRendered()){
            auto shape = itr->first->getShape();
            if(shape){
                mWindow->draw(*shape);
            }
            itr->first->renderComplete();
        }
    }
}

void MainGameWindow::create(){
    SetSubject(Settings::getInstance());
    Settings::getInstance()->setRenderer(shared_from_this());
    mPlayBoard = ObjectFactory::getGameManager();
    Register(GameHasEnded);
    mPlayBoard->create();
    mCreated = true;
}

void MainGameWindow::addMovable(RenderingJob& p){
    mQueue.push(p);
}

MainGameWindow::~MainGameWindow(){
    destroy();
}

void MainGameWindow::play(){
    if(!mGameEnded){
        if(!mWindow) return;
        mPlayBoard->play();
        displayBackground();
        displayMiddleground();
        displayForeground();
        displayQueue();
        mWindow->display();
    }
}


void MainGameWindow::destroy(){
    SetSubject(nullptr);
    if(mCreated){
        DeRegister(GameHasEnded);
        mPlayBoard->destroy();
        for(int i = 0; i < (int)RenderLayer::MaxLayer; i++){
            mRenderedList[i].clear();
        }
        Settings::getInstance()->setRenderer(nullptr);
    }
    mCreated = false;
}

bool MainGameWindow::doNeedToChangeState(){
    return mGameEnded;
}

void MainGameWindow::addRenderered(IRenderered* ptr, RenderLayer layer){
    mRenderedList[(int)layer][ptr] = RenderedProperty();
    mRenderedList[(int)layer][ptr].active = false;
}
void MainGameWindow::clearRendererd(IRenderered* ptr){
    for(int i = 0; i < (int)RenderLayer::MaxLayer; i++){
        mRenderedList[i].erase(ptr);
    }
}

void MainGameWindow::GetNotified(LiftData& data, const SettingsObservation& condition){
    if(condition == GameHasEnded){
        //Settings::getInstance()->setScore()
        mGameEnded = true;
    }
}
