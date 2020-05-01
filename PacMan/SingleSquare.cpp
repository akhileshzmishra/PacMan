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
}

void SingleSquare::display() {
    if(mCoin && mType == mapElements::Empty){
        mCoin->display();
    }
    
    if(getBaseFramePtr()){
        getBaseFramePtr()->draw(this);
    }
}

sf::Shape* SingleSquare::getShape(){
    return &mRect;
}

void SingleSquare::setPosition(const Position& p){
    mDimension.centroid = p;
    mRect.setPosition(p.x, p.y);
}

void SingleSquare::create(){
    if(mType >= 0 && mType < mapElements::Invalid){
        switch(mType){
            case mapElements::Wall:
                createWall();
                break;
            case mapElements::Empty:
                createEmpty();
                break;
            default:
                createEmpty();
                break;
        }
    }
}

void SingleSquare::setBaseFrame(IBaseFrame*  ptr){
    if(mCoin){
        mCoin->setBaseFrame(ptr);
    }
    IDisplay::setBaseFrame(ptr);
}

void SingleSquare::createEmpty(){
    mColor = Colors::EmptyColor;
    mRect.setSize(sf::Vector2f(mDimension.dimension.width, mDimension.dimension.length));
    mRect.setFillColor(sf::Color(mColor.red, mColor.green, mColor.blue));
}

void SingleSquare::createWall(){
    mColor = Colors::WallColor;
    mRect.setSize(sf::Vector2f(mDimension.dimension.width, mDimension.dimension.length));
    mRect.setFillColor(sf::Color(mColor.red, mColor.green, mColor.blue));
}


void SingleSquare::setGift(IGiftPtr ptr){
    mCoin = ptr;
}

IGiftPtr SingleSquare::getGift(){
    return mCoin;
}



