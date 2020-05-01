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
    mDim.dimension = Settings::getInstance()->getCoinDimension();
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

ZombieMakerConsumable::ZombieMakerConsumable(DimensionMarker& dim){
    setZombie(true);
}

void Consumable::createData(){
    mColor = Colors::CoinColor;
    mCircleDisplay.setRadius(mDim.dimension.length);
    mCircleDisplay.setFillColor(sf::Color(mColor.red, mColor.green, mColor.blue));
    mCircleDisplay.setPosition(mDim.centroid.x, mDim.centroid.y);
}
void Consumable::create(){
    createData();
    setBaseFrame(Settings::getInstance()->getCopyBaseFrame());
    Register(MainWindowDimensionChange);
}

void Consumable::destroy(){
    setBaseFrame(nullptr);
    DeRegister(MainWindowDimensionChange);
}

void Consumable::GetNotified(LiftData& data, const SettingsObservation& condition){
    if(condition == MainWindowDimensionChange){
        mDim.dimension = Settings::getInstance()->getCoinDimension();
        createData();
    }
}

