#include <cstdlib>

#include "utils/collection.h"
#include "utils/sampling.h"

extern "C"
long sample_lcg_by_looping(long min, long max, long* excluded, long length) {
    long diff = max - min + 1;

    unordered_set<long> excluded_items = to_set(excluded, length);

    while (true) {
        long randomNumber = min + random() % diff;

        if (excluded_items.find(randomNumber) == excluded_items.end()) {
            return randomNumber;
        }
    }
}

extern "C"
long sample_lcg_n_by_looping_without_init(long n, long min, long max, long* excluded, long length) {
    long diff = max - min + 1;

    unordered_set<long> excluded_items = to_set(excluded, length);

    long i = 0;

    while (i < n) {
        long randomNumber = min + random() % diff;

        if (excluded_items.find(randomNumber) == excluded_items.end()) {
            i += 1;
        }
    }

    return i;
}

extern "C"
void sample_lcg_n_by_looping_with_init(long n, long min, long max, long* excluded, long length) {
    sample_n(n, [&](){return sample_lcg_by_looping(min, max, excluded, length);});
}
