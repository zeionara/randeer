#ifndef STATE_LCG_RANDOMIZATION_STATE_H
#define STATE_LCG_RANDOMIZATION_STATE_H

#include <cstdlib>
#include <iostream>
#include <unistd.h>

#include"RandomizationState.h"

template <typename T>
struct LcgRandomizationState: RandomizationState<T> {
    unsigned long long multiplier, increment, modulus;

    LcgRandomizationState(unsigned long long multiplier, unsigned long long increment, unsigned long long modulus): RandomizationState<T>() {
        init(multiplier, increment, modulus);
    };

    LcgRandomizationState(unsigned long long seed, unsigned long long multiplier, unsigned long long increment, unsigned long long modulus): RandomizationState<T>(seed) {
        init(multiplier, increment, modulus);
    };

    void init(unsigned long long multiplier, unsigned long long increment, unsigned long long modulus) {
        this->multiplier = multiplier;
        this->increment = increment;
        this->modulus = modulus;
    }

    unsigned long long sample_() {
        // std::cout << "--" << std::endl;
        // std::cout << multiplier << std::endl;
        // std::cout << state << std::endl;
        // std::cout << increment << std::endl;
        // std::cout << modulus << std::endl;
        // unsigned long result = (multiplier * this->state + increment) % modulus;
        unsigned long long result = (multiplier * this->state + increment) % modulus;
        // std::cout << result << std::endl;
        // usleep(1000000);
        this->reset(result);
        // return (T)result;
        return result;
    }
};

#endif
