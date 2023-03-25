#ifndef RANDOMIZER_SHIFTING_RANDOMIZER_H
#define RANDOMIZER_SHIFTING_RANDOMIZER_H

#include "../utils/collection.h"
#include "Randomizer.h"


template <typename T>
struct InIntervalExcludingShiftingRandomizationTaskContext {
    // T diff;
    T min;
    T maxShifted;
    T* excludedItems;
    long nExcluded;

    T smallestExcluded;
    T greatestExcluded;

    T greatestExcludedMinusNexcluded;

    InIntervalExcludingShiftingRandomizationTaskContext(T min, T max, T* excluded, long length) {
        this->min = min;
        // diff = max - min + 1;

        excludedItems = sortAndShift(excluded, length, -min);
        maxShifted = max - min - length;
        this->nExcluded = length;

        smallestExcluded = excludedItems[0];
        greatestExcluded = excludedItems[length - 1];

        greatestExcludedMinusNexcluded = greatestExcluded - nExcluded;
    }

    ~InIntervalExcludingShiftingRandomizationTaskContext() {
        delete [] excludedItems;
    }
};

template <typename T>
struct ShiftingRandomizer: Randomizer<T> {

    ShiftingRandomizer(RandomizationState<T>* state): Randomizer<T>(state) {}

    virtual void initNextInIntervalExcludingContext(T min, T max, T* excluded, long length) {
        this->setTask(
            IN_INTERVAL_EXCLUDING,
            (void*) new InIntervalExcludingShiftingRandomizationTaskContext(min, max, excluded, length)
        );
    }

    T nextInIntervalExcluding() {
        InIntervalExcludingShiftingRandomizationTaskContext<T>* context = (InIntervalExcludingShiftingRandomizationTaskContext<T>*) this->context;

        T number = this->state->sample(context->maxShifted + 1);

        // if sampled number on the left to the excluded numbers sequence

        if (number < context->smallestExcluded) // <= greatest not excluded before the first excluded
            return context->min + number;

        // if sampled number on the right to the excluded numbers sequence

        if (number > context->greatestExcludedMinusNexcluded) // > greatest not excluded before the first excluded in case excluded numbers are consequitive numbers like 1, 2, 3, 4, ...
            return context->min + number + context->nExcluded;

        // if sampled number between members of the excluded numbers sequence

        long leftmostExcludedIndex = 0;
        long rightmostExcludedIndex = context->nExcluded - 1;

        long middleExcludedIndex = 0;

        while (leftmostExcludedIndex + 1 < rightmostExcludedIndex) {
            middleExcludedIndex = (leftmostExcludedIndex + rightmostExcludedIndex) >> 1;
            if (context->excludedItems[middleExcludedIndex] - (middleExcludedIndex + 1) < number) {
                leftmostExcludedIndex = middleExcludedIndex;
            } else {
                rightmostExcludedIndex = middleExcludedIndex;
            }
        }

        return context->min + number + leftmostExcludedIndex + 1;
    }
};

#endif
