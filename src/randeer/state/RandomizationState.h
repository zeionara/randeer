#ifndef STATE_RANDOMIZATION_STATE_H
#define STATE_RANDOMIZATION_STATE_H

#include <iostream>

using random_state_t = unsigned long long;

template <typename T>
struct RandomizationState {
    random_state_t state;

    RandomizationState() {
        reset(0);
    }

    RandomizationState(random_state_t seed) {
        reset(seed);
    }

    random_state_t reset(random_state_t seed) {
        this->state = seed;
        return seed;
    }

    T sample() {
        return sample_();
    }

    T sample(T max) {  // Sample value in interval [0; max)
        return sample_() % max;
    }

    T sample(T min, T max) {  // Sample value in interval [min; max)
        return min + sample(max - min);
    }

    private:

        virtual random_state_t sample_() = 0;
};

#endif
