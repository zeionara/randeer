#include "../src/randeer/state/LcgRandomizationState.h"

using namespace std;

int main() {
    auto state = LcgRandomizationState<long>(3, 2, 3, 10);

    auto number = state.sample();

    if (number != 9) {
        return 1;
    }

    number = state.sample();

    if (number != 1) {
        return 1;
    }

    number = state.sample();

    if (number != 5) {
        return 1;
    }

    return 0;
}
