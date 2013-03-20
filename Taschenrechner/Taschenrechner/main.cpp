#include <iostream>
#include <math.h>
#define Zahl 100

using namespace std;

void main()
{
    bool vergleich = false;
    char *platzhalter = new char [Zahl]; 
    while (vergleich != true)
    {
        cin.getline(platzhalter, Zahl);
        vergleich = (strncmp(platzhalter,"quit",4) == 0 ||strncmp(platzhalter,"exit",4) == 0 );
    }
    delete[] platzhalter;
};