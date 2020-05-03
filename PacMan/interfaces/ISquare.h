//
//  ISquare.h
//  PacMan
//
//  Created by Akhilesh Mishra on 01/05/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#ifndef ISquare_h
#define ISquare_h
#include "IStaticObjects.h"
#include "IGift.h"
#include "IPlayer.h"
#include "IRenderer.h"

namespace  pacman {
    class IPlayBoard;
    DECLARE_SHARED(IPlayBoard)
    
    class ISquare: public IStaticObjects, public IRenderered{
    public:
        virtual bool canMove() override{
            return false;
        }
        virtual bool allows() = 0;
        virtual void setGift(IGiftPtr ptr) = 0;
        virtual IGiftPtr getGift() = 0;
        virtual void setSize(Dimension d) = 0;
        
        virtual void setOccupant(IPlayerPtr) = 0;
        virtual IPlayerPtr getOccupant() = 0;
        virtual void setOwner(IPlayBoard* ) = 0;
        virtual IPlayBoard* getOwner() = 0;
    };

    DECLARE_SHARED(ISquare);
    
}

#endif /* ISquare_h */
