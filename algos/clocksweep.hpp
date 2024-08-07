//
// Created by dev on 03.03.22.
//

#ifndef CLOCK_AC_HPP
#define CLOCK_AC_HPP

#endif //CLOCK_AC_HPP

#include "EvictStrategy.hpp"

using clock_AC_type = std::pair<PID, AccessCount>;
using clock_AC_upper = EvictStrategyHashVector<clock_AC_type>;

struct CLOCK_AC: public clock_AC_upper {
    CLOCK_AC(): clock_AC_upper() {}
    uint next =0;

    void reInit(RamSize ram_size) override{
        clock_AC_upper::reInit(ram_size);
        next =0;
    }
    void updateElement(uint old, const Access&) override{
        ram[old].second = ram[old].second+1;
    }

    uint insertElement(const Access& access) override {
        ram[next] = {access.pid, 1};
        return next++;
    }

    PID evictOne(Access) override{
        while(true) {
            if(next >= ram.size()){
                next -= ram.size();
            }
            if(ram[next].second != 0){
                ram[next].second = ram[next].second-1;
                next ++;
            }else{
                fast_finder.erase(ram[next].first);
                return ram[next].first;
            }
        }
    }

};
