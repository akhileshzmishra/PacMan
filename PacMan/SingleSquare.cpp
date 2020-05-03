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
mBBox(){
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
    mBBox.referencePos = p;
    mRect.setPosition(p.col, p.row);
    if(mOccupant){
        mOccupant->setPosition(p);
    }
}

Position SingleSquare::getPosition(){
    return mBBox.referencePos;
}

void SingleSquare::setSize(Dimension d){
    mRect.setSize(sf::Vector2f(d.length, d.width));
}

void SingleSquare::createData(){
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

void SingleSquare::create(){
    mBBox.dimension = Settings::getInstance()->getSquareDimension();
    setBaseFrame(Settings::getInstance()->getCopyBaseFrame());
    createData();
}

void SingleSquare::destroy(){
    setBaseFrame(nullptr);
    if(mCoin){
        mCoin->destroy();
    }
    mCoin = nullptr;
}

void SingleSquare::createEmpty(){
    mColor = Colors::EmptyColor;
    mRect.setSize(sf::Vector2f(mBBox.dimension.width, mBBox.dimension.length));
    mRect.setFillColor(sf::Color(mColor.red, mColor.green, mColor.blue));
    mRect.setPosition(mBBox.referencePos.col, mBBox.referencePos.row);
}

void SingleSquare::createWall(){
    mColor = Colors::WhiteColor;
    mRect.setSize(sf::Vector2f(mBBox.dimension.width, mBBox.dimension.length));
    mRect.setFillColor(sf::Color(mColor.red, mColor.green, mColor.blue));
    mRect.setPosition(mBBox.referencePos.col, mBBox.referencePos.row);
}


void SingleSquare::setGift(IGiftPtr ptr){
    mCoin = ptr;
}

IGiftPtr SingleSquare::getGift(){
    return mCoin;
}

bool SingleSquare::move(const Position& p){
    mBBox.referencePos = p;
    mRect.move(p.row, p.col);
    return true;
}



