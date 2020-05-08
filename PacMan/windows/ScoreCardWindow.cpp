//
//  ScoreCardWindow.cpp
//  PacMan
//
//  Created by Akhilesh Mishra on 09/05/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#include "ScoreCardWindow.hpp"

using namespace pacman;
using namespace pacman::impl;

//static pacman::impl::LiftData liftData;


ScoreCardWindow::ScoreCardWindow(){
    mType.type = SCOREWINDOW;
}


ScoreCardWindow::~ScoreCardWindow(){
    
}


void ScoreCardWindow::play(){
    if(mWindow){
        mWindow->draw(mRect);
        mWindow->draw(mGameOverText);
        mWindow->draw(mScoreCardText);
        mWindow->draw(mPlayAgain);
        mWindow->display();
    }
    
}


void ScoreCardWindow::notifyKey(sf::Event& ev){
    
}

bool ScoreCardWindow::doNeedToChangeState(){
    return false;
}


void ScoreCardWindow::create(){
    if(mWindow){
        auto dimension = Settings::getInstance()->getWindowDimension();
        mRect.setSize(sf::Vector2f(dimension.length, dimension.width));
        mRect.setFillColor(sf::Color::Black);
        mFont.loadFromFile("arial.ttf");
        mGameOverText.setFont(mFont);
        mScoreCardText.setFont(mFont);
        mPlayAgain.setFont(mFont);
        
        mGameOverText.setCharacterSize(80);
        mScoreCardText.setCharacterSize(30);
        mPlayAgain.setCharacterSize(30);
        
        mGameOverText.setString(GAME_OVER);
        std::string score = ScoreCardText + std::string(" = ") +
            std::to_string(Settings::getInstance()->getCopyScore());
        mScoreCardText.setString(score);
        mPlayAgain.setString(PlayAgainText);
        
        mGameOverText.setFillColor(sf::Color::Red);
        
        auto boundA = mGameOverText.getLocalBounds();
        auto boundB = mScoreCardText.getLocalBounds();

        float maxH = std::max(boundA.height, boundB.height);
        
        
        float posY = dimension.length/2 - 3*maxH;
        float posX = 50;
        
        mGameOverText.setPosition(posX, posY);
        posY += 3*maxH;
        posX += 20;
        mScoreCardText.setPosition(posX, posY);
        posY += 1.5*maxH;
        mPlayAgain.setPosition(posX, posY);
    }
}


void ScoreCardWindow::destroy(){

}
