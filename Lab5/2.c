#include <stdio.h>
#include <windows.h>

typedef float (*ItoF) (int A);


int main () {
    int flag = 1;
    HINSTANCE libPi;
    ItoF pi;
    libPi = LoadLibrary ("Leibniz.dll");
    pi = (ItoF) GetProcAddress (libPi, "Pi");

    HINSTANCE libE;
    ItoF e;
    libE = LoadLibrary ("X.dll");
    e = (ItoF) GetProcAddress (libE, "E");

    while (1) {
        int in;
        scanf ("%d", &in);
        if (in == 0) {
            if (flag == 1) {
                FreeLibrary (libPi);
                FreeLibrary (libE);
                libPi = LoadLibrary ("Leibniz.dll");
                pi = (ItoF) GetProcAddress (libPi, "Pi");
                libE = LoadLibrary ("X.dll");
                e = (ItoF) GetProcAddress (libE, "E");
                flag = 2;
            }
            else {
                FreeLibrary (libPi);
                FreeLibrary (libE);
                libPi = LoadLibrary ("Vallis.dll");
                pi = (ItoF) GetProcAddress (libPi, "Pi");
                libE = LoadLibrary ("SeriesSum.dll");
                e = (ItoF) GetProcAddress (libE, "E");
                flag = 1;
            }
        }
        else if (in == 1) {
            int K;
            scanf ("%d", &K);
            float ans = (pi) (K);
            printf ("%f\n", ans);
        }
        else if (in == 2) {
            int x;
            scanf ("%d", &x);
            float ans = (e) (x);
            printf ("%f\n", ans);
        }
        else {
            break;
        }
    }

    printf ("!!!");
    return 0;
}