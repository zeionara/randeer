#include <cstdlib>

#include "utils/collection.h"
#include "utils/sampling.h"

#include "lcg.h"

#include "randomizer/LoopingRandomizer.h"
#include "state/DefaultRandomizationState.h"

extern "C"
long sample_default_by_looping_using_objects(long min, long max, long* excluded, long length) {
    Randomizer* randomizer = new LoopingRandomizer(new DefaultRandomizationState(randomizerSeed));

    randomizer->initNextInIntervalExcludingContext(min, max, excluded, length);
    return randomizer->next();
}

extern "C"
long sample_default_n_by_looping_without_init_using_objects(long n, long min, long max, long* excluded, long length) {
    Randomizer* randomizer = new LoopingRandomizer(new DefaultRandomizationState(randomizerSeed));

    randomizer->initNextInIntervalExcludingContext(min, max, excluded, length);

    long diff = max - min + 1;

    unordered_set<long> excluded_items = to_set(excluded, length);

    long i = 0;

    while (i < n) {
        long randomNumber = randomizer->next();

        i += 1;
    }

    return i;
}

extern "C"
void sample_default_n_by_looping_with_init_using_objects(long n, long min, long max, long* excluded, long length) {
    sample_n(n, [&](){return sample_default_by_looping_using_objects(min, max, excluded, length);});
}
