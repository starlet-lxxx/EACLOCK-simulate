#ifndef EACLOCK_hpp
#define EACLOCK_hpp

#endif // EACLOCK

#include "EvictStrategy.hpp"


using EACLOCK_Final_type = std::pair<PID, AccessCount>;
using EACLOCK_Final_upper = EvictStrategyHashVector<EACLOCK_Final_type>;

struct EACLOCK_Final: public EACLOCK_Final_upper {

    int lastWeight;
    bool lastAction;
    double lastHR;
    uint evictNum;
    uint HitInBuf;
    bool starCount;
    bool isChange;

    EACLOCK_Final(): EACLOCK_Final_upper() {}
    uint next =0;

    void reInit(RamSize ram_size) override{
        EACLOCK_Final_upper::reInit(ram_size);
        next = 0;
        lastWeight = 16;
        lastAction = +1;
        evictNum = 0;
        HitInBuf = 0;
        lastHR = 0;
        starCount = false;
        isChange = false;
    }

    uint insertElement(const Access& access) override {
        ram[next] = {access.pid, 0};
        return next++;
    }

    void UpdateWeight()
    {
        double newHR = 1.0*HitInBuf/(HitInBuf+evictNum);
        isChange = false;
        if(newHR>lastHR)
        {
            lastWeight = lastWeight + lastAction;
        }
        else
        {
            lastAction = -(lastAction);
            lastWeight = lastWeight + lastAction;
        }
        lastHR = newHR;
        if(lastWeight<=0)
        {
            lastWeight = 1;
            lastHR = newHR-0.01;
            lastAction = -1;
        }
        else if(lastWeight>=16)
        {
            lastWeight = 16;
            lastHR = newHR-0.01;
            lastAction = +1;
        }
    }

    void updateElement(uint old, const Access&) override
    {
        ram[old].second = ram[old].second+lastWeight;
        if(starCount)
            HitInBuf++;
    }

    PID evictOne(Access) override{
        starCount = true;
        while(true) {
            if(next >= ram.size()){
                next -= ram.size();
            }
            if(ram[next].second != 0){
                ram[next].second = ram[next].second-1;
                next++;
            }else{
                fast_finder.erase(ram[next].first);
                evictNum++;
                if(evictNum>=ram.size()/2)
                {
                    UpdateWeight();
                    evictNum = 0;
                    HitInBuf = 0;
                }
                return ram[next].first;
            }
        }
    }
};



using EACLOCK_WA_type = std::pair<PID, AccessCount>;
using EACLOCK_WA_upper = EvictStrategyHashVector<EACLOCK_WA_type>;

struct EACLOCK_WA: public EACLOCK_WA_upper {

    int lastWeight;
    bool lastAction;
    double lastHR;
    uint evictNum;
    uint HitInBuf;
    bool starCount;
    bool isChange;

    EACLOCK_WA(): EACLOCK_WA_upper() {}
    uint next =0;

    void reInit(RamSize ram_size) override{
        EACLOCK_WA_upper::reInit(ram_size);
        next = 0;
        lastWeight = 16;
        lastAction = +1;
        evictNum = 0;
        HitInBuf = 0;
        lastHR = 0;
        starCount = false;
        isChange = false;
    }

    uint insertElement(const Access& access) override {
        ram[next] = {access.pid, 0};
        return next++;
    }

    void UpdateWeight()
    {
        double newHR = 1.0*HitInBuf/(HitInBuf+evictNum);
        isChange = false;
        if(newHR>lastHR)
        {
            lastWeight = lastWeight + lastAction;
        }
        else
        {
            lastAction = -(lastAction);
            lastWeight = lastWeight + lastAction;
        }
        lastHR = newHR;
        if(lastWeight<=0)
        {
            lastWeight = 1;
            lastHR = newHR-0.01;
            lastAction = -1;
        }
        else if(lastWeight>=16)
        {
            lastWeight = 16;
            lastHR = newHR-0.01;
            lastAction = +1;
        }
    }

    void updateElement(uint old, const Access& access) override
    {
        if(access.write)
            ram[old].second = ram[old].second+2*lastWeight;
        else
            ram[old].second = ram[old].second+lastWeight;
        if(starCount)
            HitInBuf++;
    }

    PID evictOne(Access) override{
        starCount = true;
        while(true) {
            if(next >= ram.size()){
                next -= ram.size();
            }
            if(ram[next].second != 0){
                ram[next].second = ram[next].second-1;
                next++;
            }else{
                fast_finder.erase(ram[next].first);
                evictNum++;
                if(evictNum>=ram.size()/2)
                {
                    UpdateWeight();
                    evictNum = 0;
                    HitInBuf = 0;
                }
                return ram[next].first;
            }
        }
    }
};

using EACLOCK_DW_HR_type = std::pair<PID, AccessCount>;
using EACLOCK_DW_HR_upper = EvictStrategyHashVector<EACLOCK_DW_HR_type>;

struct EACLOCK_DW_HR: public EACLOCK_DW_HR_upper {

    int lastWeight;
    bool lastAction;
    double lastHR;
    uint evictNum;
    uint HitInBuf;
    bool starCount;
    bool isChange;
    int upLimit;
    double HRpercent;

    EACLOCK_DW_HR(double hrpercent): EACLOCK_DW_HR_upper() ,HRpercent(hrpercent){}
    uint next =0;

    void reInit(RamSize ram_size) override{
        EACLOCK_DW_HR_upper::reInit(ram_size);
        next = 0;
        lastWeight = 16;
        lastAction = +1;
        evictNum = 0;
        HitInBuf = 0;
        lastHR = 0;
        starCount = false;
        isChange = false;
        upLimit = 24;
    }

    uint insertElement(const Access& access) override {
        ram[next] = {access.pid, 0};
        return next++;
    }

    void UpdateWeight()
    {
        double newHR = 1.0*HitInBuf/(HitInBuf+evictNum);
        isChange = false;
        if(newHR>lastHR)
        {
            lastWeight = lastWeight + lastAction;
        }
        else
        {
            if(lastHR-newHR>HRpercent*(1-lastHR))
            {
                isChange = true;
                uint i = 0;
                while(i < ram.size()) {
                    if(ram[i].second != 0){
                        ram[i].second = ram[i].second/2;
                    }
                    i++;
                }
            }
            else
            {
                lastAction = -(lastAction);
                lastWeight = lastWeight + lastAction;
            }
        }
        lastHR = newHR;
        if(lastWeight<=1)
        {
            lastWeight = 1;
            lastHR = newHR-0.01;
            lastAction = -1;
        }
        else if(lastWeight>=upLimit)
        {
            lastWeight = upLimit;
            lastHR = newHR-0.01;
            lastAction = +1;
        }
    }

    void updateElement(uint old, const Access&) override{
        ram[old].second = ram[old].second+lastWeight;
        if(starCount)
            HitInBuf++;
    }

    PID evictOne(Access) override{
        starCount = true;
        while(true) {
            if(next >= ram.size()){
                next -= ram.size();
            }
            if(ram[next].second != 0){
                if(isChange)
                    ram[next].second = ram[next].second/2;
                else
                    ram[next].second = ram[next].second-1;
                next ++;
            }else{
                fast_finder.erase(ram[next].first);
                evictNum++;
                if(evictNum>=ram.size()/2)
                {
                    UpdateWeight();
                    evictNum = 0;
                    HitInBuf = 0;
                }
                return ram[next].first;
            }
        }
    }
};
