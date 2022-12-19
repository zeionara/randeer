#ifndef RANDOMIZER_CONSTRAINED_SHIFTING_RANDOMIZER_H
#define RANDOMIZER_CONSTRAINED_SHIFTING_RANDOMIZER_H

#include "Randomizer.h"


template <typename T>
struct InIntervalExcludingConstrainedShiftingRandomizationTaskContext {
    // T diff;
    T min;
    T maxShifted;
    T* excludedItems;
    long nExcluded;

    T smallestExcluded;
    T greatestExcluded;

    T greatestExcludedMinusNexcluded;

    InIntervalExcludingConstrainedShiftingRandomizationTaskContext(T min, T max, T* excluded, long length) {
        this->min = min;

        excludedItems = excluded;
        maxShifted = max - length;
        this->nExcluded = length;

        smallestExcluded = excludedItems[0];
        greatestExcluded = excludedItems[length - 1];

        greatestExcludedMinusNexcluded = greatestExcluded - nExcluded;
    }
};

template <typename T>
struct ConstrainedShiftingRandomizer: Randomizer<T> {

    ConstrainedShiftingRandomizer(RandomizationState<T>* state): Randomizer<T>(state) {}

    virtual void initNextInIntervalExcludingContext(T min, T max, T* excluded, long length) {
        this->setTask(
            IN_INTERVAL_EXCLUDING,
            (void*) new InIntervalExcludingConstrainedShiftingRandomizationTaskContext(min, max, excluded, length)
        );
    }

    T nextInIntervalExcluding() {
        InIntervalExcludingConstrainedShiftingRandomizationTaskContext<T>* context = (InIntervalExcludingConstrainedShiftingRandomizationTaskContext<T>*) this->context;

        T number = this->state->sample(context->min, context->maxShifted + 1);

        // if sampled number on the left to the excluded numbers sequence

        if (number < context->smallestExcluded) // <= greatest not excluded before the first excluded
            return number;

        // if sampled number on the right to the excluded numbers sequence

        if (number > context->greatestExcludedMinusNexcluded) // > greatest not excluded before the first excluded in case excluded numbers are consequitive numbers like 1, 2, 3, 4, ...
            return number + context->nExcluded;

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

        return number + leftmostExcludedIndex + 1;
    }
};

#endif
