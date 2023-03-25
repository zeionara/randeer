#ifndef STATE_DEFAULT_RANDOMIZATION_STATE_H
#define STATE_DEFAULT_RANDOMIZATION_STATE_H

#include <cstdlib>

#include"RandomizationState.h"

template <typename T>
struct DefaultRandomizationState: RandomizationState<T> {

    DefaultRandomizationState() {
        reset(0);
    };

    DefaultRandomizationState(random_state_t seed) {
        reset(seed);
    };

    random_state_t reset(random_state_t seed) {
        srand(seed);
        return RandomizationState<T>::reset(seed);
    }

    private:

        random_state_t sample_() {
            return rand();
        }
};

#endif
