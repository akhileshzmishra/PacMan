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
    
typedef BlockingQueue<RenderingJob, false> RenderingQueue;
struct RenderedProperty{
    bool              active;
};
typedef std::unordered_map<IRenderered*, RenderedProperty>  RenderedList;
class MainGameWindow: public IWindowState, public IRenderer,
    public std::enable_shared_from_this<MainGameWindow>,
    public SettingObserver
    {
    sf::RenderWindow*                       mWindow = 0;
    Position                                mPosition;
    RenderedList                            mRenderedList[RenderLayer::MaxLayer];
    IGameManagerPtr                         mPlayBoard;
    sf::Event                               mEvent;
    bool                                    mFullDisplay = false;
    bool                                    mGameEnded = false;
    RenderingQueue                          mQueue;
    bool                                    mCreated = false;
    WindowType                              mType;
public:
    MainGameWindow();
    virtual ~MainGameWindow();
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
    
    virtual void addRenderered(IRenderered*  , RenderLayer layer)override;
    virtual void clearRendererd(IRenderered* )override;
    
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
    
    
};
    
}}

#endif /* Windows_hpp */
