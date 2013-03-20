#include <iostream>
#include <math.h>

#define EINGABEBUFFER 100

using namespace std;

void main()
{
    char *eingabe = new char [EINGABEBUFFER];

    while (true)
    {
        cin.getline(eingabe, EINGABEBUFFER);

        if(strncmp(eingabe, "quit", 4) == 0 || strncmp(eingabe, "exit", 4) == 0)
        {
            break;
        }
    }

    delete[] eingabe;
};