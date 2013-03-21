#include <iostream>
#include <math.h>
#include <list>

#define EINGABEBUFFER 100

using namespace std;

enum tokentyp
{
    ZAHL = 256,
    OPERATOR,
};

struct token
{
    long int wert;
    tokentyp typ;
};

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

        list<token*> tokens;

        while(*rest != 0)
        {
            if(isdigit(*rest))
            {
                int i;

                for(i = 0; isdigit(rest[i]) != false; i++);

                token *gefunden = new token;

                gefunden->wert = atol(rest);
                gefunden->typ = ZAHL;

                rest = &rest[i];

                tokens.push_back(gefunden);
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

        for(list<token*>::iterator i = tokens.begin(); i != tokens.end(); ++i)
        {
            delete *i;
        }
    }

    delete[] eingabe;
};