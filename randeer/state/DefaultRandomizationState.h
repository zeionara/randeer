#ifndef STATE_DEFAULT_RANDOMIZATION_STATE_H
#define STATE_DEFAULT_RANDOMIZATION_STATE_H

#include <cstdlib>

#include"RandomizationState.h"

template <typename T>
struct DefaultRandomizationState: RandomizationState<T> {

    DefaultRandomizationState() {
        reset(0);
    };

    DefaultRandomizationState(long long seed) {
        reset(seed);
    };

    long long reset(long long seed) {
        srand(seed);
        return RandomizationState<T>::reset(seed);
    }

    T sample() {
        return rand();
    }
};

#endif
