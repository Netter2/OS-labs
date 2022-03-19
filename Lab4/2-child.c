#include <stdio.h>
#include <windows.h>

int main() 
{
    HANDLE in = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE err = GetStdHandle(STD_ERROR_HANDLE);
    DWORD D;
    void* bufferfile = MapViewOfFile (out, FILE_MAP_ALL_ACCESS, 0, 0, 512);

    float x = 0, y = 0;
    char flag;
    int shift = 2;
    float counter = 0;

    while (1) {
        if (!ReadFile (in, &y, sizeof(float), &D, NULL)) {
            *((float*) bufferfile) = 1;
            ReleaseSemaphore (err, 1, NULL);
            break;
        }
        x += y;
        flag = '@';
        if (!ReadFile (in, &flag, sizeof(char), &D, NULL)) {
            *((float*) bufferfile) = 1;
            ReleaseSemaphore (err, 1, NULL);
            break;
        }
        if (flag == '\n') {
            *((float*) bufferfile + shift) = x;
            shift ++;
            counter ++;
            x = 0;
        }
        else if (flag == '@') {
            if (counter == 0) {
                *((float*) bufferfile) = 2;
                ReleaseSemaphore (err, 1, NULL);
                break;
            }
            else {
                *((float*) bufferfile) = 0;
                *((float*) bufferfile + 1) = counter;
                ReleaseSemaphore (err, 1, NULL);
                break;
            }
        }
    }

    CloseHandle (in);
    CloseHandle (out);
    CloseHandle (err);
    UnmapViewOfFile (bufferfile);
    return 0;
}