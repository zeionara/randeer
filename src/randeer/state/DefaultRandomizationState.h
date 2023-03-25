#ifndef STATE_DEFAULT_RANDOMIZATION_STATE_H
#define STATE_DEFAULT_RANDOMIZATION_STATE_H

#include <cstdlib>

#include"RandomizationState.h"

template <typename T>
struct DefaultRandomizationState: RandomizationState<T> {

    DefaultRandomizationState() {
        reset(0);
    };

    DefaultRandomizationState(unsigned long long seed) {
        reset(seed);
    };

    unsigned long long reset(unsigned long long seed) {
        srand(seed);
        return RandomizationState<T>::reset(seed);
    }

    unsigned long long sample_() {
        return rand();
    }
};

#endif
