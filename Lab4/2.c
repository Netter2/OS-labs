#include <stdio.h>
#include <windows.h>

HANDLE file = NULL;
HANDLE bufferfile = NULL;
HANDLE trigger;
SECURITY_ATTRIBUTES sa;
PROCESS_INFORMATION pi;
STARTUPINFO si;
DWORD err = 0;
float counter = 0;
int shift = 2;
char name[256];

int main () {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    ZeroMemory (&sa, sizeof (SECURITY_ATTRIBUTES));
    sa.nLength = sizeof (SECURITY_ATTRIBUTES);
    sa.bInheritHandle = TRUE;
    bufferfile = CreateFileMapping (INVALID_HANDLE_VALUE, &sa, PAGE_READWRITE, 0, 512, NULL);
    trigger = CreateSemaphore (&sa, 0, 1, NULL);
    void* answer = MapViewOfFile (bufferfile, FILE_MAP_ALL_ACCESS, 0, 0, 512);

    scanf("%s", name);

    file = CreateFileA (//открытие файла на чтение
        name,
        GENERIC_READ,
        0,
        &sa,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if ((err = GetLastError ()) != 0)
        {
            SetConsoleTextAttribute(hConsole, (WORD) (0 | 4));
            printf ("ERROR\nIncorrect work of function \"CreateFileA\". Code of error: %ld.", err);
            SetConsoleTextAttribute(hConsole, (WORD) (0 | 7));
            CloseHandle (file);
            CloseHandle (bufferfile);
            CloseHandle (trigger);
            CloseHandle (hConsole);
            UnmapViewOfFile (bufferfile);
            return -1;
        }

    si.hStdError = trigger;
    si.hStdOutput = bufferfile;
    si.hStdInput = file;
    si.dwFlags |= STARTF_USESTDHANDLES;
    

    if (!CreateProcess (NULL,
        "2.exe",
        NULL,
        NULL,
        TRUE,
        0,
        NULL,
        NULL,
        &si,
        &pi)
    ) 
        {
            SetConsoleTextAttribute(hConsole, (WORD) (0 | 4));
            printf ("ERROR\nIncorrect work of function \"CreateProcess\".");
            SetConsoleTextAttribute(hConsole, (WORD) (0 | 7));  
            CloseHandle (file);
            CloseHandle (bufferfile);
            CloseHandle (trigger);
            CloseHandle (hConsole);
            UnmapViewOfFile (bufferfile);
            return -1;
        }
        else {
            WaitForSingleObject (trigger, INFINITE);
            if (*(float*) answer == 0) {
                counter = *((float*) answer + 1);
                for (int i = 0; i < (int) counter; i ++) {
                    printf ("%f\n", *((float*) answer + shift));
                    shift ++;
                }
            }
            else if (*(float*) answer == 1) {
                SetConsoleTextAttribute(hConsole, (WORD) (0 | 4));
                printf ("ERROR\nIncorrect work of function \"ReadFile\" in child process.");
                SetConsoleTextAttribute(hConsole, (WORD) (0 | 7));  
                CloseHandle (file);
                CloseHandle (bufferfile);
                CloseHandle (trigger);
                CloseHandle (hConsole);
                UnmapViewOfFile (bufferfile);
                return -1;
            }
            else if (*(float*) answer == 2) {
                SetConsoleTextAttribute(hConsole, (WORD) (0 | 4));
                printf ("ERROR\nInput file is empty.");
                SetConsoleTextAttribute(hConsole, (WORD) (0 | 7));  
                CloseHandle (file);
                CloseHandle (bufferfile);
                CloseHandle (trigger);
                CloseHandle (hConsole);
                UnmapViewOfFile (bufferfile);
                return -1;
            }
            else {
                SetConsoleTextAttribute(hConsole, (WORD) (0 | 4));
                printf ("ERROR\nUnknown error, child process returned incorrect code.");
                SetConsoleTextAttribute(hConsole, (WORD) (0 | 7));  
                CloseHandle (file);
                CloseHandle (bufferfile);
                CloseHandle (trigger);
                CloseHandle (hConsole);
                UnmapViewOfFile (bufferfile);
                return -1;
            }
        }


    CloseHandle (file);
    CloseHandle (bufferfile);
    CloseHandle (trigger);
    CloseHandle (hConsole);
    UnmapViewOfFile (bufferfile);
    return 0;
}