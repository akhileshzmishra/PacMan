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

template<class T>
class BlockingQueue{
    typedef typename std::remove_reference<T>::type _Type;
    typedef std::queue<_Type>  TypeQueue;
    TypeQueue                  mQ;
    CountingIntegerSignal      mSignal;
    std::recursive_mutex       mMut;
public:
    void push(_Type elem){
        {
            std::lock_guard<std::recursive_mutex> _lck(mMut);
            mQ.push(elem);
        }
        mSignal.signal();
    }
    
    size_t size(){
        size_t elemSize = 0;
        std::lock_guard<std::recursive_mutex> _lck(mMut);
        elemSize = mQ.size();
        return elemSize;
    }
    
    std::pair<_Type, bool> pop(int durationInSec = -1){
        std::pair<_Type, bool> retVal(_Type(), false);
        
        if(mSignal.waitFor(100)){
            std::lock_guard<std::recursive_mutex> _lck(mMut);
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
        std::lock_guard<std::recursive_mutex> _lck(mMut);
        while(!mQ.empty()){
            mQ.pop();
        }
        mSignal.reset();
    }
};
    
}}

#endif /* BlockingQueue_h */
