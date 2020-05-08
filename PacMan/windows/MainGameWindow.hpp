//
//  Windows.hpp
//  PacMan
//
//  Created by Akhilesh Mishra on 07/05/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#ifndef WindowsMaiini_hpp
#define WindowsMaiini_hpp

#include "AllInterfaces.h"
#include "Settings.hpp"
#include "BlockingQueue.h"

namespace pacman {namespace impl{

class MainGameWindow: public IWindowState, public IRenderer{
    sf::Window*                             mWindow = 0;
public:
    virtual ~MainGameWindow(){}
    virtual void setDrawableWindow(sf::Window* win)override{
        mWindow = win;
    }
    virtual WindowType getType() override;
    virtual void draw() override;;
    virtual void play()override = 0;
    virtual bool doNeedToChangeState() override = 0;
    
};
    
}}

#endif /* Windows_hpp */
