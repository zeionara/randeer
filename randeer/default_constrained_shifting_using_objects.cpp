#include <cstdlib>

#include "utils/collection.h"
#include "utils/sampling.h"

#include "lcg.h"

#include "randomizer/ShiftingRandomizer.h"
#include "randomizer/ConstrainedShiftingRandomizer.h"
#include "state/DefaultRandomizationState.h"

extern "C"
long sample_default_by_constrained_shifting_using_objects(long min, long max, long* excluded, long length) {
    Randomizer<long>* randomizer = new ConstrainedShiftingRandomizer<long>(new DefaultRandomizationState<long>(randomizerSeed));

    randomizer->initNextInIntervalExcludingContext(min, max, excluded, length);
    return randomizer->next();
}

extern "C"
long sample_default_n_by_constrained_shifting_without_init_using_objects(long n, long min, long max, long* excluded, long length) {
    Randomizer<long>* randomizer = new ConstrainedShiftingRandomizer<long>(new DefaultRandomizationState<long>(randomizerSeed));

    randomizer->initNextInIntervalExcludingContext(min, max, excluded, length);

    for (long i = 0; i < n; i++) {
        randomizer->next();
    }

    return n;
}

extern "C"
void sample_default_n_by_constrained_shifting_with_init_using_objects(long n, long min, long max, long* excluded, long length) {
    sample_n(n, [&](){return sample_default_by_constrained_shifting_using_objects(min, max, excluded, length);});
}
