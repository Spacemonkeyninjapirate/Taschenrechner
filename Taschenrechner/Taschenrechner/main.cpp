#include <iostream>
#include <math.h>

#define EINGABEBUFFER 100

using namespace std;

void main()
{
    char *eingabe = new char [EINGABEBUFFER];
    char *rest = eingabe;

    while (true)
    {
        cin.getline(eingabe, EINGABEBUFFER);

        if(strncmp(eingabe, "quit", 4) == 0 || strncmp(eingabe, "exit", 4) == 0)
        {
            break;
        }

        while(*rest != 0)
        {
            if(isdigit(*rest))
            {
                int i;

                for(i = 0; isdigit(rest[i]) != false; i++);

                int zahl = atol(rest);

                rest = &rest[i];

                cout << zahl << endl;
            }
            else if (*rest == '+' || *rest == '-' || *rest == '/' || *rest == '*')
            {
                rest = &rest[1];
            }
            else
            {
                rest = &rest[1];
            }
        }
    }

    delete[] eingabe;
};