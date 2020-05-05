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
    
    typedef std::pair<Directions, Coordinates> DirSuggestion;

    
    class IGhostMoveStrategy{
    public:
        virtual ~IGhostMoveStrategy(){}
        virtual void setBluePrint(IBluePrintPtr ptr) = 0;
        virtual DirSuggestion suggestNextMove(const Coordinates& , const Directions) = 0;
    };
    DECLARE_SHARED(IGhostMoveStrategy);
}
#endif /* IGhostMoveStrategy_h */
