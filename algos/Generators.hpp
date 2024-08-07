//
// Created by dev on 15.11.21.
//
#pragma once
#include <functional>
// Algos
#include "EvictStrategy.hpp"
#include "random.hpp"
#include "lru.hpp"
#include "opt.hpp"
#include "cf_lru.hpp"
#include "lru_wsr.hpp"
#include "lru_k.hpp"
#include "lfu_k.hpp"
#include "hyperbolic.hpp"
#include "staticOpt.hpp"
#include "lean_evict.hpp"
#include "CLOCK.hpp"
#include "LRFU.hpp"
#include "ARC.hpp"
#include "clocksweep.hpp"


#include "lruStackDist.hpp"
#include "EACLOCK.hpp"


#ifndef C_GENERATORS_H
#define C_GENERATORS_H

#endif //C_GENERATORS_H


// Defaults
std::function<OPT()> Opt_Generator();
std::function<StaticOpt()> StaticOpt_Generator();
std::function<Random()> Random_Generator();
std::function<CLOCK()> CLOCK_Generator();
std::function<SECOND_CHANCE()> SECOND_CHANCE_Generator();

std::function<CLOCK_AC()> CLOCK_AC_Generator();


std::function<EACLOCK_Final()> EACLOCK_Final_Generator();
std::function<EACLOCK_WA()> EACLOCK_WA_Generator();
std::function<EACLOCK_DW_HR()> EACLOCK_DW_HR_generator(double hrpercent);

// Others
std::function<CF_LRU()> CfLRUGenerator(int percentage);
std::function<LRU_WSR()> LRU_WSR_Generator();
std::function<hyperbolic()> Hyperbolic_generator(uint randSize);
std::function<LFU_K()> LFU_K_Generator(int K);
std::function<LFU_K_Z()> LFU_K_Z_Generator(int K, int out_of_ram_history_length);
std::function<LFU2_K_Z()> LFU2_K_Z_Generator(int K, int out_of_ram_history_length);
std::function<LFUalt_K()> LFUalt_K_Generator(int K);
std::function<LRU_K_Z()> LRU_K_Z_Generator(int K, int out_of_ram_history_length);
std::function<LFU_2K_Z()> LFU_2K_Z_Generator(uint K_read, uint K_write, int out_of_ram_history_length, bool writes_as_reads);
std::function<LFU_2K_Z_rand()> LFU_2K_Z_rand_Generator(uint K_read, uint K_write, int out_of_ram_history_length, uint randSize, bool writes_as_reads);
std::function<LFU_1K_E_real()> LFU_1K_E_real_Generator(uint K, uint epoch_size, uint randSize, uint randSelector, uint write_cost, int Z);
std::function<LFU_1K_E_real_vers2()> LFU_1K_E_Generator(uint K, uint epoch_size, uint randSize, uint randSelector, uint write_cost, int Z);
std::function<LFU_2K_E_real_ver2()>
LFU_2K_E_real2_Generator(uint KR, uint KW, uint epoch_size, uint randSize, uint randSelector, bool write_as_read,
                         uint writeCost);
std::function<LFU_2K_E_real()>
LFU_2K_E_real_Generator(uint KR, uint KW, uint epoch_size, uint randSize, uint randSelector, bool write_as_read,
                        float write_cost=1, float first_value=1.0, modus mod=mod_max, int Z=-1);
inline std::function<LFU_2K_E_real()>
LFU_Generator(uint KR, uint KW, uint epoch_size, uint randSize, uint randSelector, bool write_as_read, float writeCost=1, float first_value=1.0, modus mod=mod_max, int Z=-1){
    return LFU_2K_E_real_Generator(KR, KW, epoch_size, randSize, randSelector, write_as_read, writeCost, first_value,
                                   mod, Z);
}

std::function<leanEvict()> Lean_Generator(uint cooling_percentage);
std::function<leanEvict2()> Lean_Generator2(uint cooling_percentage);

std::function<LRFU()>
LRFU_Generator(double lambda, uint K);

std::function<ARC()> ARC_Generator();

//std::function<LFU_K_Z_D()> LFU1_K_Z_D_Generator(int K, int Z, int D);
// std::function<LFU2_K_Z_D()> LFU2_K_Z_D_Generator(int K, int Z, int D);

// Redundant ones (differ in implementation)
std::function<LRU()> LRU_Generator();
std::function<LRU1()> LRU1_Generator();
std::function<LRU2()> LRU2_Generator();
std::function<LRU2a()> LRU2a_Generator();
std::function<LRU2b()> LRU2b_Generator();
std::function<LRU3()> LRU3_Generator();

std::function<OPT2()> Opt2_Generator();

// Old and unused
// Has no out_of_memory_history
std::function<LRUalt_K()> LRUalt_K_Generator(int K);

// Broken ones
std::function<OPT3()> Opt3_Generator();