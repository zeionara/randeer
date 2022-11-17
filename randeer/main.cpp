#include <iostream>
#include "utils/collection.h"

using namespace std;

extern "C"
void sample(long number = 0) {
    cout << number << endl;
}

extern "C"
void seed(long seed = 0) {
    srand(seed);
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
long sample_n_by_looping(long n, long min, long max, long* excluded, long length) {
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

