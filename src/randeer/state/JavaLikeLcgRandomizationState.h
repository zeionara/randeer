#ifndef STATE_JAVA_LIKE_LCG_RANDOMIZATION_STATE_H
#define STATE_JAVA_LIKE_LCG_RANDOMIZATION_STATE_H

#include <cstdlib>

#include"LcgRandomizationState.h"

extern
random_state_t JAVA_LIKE_LCG_MULTIPLIER, JAVA_LIKE_LCG_INCREMENT, JAVA_LIKE_LCG_MODULUS;

template <typename T>
struct JavaLikeLcgRandomizationState: LcgRandomizationState<T> {
    random_state_t multiplier, increment, modulus;

    JavaLikeLcgRandomizationState(): LcgRandomizationState<T>(JAVA_LIKE_LCG_MULTIPLIER, JAVA_LIKE_LCG_INCREMENT, JAVA_LIKE_LCG_MODULUS) {};

    JavaLikeLcgRandomizationState(T seed): LcgRandomizationState<T>(seed, JAVA_LIKE_LCG_MULTIPLIER, JAVA_LIKE_LCG_INCREMENT, JAVA_LIKE_LCG_MODULUS) {};
};

#endif
