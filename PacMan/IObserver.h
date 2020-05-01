//
//  IObserver.h
//  PacMan
//
//  Created by Akhilesh Mishra on 01/05/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#ifndef IObserver_h
#define IObserver_h

#include <set>
#include <map>
#include <set>
#include <vector>
#include <type_traits>



template<class T, class X, class XComp = std::less<X> >
class ISubject2;

template<class T, class X, class XComp = std::less<X> >
class IObserver2;


template<class T, class X, class XComp >
class IObserver2
{
    typedef ISubject2<T, X, XComp>        SubjectType;
    typedef std::set<X, XComp>            ConditionSet;
    SubjectType*                          m_Subject;
    ConditionSet                          m_RegisteredList;
public:
    IObserver2(SubjectType* subject, std::vector<X>& conditions): m_Subject(subject)
    {
        if(m_Subject)
        {
            for(int i = 0; i < conditions.size(); i++)
            {
                Register(conditions[i]);
            }
        }
    }
    
    IObserver2(SubjectType* subject): m_Subject(subject)
    {
    }
    
    IObserver2(): m_Subject(nullptr)
    {
    }
    
    IObserver2(SubjectType* subject, bool registerall): m_Subject(subject)
    {
        if(registerall)
        {
            if(m_Subject){
                m_Subject->RegisterAll(this);
            }
        }
    }
    
    virtual ~IObserver2()
    {
        if(m_Subject)
        {
            m_Subject->DeRegister(this);
        }
    }
    
    void RegisterAll()
    {
        if(m_Subject){
            m_Subject->RegisterAll(this);
        }
    }
    
    void Register(X condition)
    {
        if(m_Subject)
        {
            if(m_RegisteredList.find(condition) == m_RegisteredList.end())
            {
                m_Subject->Register(this, condition);
                m_RegisteredList.insert(condition);
            }
        }
    }
    
    void DeRegister(X condition)
    {
        if(m_Subject)
        {
            m_Subject->DeRegister(this, condition);
        }
        m_RegisteredList.erase(condition);
    }
    
    void Deregister()
    {
        if(m_Subject)
        {
            m_Subject->DeRegister(this);
        }
        m_RegisteredList.clear();
        m_Subject = 0;
    }
    
    virtual void GetNotified(T& data, const X& condition) = 0;
    
    
    SubjectType* GetSubject()
    {
        return m_Subject;
    }
    
    void SetSubject(SubjectType* subject)
    {
        if(m_Subject)
        {
            m_Subject->DeRegister(this);
        }
        m_RegisteredList.clear();
        m_Subject = subject;
    }
};


template<class T, class X, class XComp>
class ISubject2
{
    typedef IObserver2<T, X, XComp>                  ObserverType;
    typedef std::multimap<X, ObserverType*, XComp>   ObserverList;
    typedef std::pair<X, ObserverType* >             ObsInsPair;
    typedef typename ObserverList::iterator          ObserverItr;
    
    typedef std::set<ObserverType* >                 AllSetType;
    ObserverList                                     m_list;
    AllSetType                                       m_AllList;
    std::recursive_mutex                             m_Lock;
    friend ObserverType;
public:
    ISubject2<T, X, XComp>()
    {
    }
    
    virtual ~ISubject2<T, X, XComp>()
    {
    }
    
    
    virtual void NotifyToObservers(T& data, const X& condition)
    {
        
        std::lock_guard<std::recursive_mutex> lck(m_Lock);
        std::pair<ObserverItr, ObserverItr> obsPair = m_list.equal_range(condition);
        ObserverItr itr = obsPair.first;
        while(itr != obsPair.second)
        {
            itr->second->GetNotified(data, condition);
            itr++;
        }
        
        for(auto allitr = m_AllList.begin(); allitr != m_AllList.end(); allitr++){
            (*allitr)->GetNotified(data, condition);
        }
        //m_ListGate.Unlock();
    }
    
protected:
    void RegisterAll(ObserverType* o)
    {
        std::lock_guard<std::recursive_mutex> lck(m_Lock);
        m_AllList.insert(o);
    }
    void Register(ObserverType* o, X condition)
    {
        std::lock_guard<std::recursive_mutex> lck(m_Lock);
        if(!o)
        {
            return;
        }
        if(m_AllList.find(o) !=  m_AllList.end()){
            return;
        }
        
        m_list.insert(ObsInsPair(condition, o));
    }
    
    void DeRegister(ObserverType* o)
    {
        std::lock_guard<std::recursive_mutex> lck(m_Lock);
        if(!o)
        {
            return;
        }
        
        std::vector<ObserverItr> deletITr;
        ObserverItr itr = m_list.begin();
        while(itr != m_list.end())
        {
            if(itr->second == o)
            {
                deletITr.push_back(itr);
            }
            
            itr++;
        }
        for(int i = 0; i < (int) deletITr.size(); i++)
        {
            m_list.erase(deletITr[i]);
        }
        
        m_AllList.erase(o);
    }
    
    void DeRegister(ObserverType* o, X condition)
    {
        std::lock_guard<std::recursive_mutex> lck(m_Lock);
        if(!o)
        {
            return;
        }
        
        std::pair<ObserverItr, ObserverItr> obsPair = m_list.equal_range(condition);
        ObserverItr itr = obsPair.first;
        while(itr != obsPair.second)
        {
            if(o == itr->second)
            {
                m_list.erase(itr);
                break;
            }
            itr++;
        }
    }
    
};



#endif

