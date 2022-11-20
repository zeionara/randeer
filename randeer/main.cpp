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
        cout << endl;
        printf("Already initialized randomizer with id %ld, cannot overwrite it", id);
        cout << endl;
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
        cout << endl;
        printf("Cannot find randomizer with id %ld", id);
        cout << endl;
        throw "Cannot find randomizer";
    } else
        existing_randomizer->second->initNextInIntervalExcludingContext(min, max, excluded, length);
}

extern "C"
long next(long id) {
    Randomizer* randomizer;

    if (auto existing_randomizer = randomizers.find(id); existing_randomizer == randomizers.end()) {
        cout << endl;
        printf("Cannot find randomizer with id %ld", id);
        cout << endl;
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
    randomizerSeed = seed;
}
