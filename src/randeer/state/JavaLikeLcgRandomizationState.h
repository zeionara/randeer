#ifndef STATE_JAVA_LIKE_LCG_RANDOMIZATION_STATE_H
#define STATE_JAVA_LIKE_LCG_RANDOMIZATION_STATE_H

#include <cstdlib>

#include"LcgRandomizationState.h"

extern
unsigned long long JAVA_LIKE_LCG_MULTIPLIER, JAVA_LIKE_LCG_INCREMENT, JAVA_LIKE_LCG_MODULUS;

template <typename T>
struct JavaLikeLcgRandomizationState: LcgRandomizationState<T> {
    unsigned long long multiplier, increment, modulus;

    JavaLikeLcgRandomizationState(): LcgRandomizationState<T>(JAVA_LIKE_LCG_MULTIPLIER, JAVA_LIKE_LCG_INCREMENT, JAVA_LIKE_LCG_MODULUS) {};

    JavaLikeLcgRandomizationState(long seed): LcgRandomizationState<T>(seed, JAVA_LIKE_LCG_MULTIPLIER, JAVA_LIKE_LCG_INCREMENT, JAVA_LIKE_LCG_MODULUS) {};

};

#endif
