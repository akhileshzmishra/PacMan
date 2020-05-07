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
mBBox(){
}


void SingleSquare::setPosition(const Position& q){
    mBBox.referencePos = q;
    mRect.setPosition(q.col, q.row);
    mAnimatron.setPosition(q.col, q.row);
    positionCoin();
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

void SingleSquare::renderComplete(){
    //mRenderable = false;
}

void SingleSquare::create(){
    mBBox.dimension = Settings::getInstance()->getSquareDimension();
    Settings::getInstance()->getCopyRenderer()->addRenderered(this, RenderLayer::Background);
    createData();
}

void SingleSquare::destroy(){
    Settings::getInstance()->getCopyRenderer()->clearRendererd(this);
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
    mAnimatron.setRadius(mBBox.dimension.length);
    mAnimatron.setFillColor(sf::Color::Blue);
    mAnimatron.setPosition(mBBox.referencePos.col, mBBox.referencePos.row);
}

bool SingleSquare::canBeRendered(){
    return mRenderable;
}

void SingleSquare::setRenderable(bool s){
    mRenderable = s;
}

sf::Shape* SingleSquare::getShape(){
    if(mCoinAnimation > 0){
        mCoinAnimation--;
        return &mAnimatron;
    }
    return &mRect;
}

void SingleSquare::setCoin(ICoinPtr ptr){
    if(mCoin){
        mCoin->destroy();
        mCoinAnimation = 10;
    }
    mCoin = ptr;
    if(mCoin){
        mCoin->setRenderable(true);
        mCoin->create();
        positionCoin();
    }
}

void SingleSquare::positionCoin(){
    auto coinDim = Settings::getInstance()->getCoinDimension();
    auto sqDim = Settings::getInstance()->getSquareDimension();
    Position p = mBBox.referencePos;
    p.row += (sqDim.length - coinDim.length)/2;
    p.col += (sqDim.width - coinDim.width)/2;
    if(mCoin){
        mCoin->setPosition(p);
    }
}

ICoinPtr SingleSquare::getCoin(){
    return mCoin;
}



