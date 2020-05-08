//
//  MapDisplay.cpp
//  PacMan
//
//  Created by Akhilesh Mishra on 29/04/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#include "MapDisplay.hpp"
#include "Settings.hpp"
#include "ObjectFactory.hpp"

using namespace pacman;
using namespace pacman::impl;


MapDisplay::MapDisplay(IBluePrintPtr plan):
mPlan(plan)
{
    SetSubject(Settings::getInstance());
}



void MapDisplay::setPosition(const Position& p) {
    calculatePositions();
}

Position MapDisplay::getPosition(){
    return Position();
}

void MapDisplay::create(){
    Register(SquareDimensionChange);
    mBBox.dimension = Settings::getInstance()->getBoardDimension();
    if(mPlan){
        mRows = mPlan->getRow();
        mCols = mPlan->getCol();
        mRowCol = RowCol(mRows, OneRow(mCols, nullptr));
        int count = 0;
        for(size_t i = 0; i < mRows; i++){
            for(size_t j = 0; j < mCols; j++){
                Coordinates coord(i, j);
                mRowCol[i][j] = std::make_shared<SingleSquare>();
                mRowCol[i][j]->setType(mPlan->getType(coord));
                mRowCol[i][j]->setCoordinates(coord);
                mRowCol[i][j]->create();
                mRowCol[i][j]->setOwner(this);
                if(!mPlan->isWall(coord)){
                    if(count%5 == 0){
                        auto coin = ObjectFactory::getCoins(Mega);
                        mRowCol[i][j]->setCoin(coin);
                    }
                    else{
                        auto coin = ObjectFactory::getCoins(Regular);
                        mRowCol[i][j]->setCoin(coin);
                    }
                }
                count++;
            }
        }
        calculatePositions();
    }
}

void MapDisplay::destroy(){
    DeRegister(SquareDimensionChange);
    for(size_t i = 0; i < mRows; i++){
        for(size_t j = 0; j < mCols; j++){
            mRowCol[i][j]->destroy();
        }
    }
}

ISquarePtr MapDisplay::getSquare(const Coordinates& c){
    if(mRows <= c.row || mCols <= c.col){
        return nullptr;
    }
    return mRowCol[c.row][c.col];
}

void MapDisplay::calculatePositions(){
    auto square = Settings::getInstance()->getSquareDimension();
    mBBox.dimension = Settings::getInstance()->getBoardDimension();
    for(size_t i = 0; i < mRows; i++){
        for(size_t j = 0; j < mCols; j++){
            auto posData = Settings::getInstance()->getSquarePositionData(Coordinates(i, j));
            if(posData){
                mRowCol[i][j]->setPosition(posData->getRefPosition());
                mRowCol[i][j]->setSize(square);
                //std::cout<<posData->getRefPosition().row<<" "<<posData->getRefPosition().col<<std::endl;
            }
        }
    }
}

void MapDisplay::GetNotified(LiftData& data, const SettingsObservation& condition){
    if(condition == SquareDimensionChange){
        calculatePositions();
    }
}
