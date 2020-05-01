//
//  IMap.h
//  PacMan
//
//  Created by Akhilesh Mishra on 29/04/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#ifndef IMap_h
#define IMap_h
#include "PrimaryObject.h"

namespace  pacman {
    class IMap: public IPrimaryObject{
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
        
    };
    
    DECLARE_SHARED(IMap);
}



#endif /* IMap_h */
