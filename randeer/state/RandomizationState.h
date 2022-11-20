#ifndef STATE_RANDOMIZATION_STATE_H
#define STATE_RANDOMIZATION_STATE_H

#include <iostream>

struct RandomizationState {
    long long state;

    RandomizationState() {
        reset(0);
    }

    RandomizationState(long seed) {
        reset(seed);
    }

    long reset(long seed) {
        // std::cout << "resetting state" << std::endl;
        this->state = seed;
        // std::cout << this->state << std::endl;
        return seed;
    }

    virtual long sample() = 0;
};

#endif
