//
//  GhostWorker.hpp
//  PacMan
//
//  Created by Akhilesh Mishra on 02/05/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#ifndef GhostWorker_hpp
#define GhostWorker_hpp

#include "AllInterfaces.h"
#include "GameState.hpp"

namespace pacman {namespace impl{
    
class GhostStateOnBoard{
    Coordinates current;
    Coordinates next;
    Position    currentPos;
    Position    nextPos;
    ISquarePtr  square;
public:
    GENERIC_GETTER_SETTER(currCoordinates, current,      Coordinates)
    GENERIC_GETTER_SETTER(nextCoordinates, next,         Coordinates)
    GENERIC_GETTER_SETTER(currPosition,    currentPos,   Position)
    GENERIC_GETTER_SETTER(nextPosition,    nextPos,      Position)
    GENERIC_GETTER_SETTER(OwningSquare,    square,       ISquarePtr)
    GhostStateOnBoard(){}
    bool hasReached(){
        return currentPos == nextPos;
    }
};
class GhostWorker: public IThreadWork{
    typedef std::vector<IGhostPtr>            Ghosts;
    Ghosts                                    mGhosts;
    IGhostMoveStrategyPtr                     mStrategy;
    GameState                                 mState;
    IBluePrintPtr                             mBluePrint;
    std::vector<GhostStateOnBoard>            mGhostState;
    
public:
    GhostWorker(IBluePrintPtr ptr);
    virtual void work() override;
    void addGhost(IGhostPtr ptr);
};

}}

#endif /* GhostWorker_hpp */
