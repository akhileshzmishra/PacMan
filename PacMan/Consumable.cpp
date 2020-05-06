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


bool Consumable::makeZombie(){
    return mZombie;
}

void Consumable::makeEmpty(){
    mValue = 0;
}

void Consumable::setPosition(const Position& p){
    mBBox.referencePos = p;
    mCircleDisplay.setPosition(p.col, p.row);
}

bool Consumable::canBeRendered(){
    return mRenderable;
}

const ShapeList* Consumable::getShapes(){
    return nullptr;
}
sf::Shape* Consumable::getShape(){
    return &mCircleDisplay;
}
void Consumable::renderComplete(){
    
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
    if(mbCreate) return;
    Settings::getInstance()->getCopyRenderer()->addRenderered(this, Middleground);
    createData();
    Register(CoinDimensionChange);
    mbCreate = true;
}

void Consumable::destroy(){
    if(mbCreate){
        Settings::getInstance()->getCopyRenderer()->clearRendererd(this);
        DeRegister(CoinDimensionChange);
    }
    mbCreate = false;
}

void Consumable::GetNotified(LiftData& data, const SettingsObservation& condition){
    if(condition == MainWindowDimensionChange){
        mBBox.dimension = Settings::getInstance()->getCoinDimension();
        createData();
    }
}

