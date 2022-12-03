#ifndef STATE_RANDOMIZATION_STATE_H
#define STATE_RANDOMIZATION_STATE_H

#include <iostream>

template <typename T>
struct RandomizationState {
    long long state;

    RandomizationState() {
        reset(0);
    }

    RandomizationState(long long seed) {
        reset(seed);
    }

    long long reset(long long seed) {
        // std::cout << "resetting state" << std::endl;
        this->state = seed;
        // std::cout << this->state << std::endl;
        return seed;
    }

    virtual T sample() = 0;

    T sample(T max) {  // Sample value in interval [0; max)
        return sample() % max;
    }

    T sample(T min, T max) {  // Sample value in interval [min; max)
        return min + sample(max - min);
    }

};

#endif
