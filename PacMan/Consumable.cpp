//
//  Consumable.cpp
//  PacMan
//
//  Created by Akhilesh Mishra on 01/05/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#include "Consumable.hpp"
#include "Settings.hpp"

using namespace pacman;
using namespace pacman::impl;

Consumable::Consumable(){
    SetSubject(Settings::getInstance());
}

void Consumable::display(){
    if(getBaseFramePtr()){
        getBaseFramePtr()->getWindow().draw(mCircleDisplay);
    }
}


bool Consumable::makeZombie(){
    return mZombie;
}

void Consumable::makeEmpty(){
    mValue = 0;
}

ZombieMakerConsumable::ZombieMakerConsumable(BoundingBox& dim){
    setZombie(true);
}

void Consumable::createData(){
    mColor = Colors::CoinColor;
    mCircleDisplay.setRadius(mBBox.dimension.length);
    mCircleDisplay.setFillColor(sf::Color(mColor.red, mColor.green, mColor.blue));
    mCircleDisplay.setPosition(mBBox.referencePos.col, mBBox.referencePos.row);
}
void Consumable::create(){
    createData();
    setBaseFrame(Settings::getInstance()->getCopyBaseFrame());
    Register(CoinDimensionChange);
}

void Consumable::destroy(){
    setBaseFrame(nullptr);
    DeRegister(CoinDimensionChange);
}

void Consumable::GetNotified(LiftData& data, const SettingsObservation& condition){
    if(condition == MainWindowDimensionChange){
        mBBox.dimension = Settings::getInstance()->getCoinDimension();
        createData();
    }
}

