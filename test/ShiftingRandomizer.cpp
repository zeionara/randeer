#include "../src/randeer/randomizer/ShiftingRandomizer.h"
#include "../src/randeer/state/DefaultRandomizationState.h"

using namespace std;

int main() {
    Randomizer<long>* randomizer = new ShiftingRandomizer<long>(new DefaultRandomizationState<long>(17));

    long excluding[] = {3, 7, 9};
    auto excluding_set = to_set(excluding, 3);

    long min = 2;
    long max = 10;

    long nMin = 0;
    long nMax = 0;

    randomizer->initNextInIntervalExcludingContext(min, max, excluding, 3);

    for (int i = 0; i < 100; i++) {
        auto number = randomizer->next();

        if (number < min || number > max || excluding_set.find(number) != excluding_set.end()) return 1;  // Generated numbers should not match any element of the "excluding" list

        if (number == min) nMin++;
        if (number == max) nMax++;
    }

    if (nMax < 1) return 1;  // lower boundary must be generated at least once
    if (nMin < 1) return 1;  // upper boundary must be generated at least once

    return 0;
}
