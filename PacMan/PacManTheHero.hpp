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
    class PacManTheHero: public IPacMan, public IThreadWork,
    public SettingObserver{
        sf::CircleShape                 mHead;
        BoundingBox                     mBBox;
        ISquareWeakPtr                  mHoldingSquare;
        IPlayBoardWeakPtr               mHoldingBoard;
        float                           mSpeed = 12;
        Directions                      mDirections;
        int                             mLives = 4;
        bool                            mIsDead = false;
        Energy                          mEnergy;
        bool                            mHasSuperPowers;
        GameState*                      mGameState = nullptr;
        Position                        mNextPos;
        bool                            mReady = false;
        bool                            mRenderable = true;
        BoolSignal                      mSignal;
        DirectionDeltaList              mDirectionDelta;
    public:
        PacManTheHero();
        virtual void setPosition(const Position& p)override;
        virtual Position getPosition() override;
        virtual void create()override;
        virtual void destroy() override;
                  
        virtual void work() override;
        void setSpeed(float x) override{
            mSpeed = x;
        }
        
        virtual void died()override;
        virtual void live()override;
        
        virtual void setCurrentSquare(ISquarePtr)override;
        virtual ISquareWeakPtr getCurrentSquare()override;
        virtual void setBoard(IPlayBoardWeakPtr)override;
        virtual IPlayBoardWeakPtr getBoard()override;
        virtual Dimension getDimension() override{
            return mBBox.dimension;
        }
        
        virtual void addEnergy(const Energy& e) override;
        virtual bool canKill()override;
        virtual void kill()override;
        
        void GetNotified(LiftData& data, const SettingsObservation& condition) override;
        void move();
        
        void setState(GameState* st){
            mGameState = st;
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
    };

    DECLARE_SHARED(PacManTheHero)
}}


#endif /* PacManTheHero_hpp */
