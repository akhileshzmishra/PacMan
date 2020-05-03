//
//  ObjectFactory.hpp
//  PacMan
//
//  Created by Akhilesh Mishra on 29/04/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#ifndef ObjectFactory_hpp
#define ObjectFactory_hpp

#include "AllInterfaces.h"
#include "GameState.hpp"
#include "GhostWorker.hpp"

namespace pacman {namespace impl{
    
class MapDisplay;
DECLARE_SHARED(MapDisplay);

class ObjectFactory{
    
public:
    static IMap* getMap();
    static IGameManagerPtr getGameManager();
    static IBluePrintPtr getNewBluePrint();
    static MapDisplayPtr getMapDisplay(IBluePrintPtr ptr);
    static IGhostPtr getGhost();
    static IGhostMoveStrategyPtr getUnchartedMoveStrategy(GameState& st);
    static GhostWorkerPtr getGhostWorker(IBluePrintPtr ptr);
};
        
}}

#endif /* ObjectFactory_hpp */
