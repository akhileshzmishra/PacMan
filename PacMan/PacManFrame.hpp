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

namespace pacman { namespace impl{
    typedef std::vector<IDisplayPtr>  DisplayList;
    class PacManFrame: public IBaseFrame, public SettingObserver{
        sf::RenderWindow                mWindow;
        sf::RectangleShape              mEndRect;
        sf::Text                        mGameEndedText;
        DisplayList                     mDisplayList;
        IGameManagerPtr                 mPlayBoard;
        bool                            mFullDisplay = false;
        bool                            mGameEnded = false;
    public:
        PacManFrame();
        virtual sf::RenderWindow& getWindow() override;
        void run();
        
        void addToList(IDisplayPtr ptr);
        
        void create();
        
        void destroy();
        
        void setGameManager(IGameManagerPtr board){
            mPlayBoard = board;
        }
        
        void GetNotified(LiftData& data, const SettingsObservation& condition) override;
    private:
        void displayAll();
        void setTotalSizes();
        void onGameEnded();
    };
    
    DECLARE_SHARED(PacManFrame);
}}

#endif /* PacManFrame_hpp */
