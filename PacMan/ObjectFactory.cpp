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
#include "Ghost.hpp"
#include "GhostUnchartedStrategy.hpp"
#include "GameManager.hpp"

using namespace pacman;
using namespace pacman::impl;


IGameManagerPtr ObjectFactory::getGameManager(){
    return std::make_shared<GameManager>();
}

IBluePrintPtr ObjectFactory::getNewBluePrint(){
    return std::make_shared<BluePrint>();
}

MapDisplayPtr ObjectFactory::getMapDisplay(IBluePrintPtr ptr){
    return std::make_shared<MapDisplay>(ptr);
}

IGhostPtr ObjectFactory::getGhost(){
    return std::make_shared<Ghost>();
}

IGhostMoveStrategyPtr ObjectFactory::getUnchartedMoveStrategy(GameState& st){
    return std::make_shared<GhostUnchartedStrategy>(st);
}

GhostWorkerPtr ObjectFactory::getGhostWorker(IBluePrintPtr ptr)
{
    return std::make_shared<GhostWorker>(ptr);
}
