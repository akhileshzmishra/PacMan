//
//  ElementalSignal.h
//  ProcUtils
//
//  Created by Akhilesh Mishra on 31/07/19.
//  Copyright © 2019 Akhilesh Mishra. All rights reserved.
//

#ifndef ElementalSignal_h
#define ElementalSignal_h
#include "CommonIncludes.h"

namespace pacman {namespace impl{

template<class T, T setValue, T notSetValue>
class ElementalSignal{
    std::mutex _m;
    std::condition_variable _cv;
    T _elem;
public:
    ElementalSignal(){
        _elem = notSetValue;
    }
    
    void reset(){
        _elem = notSetValue;
    }
    
    void signal(){
        _elem = setValue;
        _cv.notify_one();
    }
    
    T value(){
        return _elem;
    }
    
    void wait(int timeInMillisec = -1) {
        std::unique_lock<std::mutex> lk(_m);
        if (timeInMillisec > 0) {
            _cv.wait_for(lk, std::chrono::milliseconds(timeInMillisec * 1000), [&]{
                return (_elem == setValue);
            });
        }
        else {
            _cv.wait(lk, [&]{
                return (_elem == setValue);
            });
        }
    }
};



template<int initialCount, int MaxCount>
class CountingSignal{
    std::atomic_int mCount;
    std::mutex _m;
    std::condition_variable _cv;
public:
    CountingSignal():mCount(initialCount){
        
    }
    
    void reset(){
        mCount = initialCount;
    }
    
    void signal(){
        mCount++;
        if(mCount >= MaxCount){
            mCount = MaxCount;
        }
        _cv.notify_all();
    }
    
    bool waitFor(int millsec = -1){
        bool retVal = false;
        if(millsec > 0){
            std::unique_lock<std::mutex> _lck(_m);
            _cv.wait(_lck, [=, &retVal]{
                retVal = (mCount > 0);
                return retVal;
            });
        }
        else{
            auto tim = std::chrono::milliseconds(millsec);
            std::unique_lock<std::mutex> _lck(_m);
            _cv.wait_for(_lck, tim, [=, &retVal]{
                retVal = (mCount > 0);
                return retVal;
            });
        }
        if(retVal){
            mCount--;
        }
        return retVal;
    }
};

typedef ElementalSignal<bool, true, false> BoolSignal;
typedef CountingSignal<0, INT_MAX> CountingIntegerSignal;

}}
#endif /* ElementalSignal_h */
