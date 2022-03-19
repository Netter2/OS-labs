#include <math.h>

float revfactorial(int count){
    float res = 1;
    for (int i = 1; i <= count; i++) {
        res /= i;
    }
    return res;
}

__declspec (dllexport) float  E (int x) {
    float e = 0;
    for (int n = 0; n <= x; n ++) {
        e += revfactorial (n);
    }
    return e;
}