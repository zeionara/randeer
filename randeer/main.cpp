#include <iostream>
#include <functional>
#include <unordered_map>

#include "randomizer/LoopingRandomizer.h"
#include "state/DefaultRandomizationState.h"
#include "state/JavaLikeLcgRandomizationState.h"

#include "lcg.h"

unordered_map<long, Randomizer*> randomizers;

using namespace std;

enum RandomizerType {
    DEFAULT_LOOPING = 0,
    JAVA_LOOPING = 1
};

extern "C"
void init(long id, long seed, long type) {
    Randomizer* randomizer;

    if (auto existing_randomizer = randomizers.find(id); existing_randomizer != randomizers.end()) {
        printf("Already initialized randomizer with id %ld", id);
        throw "Cannot overwrite existing randomizer";
    }

    switch (type) {
        case DEFAULT_LOOPING:
            randomizer = new LoopingRandomizer(new DefaultRandomizationState(seed));
            break;
        case JAVA_LOOPING:
            randomizer = new LoopingRandomizer(new JavaLikeLcgRandomizationState(seed));
            break;
    }

    randomizers[id] = randomizer;
}

extern "C"
void init_in_interval_excluding_task(long id, long min, long max, long* excluded, long length) {
    Randomizer* randomizer;

    if (auto existing_randomizer = randomizers.find(id); existing_randomizer == randomizers.end()) {
        printf("Cannot find randomizer with id %ld", id);
        throw "Cannot find randomizer";
    } else
        existing_randomizer->second->initNextInIntervalExcludingContext(min, max, excluded, length);
}

extern "C"
long next(long id) {
    Randomizer* randomizer;

    if (auto existing_randomizer = randomizers.find(id); existing_randomizer == randomizers.end()) {
        printf("Cannot find randomizer with id %ld", id);
        throw "Cannot find randomizer";
    } else
        return existing_randomizer->second->next();
}


// deprecated

extern "C"
void sample(long number = 0) {
    cout << number << endl;
}

extern "C"
void seed(long seed = 0) {
    srand(seed);
    lastNumber = seed;
}

extern "C"
long sample_by_looping_randomizer(long min, long max, long* excluded, long length) {
    // return 10;
    // Randomizer* randomizer = new DefaultLoopingRandomizer(17);
    Randomizer* randomizer = new LoopingRandomizer(new DefaultRandomizationState(17));

    randomizer->initNextInIntervalExcludingContext(min, max, excluded, length);
    return randomizer->next();
}

extern "C"
long sample_by_looping(long min, long max, long* excluded, long length) {
    long diff = max - min + 1;
    // return diff;

    unordered_set<long> excluded_items = to_set(excluded, length);

    // for (long i = min; i <= max; i++) {
    while (true) {
        long randomNumber = min + rand() % diff;

        if (excluded_items.find(randomNumber) == excluded_items.end()) {
            return randomNumber;
        }
    }
}

extern "C"
long sample_by_looping_lcg(long min, long max, long* excluded, long length) {
    long diff = max - min + 1;
    // return diff;

    unordered_set<long> excluded_items = to_set(excluded, length);

    // for (long i = min; i <= max; i++) {
    while (true) {
        long randomNumber = min + random() % diff;

        if (excluded_items.find(randomNumber) == excluded_items.end()) {
            return randomNumber;
        }
    }
}

extern "C"
long sample_n_by_looping_without_init(long n, long min, long max, long* excluded, long length) {
    long diff = max - min + 1;
    // return diff;

    unordered_set<long> excluded_items = to_set(excluded, length);

    // for (long i = min; i <= max; i++) {
    long i = 0;

    while (i < n) {
        long randomNumber = min + rand() % diff;

        if (excluded_items.find(randomNumber) == excluded_items.end()) {
            i += 1;
            // return randomNumber;
        }
    }

    return i;
}

extern "C"
void sample_n(long n, function<long()> sample) {
    for (long i = 0; i < n; i++) {
        sample();
    }
}

extern "C"
void sample_n_by_looping_with_init(long n, long min, long max, long* excluded, long length) {
    sample_n(n, [&](){return sample_by_looping(min, max, excluded, length);});
}
