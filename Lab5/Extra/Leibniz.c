__declspec (dllexport) float Pi (int K) {
    float pi = 0;
    float i = 1;
    while (i <= K) {
        pi += (1/i);
        i += 2;
        pi -= (1/i);
        i += 2;
    }
    pi *= 4;
    return pi;
}