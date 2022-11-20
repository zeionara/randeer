#ifndef STATE_LCG_RANDOMIZATION_STATE_H
#define STATE_LCG_RANDOMIZATION_STATE_H

#include <cstdlib>
#include <iostream>
#include <unistd.h>

#include"RandomizationState.h"

struct LcgRandomizationState: RandomizationState {
    unsigned long long multiplier, increment, modulus;

    LcgRandomizationState(long multiplier, long increment, long modulus): RandomizationState() {
        init(multiplier, increment, modulus);
    };

    LcgRandomizationState(long seed, long multiplier, long increment, long modulus): RandomizationState(seed) {
        init(multiplier, increment, modulus);
    };

    void init(long multiplier, long increment, long modulus) {
        this->multiplier = multiplier;
        this->increment = increment;
        this->modulus = modulus;
    }

    long sample() {
        // std::cout << "--" << std::endl;
        // std::cout << multiplier << std::endl;
        // std::cout << state << std::endl;
        // std::cout << increment << std::endl;
        // std::cout << modulus << std::endl;
        unsigned long result = (multiplier * state + increment) % modulus;
        // std::cout << result << std::endl;
        // usleep(1000000);
        reset(result);
        return result;
    }
};

#endif
