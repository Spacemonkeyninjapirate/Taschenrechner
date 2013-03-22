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

        if (strncmp(eingabe, "quit", 4) == 0 || strncmp(eingabe, "exit", 4) == 0)
        {
            break;
        }

        list<token*> tokens = list<token*>();
        char *rest = eingabe;

        while (*rest != 0)
        {
            if (isdigit(*rest))
            {
                int i;

                for (i = 0; isdigit(rest[i]) != false; i++);

                token *gefunden = new token;

                gefunden->wert = atol(rest);
                gefunden->typ = ZAHL;

                if (tokens.size() == 0 || tokens.back()->typ != ZAHL)
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

                if (tokens.size() == 0 || tokens.back()->typ != OPERATOR)
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

        if (tokens.size() != 0 && (tokens.front()->typ == OPERATOR || tokens.back()->typ == OPERATOR))
        {
            cerr << "Syntaxfehler:\n Term beginnt oder endet mit einem Operator"<< endl;

            for (list<token*>::iterator i = tokens.begin(); i != tokens.end(); ++i)
            {
                delete *i;
            }

            continue;
        }

        long int ergebnis;
        long int merken = '=';

        for (list<token*>::iterator i = tokens.begin(); i != tokens.end(); ++i)
        {

            if ((*i)->typ == OPERATOR && ((*i)->wert == '*' || (*i)->wert == '/'))
            {
                list<token*>::iterator x = i, y = i;

                --x;
                ++y;

                if ((*i)->wert == '*')
                {
                    ergebnis = (*x)->wert * (*y)->wert;
                }
                else if ((*i)->wert == '/')
                {
                    if ((*y)->wert == 0)
                    {
                        cout << "Division durch 0 nicht erlaubt" << endl;

                        goto freigeben;
                    }

                    ergebnis = (*x)->wert / (*y)->wert;
                }

                tokens.erase(x);
                tokens.erase(y);

                (*i)->typ = ZAHL;
                (*i)->wert = ergebnis;
            }
        }

        for (list<token*>::iterator i = tokens.begin(); i != tokens.end(); ++i)
        {
            if ((*i)->typ == ZAHL)
            {
               switch (merken)
               {
                   case '=':
                       ergebnis = (*i)->wert;
                       break;

                   case '-':
                       ergebnis -= (*i)->wert;
                       break;

                   case '+':
                       ergebnis += (*i)->wert;
                       break;
               }
            }
            else
            {
                merken = (*i)->wert;
            }
        }

        cout << ergebnis << endl;

freigeben:
        for (list<token*>::iterator i = tokens.begin(); i != tokens.end(); ++i)
        {
            delete *i;
        }

    }

    delete[] eingabe;
};