#include <stdio.h>
#include <windows.h>

int main() 
{
    HANDLE in = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE err = GetStdHandle(STD_ERROR_HANDLE);
    DWORD D;

    float x = 0, y = 0;
    int error = 0;
    char flag = '@';
    int errflag = 0;


    while (1)
        {
            if(!ReadFile (in, &y, sizeof(float), &D, NULL))
                {
                    error = 2;
                    WriteFile (err, &error, sizeof(int), &D, NULL);
                    return -1;
                }

            flag = '!';

            if(!ReadFile (in, &flag, sizeof(char), &D, NULL))
                {
                    error = 2;
                    WriteFile (err, &error, sizeof(int), &D, NULL);
                    return -1;
                }

            if (flag == '!')
                {
                    break;
                }
            else if (flag != ' ')
                {
                    error = 1;
                    if(!WriteFile (err, &error, sizeof(int), &D, NULL))
                        {
                            error = 2;
                            WriteFile (err, &error, sizeof(int), &D, NULL);
                            return -1;
                        }
                    return -1;
                }
            x += y;
            errflag ++;
        }



    if (errflag == 0)
        {
            error = 3;
            if(!WriteFile (err, &error, sizeof(int), &D, NULL))
                {
                    error = 2;
                    WriteFile (err, &error, sizeof(int), &D, NULL);
                    return -1;
                }
            return -1;
        }

    if(!WriteFile (err, &error, sizeof(int), &D, NULL))
        {
            error = 2;
            WriteFile (err, &error, sizeof(int), &D, NULL);
            return -1;
        }

    if(WriteFile (out, &x, sizeof(float), &D, NULL))
        {
            error = 2;
            WriteFile (err, &error, sizeof(int), &D, NULL);
            return -1;
        }

    return 0;
}