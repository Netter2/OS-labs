#include <stdio.h>
__declspec (dllimport) float Pi (int K);
__declspec (dllimport) float E (int x);

int main () {
    int var;
    scanf ("%d", &var);
    if (var == 1) {
        int K;
        scanf ("%d", &K);
        float ans = Pi (K);
        printf ("%f", ans);
    }
    else {
        int x;
        scanf ("%d", &x);
        float ans = E (x);
        printf ("%f", ans);
    }
    return 0;
}

//gcc -c -o _.o .\_.c;gcc -o _.dll -shared .\_.o
//gcc -c -o 1.o .\1.c;gcc -o 1.exe .\1.o -L. -lLeibniz -lX
//.\1.exe