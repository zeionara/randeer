#ifndef UTILS_COLLECTION
#define UTILS_COLLECTION

#include <unordered_set>
#include <algorithm>

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

template <typename T>
T* sortAndShift(T* array, long& length, T offset) {
    T* sorted = new T[length];

    // copy(array, array + length, sorted);

    for (long i = 0; i < length; i++)
        sorted[i] = array[i] + offset;

    sort(sorted, sorted + length);

    long j = 0;
    for (long i = 1; i < length; i++)
        if (sorted[i] > sorted[i - 1])
            sorted[++j] = sorted[i];

    length = j + 1;

    return sorted;
}

#endif
