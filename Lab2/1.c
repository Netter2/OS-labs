#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <locale.h>

HANDLE parentinput = NULL;
HANDLE childoutput = NULL;
HANDLE file;
HANDLE errparentinput = NULL;
HANDLE errchildoutput = NULL;
SECURITY_ATTRIBUTES sa;
PROCESS_INFORMATION pi;
STARTUPINFO si;
DWORD D;
DWORD err = 0;
float x;
int error = 0;



int main ()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    sa.nLength = sizeof (SECURITY_ATTRIBUTES);
    sa.bInheritHandle = TRUE;
    ZeroMemory (&si, sizeof(si));
    si.cb = sizeof (si);
    ZeroMemory (&pi, sizeof(pi));
    char name[] = "working";
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
            SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 4));
            printf ("ERROR\nIncorrect work of function \"CreateFileA\". Code of error: %d.", err);
            SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 7));
            return -1;
        }
         
    if (!CreatePipe (&parentinput, &childoutput, &sa, 0)) 
        {
            if ((err = GetLastError ()) != 0)
                {
                    
                    SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 4));
                    printf ("ERROR\nIncorrect work of function \"CreatePipe\".");
                    SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 7));
                    return -1;
                }
            return -1;
        }

    if (!SetHandleInformation(parentinput, HANDLE_FLAG_INHERIT, 0))
        {
            
            SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 4));
            printf ("ERROR\nIncorrect work of function \"SetHandleInformation\".");
            SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 7));        
            return -1;
        }

    if (!CreatePipe (&errparentinput, &errchildoutput, &sa, 0)) 
    {
        if ((err = GetLastError ()) != 0)
            {
                SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 4));
                printf ("ERROR\nIncorrect work of function \"CreatePipe\".");
                SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 7));
                return -1;
            }
        return -1;
    }

    if (!SetHandleInformation(errparentinput, HANDLE_FLAG_INHERIT, 0))
        {
            SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 4));
            printf ("ERROR\nIncorrect work of function \"SetHandleInformation\".");
            SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 7));        
            return -1;
        }

    si.hStdError = errchildoutput;
    si.hStdOutput = childoutput;
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
            SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 4));
            printf ("ERROR\nIncorrect work of function \"CreateProcess\".");
            SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 7));  
            return -1;
        } 
    else
        {   
            if(!ReadFile (errparentinput, &error, sizeof(int), &D, NULL)) 
                {
                    err = GetLastError ();
                    SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 4));
                    printf ("ERROR\nIncorrect work of function \"ReadFile\". Code of error: %d.", err);
                    SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 7));
                    return -1;
                }
            else 
                {
                    if (error == 0)
                        {   
                            if(!ReadFile (parentinput, &x, sizeof(float), &D, NULL)) 
                                {
                                    err = GetLastError ();
                                    SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 4));
                                    printf ("ERROR\nIncorrect work of function \"ReadFile\". Code of error: %d.", err);
                                    SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 7));
                                    return -1;
                                }
                            else
                                {                                        
                                    printf ("%f", x);
                                }
                        }
                    else if (error == 1)
                        {
                            SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 4));
                            printf ("ERROR\nInput file is incorrect");
                            SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 7));
                        }
                    else if (error == 2)
                        {
                            SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 4));
                            printf ("ERROR\nIncorrect work of child process");
                            SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 7));
                        }
                    else if (error == 3)
                        {
                            SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 4));
                            printf ("ERROR\nFile is empty");
                            SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 7));
                        }
                }
            
        }
    CloseHandle (file);
    CloseHandle (parentinput);
    CloseHandle (childoutput);
    CloseHandle (errparentinput);
    CloseHandle (errchildoutput);
    CloseHandle (pi.hProcess);
    CloseHandle (pi.hThread);
    CloseHandle (hConsole);    
    return 0;
}