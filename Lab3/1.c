#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <pthread.h>
#include <math.h>

struct thrdata {
    int rand;
    float r;
};

int all = 0;
double hit = 0;
int count = 0;
pthread_mutex_t mutex;

void* threadFunction (void* thread_data) {//функция для потока
    float r = ((struct thrdata*) thread_data)->r;
    srand (((struct thrdata*) thread_data)->rand);
    
    while (count < all) {
        double a = rand ();
        double b = rand ();
        int c = rand ();
        if ((c % 2) == 1) {
            a *= -1;
        }
        c = rand ();
        if ((c % 2) == 1) {
            b *= -1;
        }

        a *= r / RAND_MAX;
        b *= r / RAND_MAX;

        pthread_mutex_lock(&mutex);
        if ((a * a) + (b * b) <= (r * r)) {
            hit ++;
        }

        count ++;
        pthread_mutex_unlock(&mutex);
    }
    
    pthread_exit(0);
    return NULL;
}

int main (int argc, char** argv) {
    DWORD err;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    struct thrdata data;
    data.rand = time(NULL);
    int number = 0;
    float r = 0;
    double S = 0;

    while(*argv[1]) {
        number = number * 10 + (*argv[1] ++ - '0');
    }

    printf ("Enter radius: ");
    scanf ("%f", &r);

    printf ("Enter number of dots: ");
    scanf ("%d", &all);

    data.r = r;
    pthread_t thread [number];
    int timecounter = GetTickCount();
    for (int i = 0; i < number; i ++) {
        void* thread_data = &data;
        if (pthread_create (&thread [i], NULL, threadFunction, thread_data)) {
            err = GetLastError ();
            SetConsoleTextAttribute(hConsole, (WORD) (0 | 4));
            printf ("ERROR\nCannot create a thread. Code of error: %d.", err);
            SetConsoleTextAttribute(hConsole, (WORD) (0 | 7));
        }
        
        data.rand ++;
    }

    for (int i = 0; i < number; i ++) {
        pthread_join (thread [i], NULL);
    }

    timecounter = GetTickCount() - timecounter;
    S = (2 * r * 2 * r) * (hit / all);
    printf ("S = %f\n", S);
    printf ("Inacuracy = %f\n", S - (r * r * 3.1415926535));
    printf ("Procent of inacuracy = %f%c \n", (100 * abs(S - (r * r * 3.1415926535)) / (r * r * 3.1415926535)), 37);
    printf ("Worktime = %d ms\n", timecounter);
    pthread_mutex_destroy(&mutex);
    return 0;
}