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
static const float CoinDim = 15.0;

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
        }
        mTopLeft.x = 0.f;
        mTopLeft.y = 0.f;
    }
}

Position Settings::getPositionFromCoordinates(Coordinates c){
    Position p;
    float fsl = mSquareDimension.length;
    float fsw = mSquareDimension.width;
    p.x = mTopLeft.x + mBorders.length + fsl*(c.x) + fsl*0.5;
    p.y = mTopLeft.y + mBorders.width + fsw*(c.y) + fsw*0.5;
    return p;
}

void Settings::setWindowDimension(const Dimension& d){
    mWindowDimension = d;
    calculate();
    pacman::impl::LiftData ldata;
    ldata.dim = mWindowDimension;
    NotifyToObservers(ldata, MainWindowDimensionChange);
    
    ldata.dim = mBoardDimension;
    NotifyToObservers(ldata, BoardDimensionChange);
    
    ldata.dim = mSquareDimension;
    NotifyToObservers(ldata, SquareDimensionChange);
    
    ldata.dim = mCoinDimension;
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
