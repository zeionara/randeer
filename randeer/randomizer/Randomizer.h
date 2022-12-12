#ifndef RANDOMIZER_H
#define RANDOMIZER_H

#include <iostream>

#include "../utils/collection.h"
#include "../state/RandomizationState.h"

#include "RandomizationTask.h"

template <typename T>
struct Randomizer {
     void* context;
     RandomizationTask task;

     RandomizationState<T>* state;
 
     Randomizer(RandomizationState<T>* state) {
         this->state = state;
     }
 
     // long sample() {
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
 
     // long next() {
     //     long value = sample();
     //     // cout << "In method randomizer.next" << endl;
     //     // cout << value << endl;
     //     // return this->state->reset(value);
     //     return value;
     // }
 
     void setTask(RandomizationTask task, void* context) {
         this->task = task;
         this->context = context;
     }

     virtual void initNextInIntervalExcludingContext(T min, T max, T* excluded, long length) = 0;
     virtual T nextInIntervalExcluding() = 0;
};

#endif
