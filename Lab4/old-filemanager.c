#include <stdio.h>
#include <windows.h>
#include <string.h>

int main ()
{
    float x;
    DWORD D;
    char end = '!';
    char space = ' ';
    float null = 0;
    char name[] = "working";
    scanf("%s", name);
    HANDLE file = CreateFileA (//создание файла
        name,
        GENERIC_WRITE,
        0,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    ); 
    printf ("Enter numbers: ");
    while (scanf ("%f%c", &x, &space) > 0)
    {
        WriteFile (file, &x, sizeof(float), &D, NULL);
        WriteFile (file, &space, sizeof(char), &D, NULL);
    }
    CloseHandle (file);
}