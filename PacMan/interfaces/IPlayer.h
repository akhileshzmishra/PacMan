//
//  IPlayer.h
//  PacMan
//
//  Created by Akhilesh Mishra on 29/04/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#ifndef IPlayer_h
#define IPlayer_h
#include "IStaticObjects.h"
namespace  pacman {
    class ISquare;
    DECLARE_SHARED(ISquare)
    class IPlayBoard;
    DECLARE_SHARED(IPlayBoard);
    class IPlayer: public IPrimaryObject, public IRenderered{
        Directions                       mDir;
    public:
        
        
        virtual void setCurrentSquare(ISquarePtr) = 0;
        virtual ISquareWeakPtr getCurrentSquare() = 0;
        virtual void setBoard(IPlayBoardWeakPtr) = 0;
        virtual IPlayBoardWeakPtr getBoard() = 0;
        virtual Dimension getDimension() = 0;
        virtual void died() = 0;
        virtual void live() = 0;
        virtual bool isGhost() = 0;
        virtual void setRenderable(bool s) = 0;
        virtual void addMovable(const Position& p) = 0;
        virtual void addMovable(const Position& p, float speed) = 0;
        GENERIC_GETTER_SETTER(CurDirection, mDir, Directions);
    };

    DECLARE_SHARED(IPlayer);


    class IGhost: public IPlayer{
    public:
        virtual void setZombie(bool s) = 0;
        virtual bool isZombie() = 0;
        virtual bool isGhost(){
            return true;
        }
    };

    DECLARE_SHARED(IGhost);


    class IPacMan: public IPlayer{
        virtual void addEnergy(const Energy& e) = 0;
        virtual bool canKill() = 0;
        virtual void kill() = 0;
        virtual bool isGhost() override{
            return false;
        }
    };

    DECLARE_SHARED(IPacMan);
}

#endif /* IPlayer_h */
