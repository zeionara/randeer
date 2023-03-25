#ifndef STATE_LCG_RANDOMIZATION_STATE_H
#define STATE_LCG_RANDOMIZATION_STATE_H

#include <cstdlib>
#include <iostream>
#include <unistd.h>

#include"RandomizationState.h"

template <typename T>
struct LcgRandomizationState: RandomizationState<T> {
    random_state_t multiplier, increment, modulus;

    LcgRandomizationState(random_state_t multiplier, random_state_t increment, random_state_t modulus): RandomizationState<T>() {
        init(multiplier, increment, modulus);
    };

    LcgRandomizationState(random_state_t seed, random_state_t multiplier, random_state_t increment, random_state_t modulus): RandomizationState<T>(seed) {
        init(multiplier, increment, modulus);
    };

    private:

        void init(random_state_t multiplier, random_state_t increment, random_state_t modulus) {
            this->multiplier = multiplier;
            this->increment = increment;
            this->modulus = modulus;
        }

        random_state_t sample_() {
            random_state_t result = (multiplier * this->state + increment) % modulus;
            this->reset(result);
            return result;
        }
};

#endif
