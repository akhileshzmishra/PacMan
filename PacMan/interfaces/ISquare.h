//
//  ISquare.h
//  PacMan
//
//  Created by Akhilesh Mishra on 01/05/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#ifndef ISquare_h
#define ISquare_h
#include "IDisplay.h"
#include "IGift.h"

namespace  pacman {
    class ISquare: public IDisplay{
    public:
        virtual bool canMove() override{
            return false;
        }
        virtual bool move() override{
            return false;
        }
        virtual void setDirection(Directions d) override{
            (void)d;
        }
        virtual void setSpeed(size_t speed) override{
            (void)speed;
        }
        virtual bool allows() = 0;
        virtual void setGift(IGiftPtr ptr) = 0;
        virtual IGiftPtr getGift() = 0;
        
        virtual void create() = 0;
    };

    DECLARE_SHARED(ISquare);
    
}

#endif /* ISquare_h */
