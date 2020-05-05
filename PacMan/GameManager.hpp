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
    std::unique_ptr<std::thread>              mHelper;
    bool                                      mPlayContinue = true;
    bool                                      mPause = false;
    BoolSignal                                mSignal;
    bool                                      mCreated = false;
public:
    GameManager();
    GENERIC_GETTER_SETTER(SquareDim,   mBBox,    BoundingBox);
    virtual void create() override;
    virtual void destroy() override;
    virtual void setPosition(const Position& p) override;
    virtual void play() override;
    virtual void pause()override;
    virtual void stop()override;
    
private:
    void createAndRun();
    
};



}}



#endif /* ConcreteMap_hpp */
