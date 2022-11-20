#ifndef STATE_LCG_RANDOMIZATION_STATE_H
#define STATE_LCG_RANDOMIZATION_STATE_H

#include <cstdlib>

#include"RandomizationState.h"

struct LcgRandomizationState: RandomizationState {
    long multiplier, increment, modulus;

    LcgRandomizationState(long multiplier, long increment, long modulus): RandomizationState() {
        init(multiplier, increment, modulus);
    };

    LcgRandomizationState(long seed, long multiplier, long increment, long modulus): RandomizationState(seed) {
        init(multiplier, increment, modulus);
    };

    void init(long multiplier, long increment, long modulus) {
        this->multiplier = multiplier;
        this->increment = increment;
        this->increment = modulus;
    }

    long sample() {
        return (multiplier * state + increment) % modulus;
    }
};

#endif
