#ifndef STATE_RANDOMIZATION_STATE_H
#define STATE_RANDOMIZATION_STATE_H

struct RandomizationState {
    long state;

    RandomizationState() {
        reset(0);
    }

    RandomizationState(long seed) {
        reset(seed);
    }

    long reset(long seed) {
        this->state = seed;
        return seed;
    }

    virtual long sample() = 0;
};

#endif
