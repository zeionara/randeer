#ifndef STATE_JAVA_LIKE_LCG_RANDOMIZATION_STATE_H
#define STATE_JAVA_LIKE_LCG_RANDOMIZATION_STATE_H

#include <cstdlib>

#include"LcgRandomizationState.h"

extern
long JAVA_LIKE_LCG_MULTIPLIER, JAVA_LIKE_LCG_INCREMENT, JAVA_LIKE_LCG_MODULUS;

struct JavaLikeLcgRandomizationState: LcgRandomizationState {
    long multiplier, increment, modulus;

    JavaLikeLcgRandomizationState(): LcgRandomizationState(JAVA_LIKE_LCG_MULTIPLIER, JAVA_LIKE_LCG_INCREMENT, JAVA_LIKE_LCG_MODULUS) {};

    JavaLikeLcgRandomizationState(long seed): LcgRandomizationState(seed, JAVA_LIKE_LCG_MULTIPLIER, JAVA_LIKE_LCG_INCREMENT, JAVA_LIKE_LCG_MODULUS) {};

};

#endif
