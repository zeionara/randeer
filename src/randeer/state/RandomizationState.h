#ifndef STATE_RANDOMIZATION_STATE_H
#define STATE_RANDOMIZATION_STATE_H

#include <iostream>

template <typename T>
struct RandomizationState {
    unsigned long long state;

    RandomizationState() {
        reset(0);
    }

    RandomizationState(unsigned long long seed) {
        reset(seed);
    }

    unsigned long long reset(unsigned long long seed) {
        // std::cout << "resetting state" << std::endl;
        this->state = seed;
        // std::cout << this->state << std::endl;
        return seed;
    }

    virtual unsigned long long sample_() = 0;

    T sample() {
        return sample_();
    }

    T sample(T max) {  // Sample value in interval [0; max)
        return sample_() % max;
    }

    T sample(T min, T max) {  // Sample value in interval [min; max)
        return min + sample(max - min);
    }

};

#endif
