#include <functional>

using namespace std;

extern "C"
void sample_n(long n, function<long()> sample);
