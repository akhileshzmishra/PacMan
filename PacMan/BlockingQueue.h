//
//  BlockingQueue.h
//  PacMan
//
//  Created by Akhilesh Mishra on 05/05/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#ifndef BlockingQueue_h
#define BlockingQueue_h
#include "CommonIncludes.h"
#include "ElementalSignal.h"

namespace pacman {namespace impl{
    
template<bool lock>
class Locker{
    std::mutex& _mutex;
public:
    Locker(std::mutex& m):_mutex(m){
        _mutex.lock();
    }
    ~Locker(){
        _mutex.unlock();
    }
};
    
template<>
class Locker<false>{
public:
    Locker(std::mutex& m){
    }
    ~Locker(){
    }
};

template<class T, bool lock>
class BlockingQueue{
    typedef typename std::remove_reference<T>::type _Type;
    typedef std::queue<_Type>  TypeQueue;
    TypeQueue                  mQ;
    CountingIntegerSignal      mSignal;
    std::mutex                 mMut;
    typedef Locker<lock>       Guard;
public:
    void push(_Type elem){
        {
            Guard gd(mMut);
            mQ.push(elem);
        }
        mSignal.signal();
    }
    
    size_t size(){
        size_t elemSize = 0;
        Guard gd(mMut);
        elemSize = mQ.size();
        return elemSize;
    }
    
    std::pair<_Type, bool> pop(int durationInSec = -1){
        std::pair<_Type, bool> retVal(_Type(), false);
        
        if(mSignal.waitFor(100)){
            Guard gd(mMut);
            if(!mQ.empty()){
                retVal.first = mQ.front();
                retVal.second = true;
                mQ.pop();
            }
            return retVal;
        }
        
        return retVal;
    }
    
    void clear(){
        Guard gd(mMut);
        while(!mQ.empty()){
            mQ.pop();
        }
        mSignal.reset();
    }
};
    
}}

#endif /* BlockingQueue_h */
