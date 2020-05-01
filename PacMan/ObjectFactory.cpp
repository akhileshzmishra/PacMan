//
//  ObjectFactory.cpp
//  PacMan
//
//  Created by Akhilesh Mishra on 29/04/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#include "ObjectFactory.hpp"
#include "BluePrint.hpp"
#include "MapDisplay.hpp"

using namespace pacman;
using namespace pacman::impl;

IMap* ObjectFactory::getMap(){
    return nullptr;
}

IPlayer* ObjectFactory::getPlayer(){
    return nullptr;
}

IBluePrintPtr ObjectFactory::getNewBluePrint(){
    return std::make_shared<BluePrint>();
}

MapDisplayPtr ObjectFactory::getMapDisplay(IBluePrintPtr ptr){
    return std::make_shared<MapDisplay>(ptr);
}
