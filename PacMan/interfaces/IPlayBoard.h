//
//  IPlayBoard.h
//  PacMan
//
//  Created by Akhilesh Mishra on 30/04/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#ifndef IPlayBoard_h
#define IPlayBoard_h
#include "PrimaryObject.h"
#include "IDisplay.h"
#include "IPlayer.h"
namespace  pacman {
    class IGameManager: public IPrimaryObject{
    public:
        virtual bool canMove()override {return false;}
        virtual bool move(const Position& p) override{return false;}
        virtual void setPosition(const Position& )override{}
        virtual void setupDisplay() = 0;
        virtual void startGame() = 0;
    };
    DECLARE_SHARED(IGameManager);
    
    class IPlayBoard: public IDisplay{
    public:
    };
    DECLARE_SHARED(IPlayBoard);
}



#endif /* IPlayBoard_h */
