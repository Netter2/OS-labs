__declspec (dllexport) float Pi (int K) {
    float pi = 1;
    float i = 1;
    while (i <= K) {
        pi *= ((4.0 * i * i) / (4 * i * i - 1));
        i ++;
    }
    pi *= 2;
    return pi;
}