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

namespace pacman { namespace impl{
    typedef BlockingQueue<RenderingJob> RenderingQueue;
    struct RenderedProperty{
        bool              active;
    };
    typedef std::unordered_map<IRenderered*, RenderedProperty>  RenderedList;
    class PacManFrame: public IRenderer, public SettingObserver,
    public std::enable_shared_from_this<PacManFrame>{
        sf::RenderWindow                mWindow;
        sf::RectangleShape              mEndRect;
        sf::Text                        mGameEndedText;
        sf::Font                        mfont;
        RenderedList                    mRenderedList[RenderLayer::MaxLayer];
        IGameManagerPtr                 mPlayBoard;
        bool                            mFullDisplay = false;
        bool                            mGameEnded = false;
        RenderingQueue                  mQueue;
        bool                            mCreated = false;
    public:
        PacManFrame();
        ~PacManFrame();
        virtual void addRenderered(IRenderered*  , RenderLayer layer)override;
        virtual void clearRendererd(IRenderered* )override;
        void run();
        
        void create();
        
        void destroy();
        
        void setGameManager(IGameManagerPtr board){
            mPlayBoard = board;
        }
        
        void addMovable(RenderingJob& j) override;
        
        void GetNotified(LiftData& data, const SettingsObservation& condition) override;
    private:
        void displayBackground();
        void displayMiddleground();
        void displayForeground();
        void displayQueue();
        void setTotalSizes();
        void onGameEnded();
    };
    
    DECLARE_SHARED(PacManFrame);
}}

#endif /* PacManFrame_hpp */
