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
#include "Settings.hpp"

namespace pacman {namespace impl{
    
class GhostStateOnBoard{
    Coordinates           current;
    Coordinates           target;
    Position              currentPos;
    Position              nextPos;
    ISquareWeakPtr        square;
    Directions            mDirection;
    Dimension             mGhostBBox;
    float                 mSpeed;
    IGhostPtr             mGhost;
    IPlayBoardWeakPtr     mPlayer;
    static Dimension      sSquareDim;
    static Dimension      sGhostDim;
    GameState*            mState;
    bool                  mStop = false;
public:
    GhostStateOnBoard(){}
    GhostStateOnBoard(IGhostPtr ptr);
    GENERIC_GETTER_SETTER(currCoordinates,   current,      Coordinates)
    GENERIC_GETTER_SETTER(targetCoordinates, target,       Coordinates)
    GENERIC_GETTER_SETTER(currPosition,      currentPos,   Position)
    GENERIC_GETTER_SETTER(targetPosition,    nextPos,      Position)
    GENERIC_GETTER_SETTER(OwningSquare,      square,       ISquareWeakPtr)
    GENERIC_GETTER_SETTER(Direction,         mDirection,   Directions)
    GENERIC_GETTER_SETTER(Speed,             mSpeed,       float)
    GENERIC_GETTER_SETTER(Stop,              mStop,        bool)
    GENERIC_GETTER_SETTER(Ghost,             mGhost,       IGhostPtr)
    GENERIC_GETTER_SETTER(Player,            mPlayer,      IPlayBoardWeakPtr)
    GENERIC_GETTER_SETPTR(GameState,         mState,       GameState)
    GENERIC_GETTER_SETTER(GhostDimension,    mGhostBBox,   Dimension)
    bool hasReached();
    
    void destroy(){
        if(mGhost){
            mGhost->destroy();
            mGhost = nullptr;
        }
    }
    
    static void setSquareDim(const Dimension& d){
        sSquareDim = d;
    }
    
    static void setGhostDim(const Dimension& d){
        sGhostDim = d;
    }
    
    void move();
    
    bool arrive();
    
    bool lookAhead(DirSuggestion& s);
    
    void calculatePositions();
    
    void correctPosition();
private:
    bool hasReached(Directions dir);
};
class GhostWorker: public IThreadWork, public SettingObserver{
    IGhostMoveStrategyPtr                     mStrategy;
    GameState                                 mState;
    IBluePrintPtr                             mBluePrint;
    std::vector<GhostStateOnBoard>            mGhostState;
    float                                     mSpeed = 3.0;
    IBaseFramePtr                             mBaseFrame;
    bool                                      mStart = false;
    bool                                      mGameEnded = false;
public:
    GhostWorker(IBluePrintPtr ptr);
    virtual void work() override;
    void addGhost(IGhostPtr ptr);
    void setSpeed(float x) override{
        mSpeed = x;
    }
    
    GameState* getState(){
        return &mState;
    }
    
    void create();
    void destroy();
    
    void GetNotified(LiftData& data, const SettingsObservation& condition) override;
};

    
    DECLARE_SHARED(GhostWorker);
    
}}

#endif /* GhostWorker_hpp */
