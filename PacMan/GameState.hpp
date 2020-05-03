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
namespace pacman {namespace impl{
    class GameNode{
        int           nodeValue = 0;
        mapElements   type = mapElements::Invalid;
    public:
        GENERIC_GETTER_SETTER(Value, nodeValue, int)
        GENERIC_GETTER_SETTER(type,  type,      mapElements)
        void addValue(int v){
            if(!isWall()){
                nodeValue += v;
            }
        }
        bool allows()const{
            return type != mapElements::Wall;
        }
        void swapTypes(GameNode& other){
            std::swap(type, other.type);
        }
        
        bool isGhost()const{
            return type == mapElements::GhostPos;
        }
        
        bool isWall()const{
            return type == mapElements::Wall;
        }
        
        bool isPlayer()const{
            return type == mapElements::PlayerPos;
        }
        
        bool isEmpty()  const                       {return type == mapElements::Empty;}
        void setGhost()                             {type = mapElements::GhostPos;}
        void setPlayer()                            {type = mapElements::GhostPos;}
        void setEmpty(){
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
    public:
        GameState(IBluePrintPtr ptr):mBluePrint(ptr){
            create();
        }
        
        bool canMove(Coordinates c)const{
            return mBoard[c.row][c.col].allows();
        }
        
        bool moveGhost(const Coordinates& from, const Coordinates& to){
            if(mBoard[from.row][from.col].isGhost()&&
               mBoard[to.row][to.col].isEmpty()){
                mBoard[from.row][from.col].setEmpty();
                mBoard[to.row][to.col].setGhost();
                return true;
            }
            return false;
        }
        
        bool movePlayer(const Coordinates& from, const Coordinates& to){
            if(mBoard[from.row][from.col].isPlayer()&&
               mBoard[to.row][to.col].isEmpty()){
                mBoard[from.row][from.col].setEmpty();
                mBoard[to.row][to.col].setPlayer();
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
        
        
        bool isGhost(Coordinates c)const{
            return mBoard[c.row][c.col].isGhost();
        }
        
        bool isEmpty(Coordinates c)const{
            return mBoard[c.row][c.col].isEmpty();
        }
        
        bool isPlayer(Coordinates c)const{
            return mBoard[c.row][c.col].isPlayer();
        }
        
        bool isWall(Coordinates c) const{
            return mBoard[c.row][c.col].isWall();
        }
        
        size_t getRows() const{
            return mBluePrint->getRow();
        }
        
        void addToBoard(Coordinates c, int num){
            if(c.row < mBluePrint->getRow() && c.col < mBluePrint->getCol()){
                mBoard[c.row][c.col].addValue(num);
            }
        }
        
        int getBoardNum(Coordinates c)const{
            return mBoard[c.row][c.col].getConstRefValue();
        }
        
        size_t getCols()const{
            return mBluePrint->getCol();
        }
        
        const Coordinates& getPlayerPosition()const{
            return mPlayerPosition;
        }
        
        void addScore(int s){
            mScore += s;
        }
    private:
        void create(){
            mBoard = GameNodeTwoD(mBluePrint->getRow(),
                               GameNodeVec(mBluePrint->getCol()));
            
            for(size_t i = 0; i < mBluePrint->getRow(); i++){
                for(size_t j = 0; j < mBluePrint->getCol(); j++){
                    Coordinates cord(i, j);
                    mBoard[i][j].settype(mBluePrint->getType(cord));
                    if(mBoard[i][j].isPlayer()){
                        mPlayerPosition = cord;
                    }
                }
            }
        }
    };
}}


#endif /* GameState_hpp */
