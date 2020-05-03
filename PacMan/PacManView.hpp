//
//  PacManView.hpp
//  PacMan
//
//  Created by Akhilesh Mishra on 01/05/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#ifndef PacManView_hpp
#define PacManView_hpp

#include "AllInterfaces.h"
#include "IPlayBoard.h"

namespace pacman{ namespace impl{
    class PacManFrame;
    DECLARE_SHARED(PacManFrame);
    
class PacManView{
    PacManFramePtr                  mFrame;
public:
    PacManView();
    void run();
    virtual ~PacManView();
    void create();
    void destroy();
};
    
}}

#endif /* PacManView_hpp */
