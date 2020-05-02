//
//  IGhostMoveStrategy.h
//  PacMan
//
//  Created by Akhilesh Mishra on 02/05/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#ifndef IGhostMoveStrategy_h
#define IGhostMoveStrategy_h
#include "CommonIncludes.h"
namespace  pacman {
    class IBluePrint;
    DECLARE_SHARED(IBluePrint);
    
    class IGhost;
    DECLARE_SHARED(IGhost);
    
    class IGhostMoveStrategy{
    public:
        virtual void setBluePrint(IBluePrintPtr ptr) = 0;
        virtual Coordinates suggestNextMove(IGhostPtr) = 0;
    };
    DECLARE_SHARED(IGhostMoveStrategy);
}
#endif /* IGhostMoveStrategy_h */
