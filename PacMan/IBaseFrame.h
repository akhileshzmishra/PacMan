//
//  IBaseFrame.h
//  PacMan
//
//  Created by Akhilesh Mishra on 01/05/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#ifndef IBaseFrame_h
#define IBaseFrame_h
#include "CommonIncludes.h"
#include "GraphicIncludes.h"

namespace  pacman {
class IDisplay;
DECLARE_SHARED(IDisplay);
class IBaseFrame{
public:
    virtual sf::RenderWindow& getWindow() = 0;
    
};
    
DECLARE_SHARED(IBaseFrame);
}

#endif /* IBaseFrame_h */
