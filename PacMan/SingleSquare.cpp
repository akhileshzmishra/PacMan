//
//  SingleSquare.cpp
//  PacMan
//
//  Created by Akhilesh Mishra on 01/05/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#include "SingleSquare.hpp"
#include "Settings.hpp"

using namespace pacman;
using namespace pacman::impl;

SingleSquare::SingleSquare(int type):
mType(type),
mOccupant(nullptr),
mDimension(){
    mDimension.dimension = Settings::getInstance()->getSquareDimension();
    SetSubject(Settings::getInstance());
}

void SingleSquare::display() {
    if(getBaseFramePtr()){
        getBaseFramePtr()->getWindow().draw(mRect);
    }
    if(mCoin && mType == mapElements::Empty){
        mCoin->display();
    }
}

void SingleSquare::setPosition(const Position& p){
    mDimension.centroid = p;
    mRect.setPosition(p.x, p.y);
}

void SingleSquare::createData(){
    mDimension.dimension = Settings::getInstance()->getSquareDimension();
    if(mType >= 0 && mType < mapElements::Invalid){
        switch(mType){
            case mapElements::Wall:
                createWall();
                break;
            case mapElements::Empty:
                createEmpty();
                break;
            default:
                createWall();
                break;
        }
    }
}

void SingleSquare::create(){
    setBaseFrame(Settings::getInstance()->getCopyBaseFrame());
    createData();
    Register(MainWindowDimensionChange);
}

void SingleSquare::destroy(){
    DeRegister(MainWindowDimensionChange);
    setBaseFrame(nullptr);
    if(mCoin){
        mCoin->destroy();
    }
    mCoin = nullptr;
}

void SingleSquare::createEmpty(){
    mColor = Colors::EmptyColor;
    mRect.setSize(sf::Vector2f(mDimension.dimension.width, mDimension.dimension.length));
    mRect.setFillColor(sf::Color(mColor.red, mColor.green, mColor.blue));
    mRect.setPosition(mDimension.centroid.x, mDimension.centroid.y);
}

void SingleSquare::createWall(){
    mColor = Colors::WallColor;
    mRect.setSize(sf::Vector2f(mDimension.dimension.width, mDimension.dimension.length));
    mRect.setFillColor(sf::Color(mColor.red, mColor.green, mColor.blue));
    mRect.setPosition(mDimension.centroid.x, mDimension.centroid.y);
}


void SingleSquare::setGift(IGiftPtr ptr){
    mCoin = ptr;
}

IGiftPtr SingleSquare::getGift(){
    return mCoin;
}


void SingleSquare::GetNotified(LiftData& data, const SettingsObservation& condition){
    if(condition == MainWindowDimensionChange){
        createData();
    }
}



