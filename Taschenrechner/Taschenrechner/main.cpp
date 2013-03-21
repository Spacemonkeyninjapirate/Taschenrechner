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


    while (true)
    {
        cin.getline(eingabe, EINGABEBUFFER);

        if(strncmp(eingabe, "quit", 4) == 0 || strncmp(eingabe, "exit", 4) == 0)
        {
            break;
        }

        list<token*> tokens = list<token*>();
        char *rest = eingabe;

        while(*rest != 0)
        {
            if(isdigit(*rest))
            {
                int i;

                for(i = 0; isdigit(rest[i]) != false; i++);

                token *gefunden = new token;

                gefunden->wert = atol(rest);
                gefunden->typ = ZAHL;

                if(tokens.size() == 0 || tokens.back()->typ != ZAHL)
                {
                    tokens.push_back(gefunden);
                }
                else
                {
                    cout << "Syntaxfehler\t Fehler bei " << rest << endl;

                    delete gefunden;

                    break;
                }

                rest = &rest[i];
            }
            else if (*rest == '+' || *rest == '-' || *rest == '/' || *rest == '*')
            {
                token *gefunden = new token;

                gefunden->wert = *rest;
                gefunden->typ = OPERATOR;

                if(tokens.size() == 0 || tokens.back()->typ != OPERATOR)
                {
                    tokens.push_back(gefunden);
                }
                else
                {
                    cerr << "Syntaxfehler\t Fehler bei "<< rest << endl;

                    delete gefunden;

                    break;
                }

                rest = &rest[1];
            }
            else
            {
                rest = &rest[1];
            }
        }

        for(list<token*>::iterator i = tokens.begin(); i != tokens.end(); ++i)
        {
            switch ((*i)->typ)
            {
            case ZAHL:
                cout << "ZAHL\t\t";
                cout << (*i)->wert << endl;
                break;
                
            case OPERATOR:
                cout << "OPERATOR\t";
                cout << static_cast<char>((*i)->wert) << endl;
                break;

            default:
                break;
            }

            delete *i;
        }
    }

    delete[] eingabe;
};