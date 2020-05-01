//
//  PrimaryObject.h
//  PacMan
//
//  Created by Akhilesh Mishra on 29/04/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#ifndef PrimaryObject_h
#define PrimaryObject_h
#include "CommonIncludes.h"
#include "IBaseFrame.h"
namespace  pacman {
    class IPrimaryObject{
        IBaseFrame*             mBaseFramePtr = nullptr;
    public:
        virtual bool canMove() = 0;
        virtual bool move() = 0;
        virtual void setPosition(const Position& p) = 0;
        virtual void setDirection(Directions d) = 0;
        virtual void setSpeed(size_t speed) = 0;
        virtual void setBaseFrame(IBaseFrame*  ptr){
            mBaseFramePtr = ptr;
        }
        
        IBaseFrame* getBaseFramePtr(){
            return mBaseFramePtr;
        }
        
    };

    DECLARE_SHARED(IPrimaryObject);

}
#endif /* PrimaryObject_h */
