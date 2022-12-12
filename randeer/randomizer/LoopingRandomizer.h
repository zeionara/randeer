#ifndef RANDOMIZER_LOOPING_RANDOMIZER_H
#define RANDOMIZER_LOOPING_RANDOMIZER_H

#include "Randomizer.h"

template <typename T>
struct InIntervalExcludingLoopingRandomizationTaskContext {
    T diff;
    T min;
    unordered_set<T> excluded_items;

    InIntervalExcludingLoopingRandomizationTaskContext(T min, T max, T* excluded, long length) {
        this->min = min;
        diff = max - min + 1;
        excluded_items = to_set(excluded, length);
    }
};

template <typename T>
struct LoopingRandomizer: Randomizer<T> {

    LoopingRandomizer(RandomizationState<T>* state): Randomizer<T>(state) {}

    virtual void initNextInIntervalExcludingContext(T min, T max, T* excluded, long length) {
        this->setTask(
            IN_INTERVAL_EXCLUDING,
            (void*) new InIntervalExcludingLoopingRandomizationTaskContext(min, max, excluded, length)
        );
    }

    T nextInIntervalExcluding() {
        InIntervalExcludingLoopingRandomizationTaskContext<T>* context = (InIntervalExcludingLoopingRandomizationTaskContext<T>*) this->context;

        T number;
        
        while (true) {
            number = context->min + this->state->sample(context->diff);

            // cout << number << endl;

            if (context->excluded_items.find(number) == context->excluded_items.end()) {
                return number;
            }
        }

        return number;
    }
};

#endif
