//
//  ConcreteMap.hpp
//  PacMan
//
//  Created by Akhilesh Mishra on 29/04/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#ifndef ConcreteMap_hpp
#define ConcreteMap_hpp

#include "AllInterfaces.h"
#include "MapDisplay.hpp"
#include "BluePrint.hpp"
#include "PacManTheHero.hpp"

namespace pacman {namespace impl{


class GameManager: public IGameManager{
    MapDisplayPtr                             mDisplay;
    IBluePrintPtr                             mBluePrint;
    BoundingBox                               mBBox;
    GhostWorkerPtr                            mGhostWorker;
    PacManTheHero                             mPacMan;
public:
    GameManager();
    GENERIC_GETTER_SETTER(SquareDim,   mBBox,    BoundingBox);
    virtual void create() override;
    virtual void destroy() override;
    virtual void setPosition(const Position& p) override;
    virtual void play() override;
    
};



}}



#endif /* ConcreteMap_hpp */
