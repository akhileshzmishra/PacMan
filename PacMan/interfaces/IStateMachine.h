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
#include "IRenderer.h"

namespace  pacman {

struct WindowType{
    int type = 0;
};

class IWindowState{
public:
    virtual void setDrawableWindow(sf::Window* win) = 0;
    virtual WindowType getType() = 0;
    virtual void draw() = 0;;
    virtual void play() = 0;
    virtual bool doNeedToChangeState() = 0;
    
};

DECLARE_SHARED(IWindowState);

class IWindowStateMachine{
public:
    virtual void addState(IWindowState* st) = 0;
    virtual void registerChange(WindowType& from, WindowType& to) = 0;
    
    virtual void draw() = 0;
    virtual void play() = 0;
};
DECLARE_SHARED(IWindowStateMachine);

}
#endif /* IStateMachine_h */
