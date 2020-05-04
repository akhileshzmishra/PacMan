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
#include "../Utiliity.hpp"

namespace pacman { namespace impl{
    class GhostUnchartedStrategy: public IGhostMoveStrategy{
        const GameState&              mState;
        IBluePrintPtr                 mPrint;
        DirectionDeltaList            mDirectionDelta;
    public:
        GhostUnchartedStrategy(const GameState& st);
        virtual void setBluePrint(IBluePrintPtr ptr)override;
        virtual DirSuggestion suggestNextMove(const Coordinates& , const Directions)override;
    };
}}

#endif /* GhostUnchartedStrategy_hpp */
