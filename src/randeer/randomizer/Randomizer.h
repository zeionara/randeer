#ifndef RANDOMIZER_RANDOMIZER_H
#define RANDOMIZER_RANDOMIZER_H

#include <iostream>

#include "../state/RandomizationState.h"

#include "RandomizationTask.h"

template <typename T>
struct Randomizer {
    RandomizationTask task;
    RandomizationState<T>* state;
 
    Randomizer(RandomizationState<T>* state) {
        this->state = state;
    }
 
    T next() {
        switch (task) {
            case IN_INTERVAL_EXCLUDING:
                return nextInIntervalExcluding();
                break;
            default:
                printf("Wrong task identifier %u, cannot initialize randomization task", task);
                throw "Cannot initialize randomization task";
        }
    }
 
    void setTask(RandomizationTask task, void* context) {
        this->task = task;
        this->context = context;
    }

    virtual void initNextInIntervalExcludingContext(T min, T max, T* excluded, long length) = 0;
    virtual T nextInIntervalExcluding() = 0;

    protected:

        void* context;
};

#endif
