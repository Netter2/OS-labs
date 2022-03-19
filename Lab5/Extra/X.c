#include <math.h>
__declspec (dllexport) float  E (int x) {
    float e = pow((1 + 1.0 / x), x);
    return e;
}