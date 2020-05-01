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
    class IPlayBoard: public IDisplay{
    public:
        virtual void setDirection(Directions d) override{
            (void)d;
        }
        virtual void setSpeed(size_t speed) override{
            (void)speed;
        }
    };
    DECLARE_SHARED(IPlayBoard);
}



#endif /* IPlayBoard_h */
