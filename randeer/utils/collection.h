#ifndef UTILS_COLLECTION
#define UTILS_COLLECTION

#include <unordered_set>
using namespace std;

// template <typename T>

// unordered_set<T> to_set(T* array, long length);

// unordered_set<long> to_set(long* array, long length);

template <typename T>

unordered_set<T> to_set(T* array, long length) {
    unordered_set<T> items;

    for (long i = 0; i < length; i++) {
        items.insert(array[i]);
    }

    return items;
}

#endif
