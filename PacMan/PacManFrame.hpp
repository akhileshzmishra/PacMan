//
//  PacManFrame.hpp
//  PacMan
//
//  Created by Akhilesh Mishra on 01/05/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#ifndef PacManFrame_hpp
#define PacManFrame_hpp

#include "AllInterfaces.h"
#include "Settings.hpp"
#include "BlockingQueue.h"
#include "MainGameWindow.hpp"

namespace pacman { namespace impl{
    
    class PacManFrame: public SettingObserver, public IWindowStateMachine{
        sf::RenderWindow                mWindow;
        IWindowStatePtr                 mCurrentState;
        bool                            mGameEnded = false;
        bool                            mFullDisplay = false;
        std::string                     mCurrentStatString;
    public:
        PacManFrame();
        ~PacManFrame();
        void run();
        
        void create();
        
        void destroy();
        
        
        void GetNotified(LiftData& data, const SettingsObservation& condition) override;
        
        virtual void goToNextState() override;
        
    private:
        void setTotalSizes();
        IWindowStatePtr createWindow(const std::string& type);
        void getNextState();
    };
    
    DECLARE_SHARED(PacManFrame);
}}

#endif /* PacManFrame_hpp */
