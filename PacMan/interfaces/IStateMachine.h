//
//  IStateMachine.h
//  PacMan
//
//  Created by Akhilesh Mishra on 07/05/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#ifndef IStateMachine_h
#define IStateMachine_h
#include "CommonIncludes.h"
#include "PrimaryObject.h"
#include "GraphicIncludes.h"

namespace  pacman {

struct WindowType{
    std::string type;
};

class IWindowState: public IPrimaryObject{
public:
    virtual void setDrawableWindow(sf::RenderWindow* win) = 0;
    virtual WindowType getType() = 0;
    virtual void notifyKey(sf::Event& ) = 0;
    virtual void play() = 0;
    virtual bool doNeedToChangeState() = 0;
    
};

DECLARE_SHARED(IWindowState);

class IWindowStateMachine{
public:
    virtual void goToNextState() = 0;
};
DECLARE_SHARED(IWindowStateMachine);

}
#endif /* IStateMachine_h */
