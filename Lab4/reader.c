#include <stdio.h>
#include <windows.h>
#include <string.h>

int main () {
    float number;
    char symbol;
    DWORD D;
    char name[] = "working";
    scanf("%s", name);
    printf("%s\n", name);
    SECURITY_ATTRIBUTES sa;
    HANDLE file = CreateFileA (//открытие файла на чтение
        name,
        GENERIC_READ,
        0,
        &sa,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );
    while (1) {
        symbol = '@';
        ReadFile (file, &number, sizeof(float), &D, NULL);
        ReadFile (file, &symbol, sizeof(char), &D, NULL);
        printf ("%f%c", number, symbol);
        if (symbol == '@') {
            break;
        }
    }
    return 0;
}