//
//  Settings.cpp
//  PacMan
//
//  Created by Akhilesh Mishra on 01/05/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#include "Settings.hpp"
#include "BluePrint.hpp"

using namespace pacman;
using namespace pacman::impl;

static const float WindowDim = 1080.0;
static const float BorderDim = 2.0;
static const float SquareDim = 50.0;
static const float CoinDim = 20.0;
static const float GhostDim = 25.0;

Settings::Settings(){
    
}

Settings* Settings::getInstance(){
    static Settings settings;
    return &settings;
}

void Settings::start(){
    mBorders.length = mBorders.width = BorderDim;
    mSquareDimension.length = mSquareDimension.width = SquareDim;
    mWindowDimension.length = mWindowDimension.width = WindowDim;
    mCoinDimension.length = mCoinDimension.width = CoinDim;
    mBoardDimension.length = mWindowDimension.length - 2*mBorders.length;
    mBoardDimension.width = mWindowDimension.width - 2*mBorders.width;
    mGhostDimension.width = mGhostDimension.length = GhostDim;
    //refillSquarePositions();
}

void Settings::calculate(){
    if(mBluePrint){
        size_t r = mBluePrint->getRow();
        size_t c = mBluePrint->getCol();
        if(r > 0 && c > 0){
            mBoardDimension.length = mWindowDimension.length - 2*mBorders.length;
            mBoardDimension.width = mWindowDimension.width - 2*mBorders.width;
            float squarelength = std::min(mBoardDimension.length/c, mBoardDimension.width/r);
            mSquareDimension.length = squarelength;
            mSquareDimension.width = squarelength;
            mCoinDimension.width = mCoinDimension.length = mSquareDimension.length*.4;
            mGhostDimension.width = mGhostDimension.length = squarelength/2;
            refillSquarePositions();
        }
        mTopLeft.row = 0.f;
        mTopLeft.col = 0.f;
    }
}

void Settings::refillSquarePositions(){
    mData.clear();
    Position itr = mTopLeft;
    size_t r = mBluePrint->getRow();
    size_t c = mBluePrint->getCol();
    mData = SQMatrixData(r, SQRowPositionData(c));
    for(size_t i = 0; i < r; i++){
        itr.col = mTopLeft.col;
        for(size_t j=  0; j < c; j++){
            mData[i][j].setPosition(itr);
            itr.col += mSquareDimension.length;
        }
        itr.row += mSquareDimension.width;
    }
}
SquarePositionData* Settings::getSquarePositionData(const Coordinates& c){
    if(c.row < mData.size()){
        if(c.col < mData[c.row].size()){
            return &mData[c.row][c.col];
        }
    }
    return nullptr;
}

void Settings::setWindowDimension(const Dimension& d){
    mWindowDimension = d;
    calculate();
    pacman::impl::LiftData ldata;

    NotifyToObservers(ldata, MainWindowDimensionChange);
    
    NotifyToObservers(ldata, BoardDimensionChange);
    
    NotifyToObservers(ldata, SquareDimensionChange);
    
    NotifyToObservers(ldata, CoinDimensionChange);
}

const Dimension& Settings::getCoinDimension(){
    return mCoinDimension;
}

const Dimension& Settings::getSquareDimension(){
    return mSquareDimension;
}

const Dimension& Settings::getBoardDimension(){
    return mBoardDimension;
}

const Dimension& Settings::getWindowDimension(){
    return mWindowDimension;
}

const Position& Settings::getTopLeftMapPosition(){
    return mTopLeft;
}


const Dimension& Settings::getBoardBorders(){
    return mBorders;
}

ColorRGB Settings::getBoardColor(){
    return Colors::WallColor;
}

ColorRGB Settings::getEmptyColor(){
    return Colors::EmptyColor;
}

ColorRGB Settings::getWallColor(){
    return Colors::WallColor;
}

ColorRGB Settings::getCoinColor(){
    return Colors::CoinColor;
}
