#include "../src/randeer/state/JavaLikeLcgRandomizationState.h"

using namespace std;

int main() {
    auto state = JavaLikeLcgRandomizationState<long>(17);

    auto number = state.sample();

    if (number != 428653366600) {
        return 1;
    }

    number = state.sample();

    if (number != 120313015605171) {
        return 1;
    }

    number = state.sample();

    if (number != 44860430444866) {
        return 1;
    }

    return 0;
}
