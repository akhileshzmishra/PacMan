//
//  ScoreCardWindow.hpp
//  PacMan
//
//  Created by Akhilesh Mishra on 09/05/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#ifndef ScoreCardWindow_hpp
#define ScoreCardWindow_hpp

#include "AllInterfaces.h"
#include "Settings.hpp"
#include "BlockingQueue.h"

namespace pacman {namespace impl{
    
    class ScoreCardWindow: public IWindowState{
        sf::RenderWindow*                       mWindow = 0;
        bool                                    mCreated = false;
        WindowType                              mType;
        Position                                mPosition;
        sf::RectangleShape                      mRect;
        sf::Text                                mGameOverText;
        sf::Text                                mScoreCardText;
        sf::Text                                mPlayAgain;
        sf::Font                                mFont;
        int                                     mPresent = 0;
    public:
        ScoreCardWindow();
        virtual ~ScoreCardWindow();
        virtual void setDrawableWindow(sf::RenderWindow* win)override{
            mWindow = win;
        }
        virtual WindowType getType() override{
            return mType;
        }
        
        virtual void play()override;
        virtual bool doNeedToChangeState() override;
        
        virtual void setPosition(const Position& p)override{
            mPosition = p;
        }
        virtual Position getPosition()override{
            return mPosition;
        }
        
        virtual void notifyKey(sf::Event& ev) override;
        
        virtual void create()override;
        virtual void destroy()override;
        
    };
}};

#endif /* ScoreCardWindow_hpp */
