#include <iostream>
#include <math.h>

#define EINGABEBUFFER 100

using namespace std;

void main()
{
    bool soll_beenden = false;

    char *eingabe = new char [EINGABEBUFFER];

    while (soll_beenden != true)
    {
        cin.getline(eingabe, EINGABEBUFFER);

        soll_beenden = (strncmp(eingabe, "quit", 4) == 0 || strncmp(eingabe, "exit", 4) == 0);
    }

    delete[] eingabe;
};