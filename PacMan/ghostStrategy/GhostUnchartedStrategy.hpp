//
//  GhostUnchartedStrategy.hpp
//  PacMan
//
//  Created by Akhilesh Mishra on 02/05/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#ifndef GhostUnchartedStrategy_hpp
#define GhostUnchartedStrategy_hpp

#include "../CommonIncludes.h"
#include "../AllInterfaces.h"
#include "../GameState.hpp"

namespace pacman { namespace impl{
    class GhostUnchartedStrategy: public IGhostMoveStrategy{
        GameState&              mState;
        IBluePrintPtr           mPrint;
    public:
        GhostUnchartedStrategy(GameState& st);
        virtual void setBluePrint(IBluePrintPtr ptr)override;
        virtual Coordinates suggestNextMove(IGhostPtr ptr)override;
    };
}}

#endif /* GhostUnchartedStrategy_hpp */
