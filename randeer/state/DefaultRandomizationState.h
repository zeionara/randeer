#ifndef STATE_DEFAULT_RANDOMIZATION_STATE_H
#define STATE_DEFAULT_RANDOMIZATION_STATE_H

#include <cstdlib>

#include"RandomizationState.h"

struct DefaultRandomizationState: RandomizationState {
    long state;

    DefaultRandomizationState() {
        reset(0);
    };

    DefaultRandomizationState(long seed) {
        reset(seed);
    };

    long reset(long seed) {
        srand(seed);
        return RandomizationState::reset(seed);
    }

    long sample() {
        return rand();
    }
};

#endif
