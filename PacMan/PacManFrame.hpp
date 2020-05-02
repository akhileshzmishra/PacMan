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

namespace pacman { namespace impl{
    typedef std::vector<IDisplayPtr>  DisplayList;
    class PacManFrame: public IBaseFrame{
        sf::RenderWindow                mWindow;
        DisplayList                     mDisplayList;
        IGameManagerPtr                 mPlayBoard;
        bool                            mFullDisplay = false;
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
    private:
        void displayAll();
        void setTotalSizes();
    };
    
    DECLARE_SHARED(PacManFrame);
}}

#endif /* PacManFrame_hpp */
