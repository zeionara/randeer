#include "sampling.h"

void sample_n(long n, function<long()> sample) {
    for (long i = 0; i < n; i++) {
        sample();
    }
}
