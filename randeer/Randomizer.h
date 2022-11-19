#ifndef RANDOMIZER_H
#define RANDOMIZER_H

#include <iostream>
#include "utils/collection.h"

enum RandomizationTask {
    IN_INTERVAL_EXCLUDING
};

struct InIntervalExcludingLoopingRandomizationTaskContext {
    long diff;
    long min;
    unordered_set<long> excluded_items;

    InIntervalExcludingLoopingRandomizationTaskContext(long min, long max, long* excluded, long length) {
        this->min = min;
        diff = max - min + 1;
        excluded_items = to_set(excluded, length);
    }
};

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

    virtual long randa() = 0;
};

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

    long randa() {
        return rand();
    }
};


struct Randomizer {
     void* context;
     RandomizationTask task;

     RandomizationState* state;
 
     Randomizer(RandomizationState* state) {
         this->state = state;
     }
 
     long sample() {
         switch (task) {
             case IN_INTERVAL_EXCLUDING:
                 return nextInIntervalExcluding();
                 break;
         }

     }
 
     long next() {
         return this->state->reset(sample());
     }
 
     void setTask(RandomizationTask task, void* context) {
         this->task = task;
         this->context = context;
     }

     virtual void initNextInIntervalExcludingContext(long min, long max, long* excluded, long length) = 0;
     virtual long nextInIntervalExcluding() = 0;
};

struct LoopingRandomizer: Randomizer {  //: Randomizer {
    // void* context;
    // RandomizationTask task;

    // long state;

    LoopingRandomizer(RandomizationState* state): Randomizer(state) {}

    // void reset(long seed) {
    //     this->state = seed;
    // }

    // long next() {
    //     switch (task) {
    //         case IN_INTERVAL_EXCLUDING:
    //             return nextInIntervalExcluding();
    //             break;
    //     }
    // }

    // void setTask(RandomizationTask task, void* context) {
    //     this->task = task;
    //     this->context = context;
    // }

    virtual void initNextInIntervalExcludingContext(long min, long max, long* excluded, long length) {
        setTask(
            IN_INTERVAL_EXCLUDING,
            (void*) new InIntervalExcludingLoopingRandomizationTaskContext(min, max, excluded, length)
        );
    }

    long nextInIntervalExcluding() {
        InIntervalExcludingLoopingRandomizationTaskContext* context = (InIntervalExcludingLoopingRandomizationTaskContext*) this->context;

        long number;
        
        while (true) {
            number = context->min + this->state->randa() % context->diff;

            if (context->excluded_items.find(number) == context->excluded_items.end()) {
                return number;
            }
        }


        return number;
    }
};

#endif
