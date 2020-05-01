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
    public:
        PacManFrame();
        virtual sf::RenderWindow& getWindow() override;
        void run();
        
        void addToList(IDisplayPtr ptr);
        
        void destroy();
        
    private:
        void displayAll();
        void setTotalSizes();
    };
    
    DECLARE_SHARED(PacManFrame);
}}

#endif /* PacManFrame_hpp */
