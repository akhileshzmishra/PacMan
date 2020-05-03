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
    struct RenderedProperty{
        bool              active;
    };
    typedef std::unordered_map<IRenderered*, RenderedProperty>  RenderedList;
    class PacManFrame: public IRenderer, public SettingObserver,
    public std::enable_shared_from_this<PacManFrame>{
        sf::RenderWindow                mWindow;
        sf::RectangleShape              mEndRect;
        sf::Text                        mGameEndedText;
        RenderedList                    mRenderedList[RenderLayer::MaxLayer];
        IGameManagerPtr                 mPlayBoard;
        bool                            mFullDisplay = false;
        bool                            mGameEnded = false;
    public:
        PacManFrame();
        virtual void addRenderered(IRenderered*  , RenderLayer layer)override;
        virtual void clearRendererd(IRenderered* )override;
        void run();
        
        void create();
        
        void destroy();
        
        void setGameManager(IGameManagerPtr board){
            mPlayBoard = board;
        }
        
        void GetNotified(LiftData& data, const SettingsObservation& condition) override;
    private:
        void displayBackground();
        void displayForeground();
        void setTotalSizes();
        void onGameEnded();
    };
    
    DECLARE_SHARED(PacManFrame);
}}

#endif /* PacManFrame_hpp */
