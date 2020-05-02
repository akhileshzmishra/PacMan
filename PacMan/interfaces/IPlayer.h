//
//  IPlayer.h
//  PacMan
//
//  Created by Akhilesh Mishra on 29/04/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#ifndef IPlayer_h
#define IPlayer_h
#include "IDisplay.h"
namespace  pacman {
    class ISquare;
    DECLARE_SHARED(ISquare)
    class IPlayer: public IDisplay{
    public:
        virtual bool canMove() override{
            return true;
        }
        
        virtual void setCurrentSquare(ISquarePtr) = 0;
        virtual ISquarePtr getCurrentSquare() = 0;
        
    };

    DECLARE_SHARED(IPlayer);


    class IGhost: public IPlayer{
    public:
        virtual void live() = 0;
        virtual void setZombie(bool s) = 0;
        virtual bool isZombie() = 0;
        virtual void died() = 0;
        virtual void setDirection(Directions d) = 0;
        virtual void setSpeed(size_t speed) = 0;
        
    };

    DECLARE_SHARED(IGhost);


    class IPacMan: public IPlayer{
        virtual void consume(const Energy& e) = 0;
        virtual void canKill() = 0;
        virtual void kill() = 0;
    };

    DECLARE_SHARED(IPacMan);
}

#endif /* IPlayer_h */
