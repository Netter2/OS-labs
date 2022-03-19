#include <stdio.h>
#include <math.h>

float revfactorial(int count){
    float res = 1;
    for (int i = 1; i <= count; i++) {
        res /= i;
    }
    return res;
}

float  E (int x) {
    float e = 0;
    for (int n = 0; n <= x; n ++) {
        e += revfactorial (n);
    }
    return e;
}

float Pi (int K) {
    float pi = 1;
    float i = 1;
    while (i <= K) {
        pi *= ((4.0 * i * i) / (4 * i * i - 1));
        i ++;
    }
    pi *= 2;
    return pi;
}

int main () {
    float ans = E (50);
    printf ("%f", ans);
    return 0;
}