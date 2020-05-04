//
//  GameState.hpp
//  PacMan
//
//  Created by Akhilesh Mishra on 02/05/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#ifndef GameState_hpp
#define GameState_hpp

#include "AllInterfaces.h"
#include "Utiliity.hpp"
namespace pacman {namespace impl{
    class GameNode{
        size_t                   nodeValue = 0;
        mapElements              type = mapElements::Invalid;
        std::vector<bool>        neighbours;
        int                      mNeighbours = 0;
        int                      mGhosts = 0;
    public:
        GameNode(): neighbours(4, false){
        }
        GENERIC_GETTER_SETTER(Value, nodeValue,        size_t)
        int getNeighbours() const{
            return mNeighbours;
        }
        
        void addValue(size_t v){
            if(!isWall()){
                nodeValue += v;
            }
        }
        void addNeibour(Directions d){
            if(d >= Directions::InvalidDir){
                return;
            }
            if(!neighbours[(int)d]){
                neighbours[(int)d] = true;
                mNeighbours++;
            }
        }
        
        bool canGoTo(Directions d) const {
            if(d >= Directions::InvalidDir){
                return false;
            }
            return neighbours[(int)d];
        }
        
        bool allows()const{
            return type != mapElements::Wall;
        }
        void swapTypes(GameNode& other){
            if(type == other.type){
                return;
            }
            if(isGhost()){
                mGhosts--;
            }
            if(other.isGhost()){
                other.mGhosts--;
            }
            std::swap(type, other.type);
        }
        
        bool isGhost()const{
            return type == mapElements::GhostPos || mGhosts > 0;
        }
        
        bool isWall()const{
            return type == mapElements::Wall;
        }
        
        bool isPlayer()const{
            return type == mapElements::PlayerPos;
        }
        
        bool isEmpty()  const                       {return type == mapElements::Empty;}
        void setGhost(){
            type = mapElements::GhostPos;
            mGhosts++;
        }
        void setPlayer(){
            if(isGhost()){
                mGhosts--;
            }
            type = mapElements::GhostPos;
        }
        void setEmpty(){
            if(isGhost()){
                mGhosts--;
            }
            type = mapElements::Empty;
        }
        void setWall(){
            type = mapElements::Wall;
        }
    };
    typedef std::vector<GameNode>     GameNodeVec;
    typedef std::vector<GameNodeVec>  GameNodeTwoD;
    class GameState{
        int                           mScore;
        IBluePrintPtr                 mBluePrint;
        int                           mGhostCount = 0;
        int                           mPlayerCount = 0;
        GameNodeTwoD                  mBoard;
        Coordinates                   mPlayerPosition;
        size_t                        mRows;
        size_t                        mCols;
        std::recursive_mutex          mMutex;
        typedef std::lock_guard<std::recursive_mutex> Lock;
        
    public:
        GameState(IBluePrintPtr ptr):mBluePrint(ptr){
            create();
        }
        
        bool canMove(const Coordinates& c)const{
            return isCoordinateOK(c) && mBoard[c.row][c.col].allows();
        }
        
        bool moveGhost(const Coordinates& from, const Coordinates& to){
            Lock lck(mMutex);
            if(mBoard[from.row][from.col].isGhost() &&
               (mBoard[to.row][to.col].isEmpty() || mBoard[to.row][to.col].isGhost())){
                mBoard[from.row][from.col].setEmpty();
                mBoard[to.row][to.col].setGhost();
                mBoard[to.row][to.col].addValue(1);
                return true;
            }
            return false;
        }
        
        bool movePlayer(const Coordinates& from, const Coordinates& to){
            Lock lck(mMutex);
            if(mBoard[from.row][from.col].isPlayer()&&
               mBoard[to.row][to.col].isEmpty()){
                mBoard[from.row][from.col].setEmpty();
                mBoard[to.row][to.col].setPlayer();
                mBoard[to.row][to.col].addValue(1);
                return true;
            }
            return false;
        }
        
        void print() const{
            for(size_t i = 0; i < mBluePrint->getRow(); i++){
                for(size_t j = 0; j < mBluePrint->getCol(); j++){
                    char k = '.';
                    if(mBoard[i][j].isWall()){
                        k='=';
                    }
                    if(mBoard[i][j].isGhost()){
                        k='P';
                    }
                    std::cout<<k<<' ';
                }
                std::cout<<std::endl;
            }
            std::cout<<std::endl;
        }
        
        
        bool isGhost(const Coordinates& c)const{
            return mBoard[c.row][c.col].isGhost();
        }
        
        bool isEmpty(const Coordinates& c)const{
            return mBoard[c.row][c.col].isEmpty();
        }
        
        bool isPlayer(const Coordinates& c)const{
            return mBoard[c.row][c.col].isPlayer();
        }
        
        bool isWall(const Coordinates& c) const{
            return mBoard[c.row][c.col].isWall();
        }
        
        int getNeighbors(const Coordinates& c) const{
            return mBoard[c.row][c.col].getNeighbours();
        }
        
        int canGoTo(const Coordinates& c, Directions d) const{
            return isCoordinateOK(c) && mBoard[c.row][c.col].canGoTo(d) && mBoard[c.row][c.col].allows();
        }
        
        size_t getRows() const{
            return mRows;
        }
        
        void addToBoard(const Coordinates& c, size_t num){
            if(c.row < mBluePrint->getRow() && c.col < mBluePrint->getCol()){
                mBoard[c.row][c.col].addValue(num);
            }
        }
        
        size_t getBoardNum(const Coordinates& c)const{
            return mBoard[c.row][c.col].getConstRefValue();
        }
        
        size_t getCols()const{
            return mCols;
        }
        
        const Coordinates& getPlayerPosition()const{
            return mPlayerPosition;
        }
        
        void addScore(int s){
            mScore += s;
        }
        
        bool isCoordinateOK(const Coordinates& c) const{
            return c.row < mRows && c.col < mCols;
        }
    private:
        void create(){
            mBoard = GameNodeTwoD(mBluePrint->getRow(),
                               GameNodeVec(mBluePrint->getCol()));
            DirectionDeltaList dlist = Utility::getDirectionsDelta();
            mRows = mBluePrint->getRow();
            mCols = mBluePrint->getCol();
            for(int i = 0; i < (int)mRows; i++){
                for(int j = 0; j < (int)mCols; j++){
                    const Coordinates cord(i, j);
                    if(mBluePrint->isGhost(cord)){
                        mBoard[i][j].setGhost();
                    }
                    else if(mBluePrint->isWall(cord)){
                        mBoard[i][j].setWall();
                        continue;
                    }
                    else if(mBluePrint->isEmpty(cord)){
                        mBoard[i][j].setEmpty();
                    }
                    else if(mBluePrint->isPlayer(cord)){
                        mBoard[i][j].setPlayer();
                        mPlayerPosition = cord;
                    }
                    for(int k = 0; k < dlist.size(); k++){
                        int r1 = i + dlist[k].rowDelta;
                        int c1 = j + dlist[k].colDelta;
                        const Coordinates c(r1,c1);
                        if(isCoordinateOK(c) && !mBluePrint->isWall(c)){
                            mBoard[i][j].addNeibour(dlist[k].direction);
                        }
                    }
                }
            }
        }
    };
}}


#endif /* GameState_hpp */
