//
//  PacManTheHero.hpp
//  PacMan
//
//  Created by Akhilesh Mishra on 03/05/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#ifndef PacManTheHero_hpp
#define PacManTheHero_hpp

#include "AllInterfaces.h"
#include "Settings.hpp"
#include "GameState.hpp"
#include "ElementalSignal.h"
#include "Utiliity.hpp"

namespace pacman{namespace impl{
    
    class PacManState{
        ISquarePtr           currentSquare;
        Position             currentPosition;
        Directions           direction;
        float                mSpeed = 5.0;
        IPlayBoardWeakPtr    playboard;
        GameState*           mGameState;
        BoundingBox          mBBox;
        DirectionDeltaList   mDelta;
        Dimension            mPacmanDim;
        Coordinates          coordinates;
    public:
        PacManState();
        GENERIC_GETTER_SETTER(CurrentSquare,      currentSquare,      ISquarePtr)
        GENERIC_GETTER_SETTER(Directions,         direction,          Directions)
        GENERIC_GETTER_SETTER(Speed,              mSpeed,             float)
        GENERIC_GETTER_SETPTR(GameState,          mGameState,         GameState)
        GENERIC_GETTER_SETTER(Dimension,          mBBox.dimension,    Dimension)
        GENERIC_GETTER_SETTER(Position,           currentPosition,    Position)
        GENERIC_GETTER_SETTER(Coordinates,        coordinates,        Coordinates)
        void setPlayboard(IPlayBoardWeakPtr ptr){
            playboard = ptr;
        }
        IPlayBoardWeakPtr getBoard() {return playboard;}
        const DirectionDeltaList& getDirectionDelta(){
            return mDelta;
        }
        
        void move();
        
        void recalculatePosition();
        
    private:
        bool examineIfReached();
        
    };
    class PacManTheHero: public IPacMan, public IThreadWork,
    public SettingObserver{
        sf::CircleShape                 mHead;
        int                             mLives = 4;
        bool                            mIsDead = false;
        Energy                          mEnergy;
        bool                            mHasSuperPowers;
        Position                        mNextPos;
        bool                            mReady = false;
        bool                            mRenderable = true;
        PacManState                     mInternalState;
        BoolSignal                      mSignal;
    public:
        PacManTheHero();
        virtual void setPosition(const Position& p)override;
        virtual Position getPosition() override;
        virtual void create()override;
        virtual void destroy() override;
                  
        virtual void work() override;
        void setSpeed(float x) override{
            mInternalState.setSpeed(x);
        }
        
        virtual void died()override;
        virtual void live()override;
        
        virtual void setCurrentSquare(ISquarePtr)override;
        virtual ISquareWeakPtr getCurrentSquare()override;
        virtual void setBoard(IPlayBoardWeakPtr)override;
        virtual IPlayBoardWeakPtr getBoard()override;
        virtual Dimension getDimension() override{
            return mInternalState.getRefDimension();
        }
        
        virtual void addEnergy(const Energy& e) override;
        virtual bool canKill()override;
        virtual void kill()override;
        
        void GetNotified(LiftData& data, const SettingsObservation& condition) override;
        
        void setState(GameState* st){
            mInternalState.setGameState(st);
        }
        
        virtual bool canBeRendered()override;
        virtual sf::Shape* getShape()override;
        void setRenderable(bool s)override{
            mRenderable = s;
        }
        const ShapeList* getShapes() override{
            return nullptr;
        }
        virtual void renderComplete() override;
        
    private:
        void resetShape();
    };

    DECLARE_SHARED(PacManTheHero)
}}


#endif /* PacManTheHero_hpp */
