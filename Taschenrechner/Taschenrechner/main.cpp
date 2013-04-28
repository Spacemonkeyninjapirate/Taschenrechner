#include <iostream>
#include <cmath>
#include <list>
#include <stdexcept>
#include <string>
#include <sstream>

#define EINGABEBUFFER 100

using namespace std;

enum tokentyp
{
    ZAHL = 256,
    OPERATOR,
};

struct token
{
    tokentyp typ;
    union
    {
        float wert;
        char operation;
    };
};

_declspec(dllexport) float taschenrechner(char *&rest, int level);

void main()
{
    char *eingabe = new char [EINGABEBUFFER];

    while (true)
    {
        cin.getline(eingabe, EINGABEBUFFER);

        if(cin.gcount() ==  1)
        {
            continue;
        }

        if (strncmp(eingabe, "quit", 4) == 0 || strncmp(eingabe, "exit", 4) == 0)
        {
            break;
        }

        char *rest = eingabe;

        try
        {
            float ergebnis = taschenrechner(rest, 0);

            cout << ergebnis << endl;
        }
        catch (runtime_error &e)
        {
        }
    }

    delete[] eingabe;
};

float taschenrechner(char *&rest, int level)
{
        list<token*> tokens = list<token*>();

        while (*rest != 0)
        {
            if (isdigit(*rest))
            {
                size_t index;

                token *gefunden = new token;

                gefunden->wert = stof(rest, &index);
                gefunden->typ = ZAHL;

                if (tokens.size() == 0 || tokens.back()->typ != ZAHL)
                {
                    tokens.push_back(gefunden);
                }
                else
                {
                    for (list<token*>::iterator i = tokens.begin(); i != tokens.end(); ++i)
                    {
                        delete *i;
                    }
 
                     delete gefunden;

                    stringstream fehler;

                    fehler << "Syntaxfehler bei " << rest;

                    throw runtime_error(fehler.str());
                }

                rest = &rest[index];
            }
            else if (*rest == '+' || *rest == '-' || *rest == '/' || *rest == '*' || *rest == '^')
            {
                token *gefunden = new token;

                gefunden->operation = *rest;
                gefunden->typ = OPERATOR;

                if (tokens.size() == 0 || tokens.back()->typ != OPERATOR)
                {
                    tokens.push_back(gefunden);
                }
                else
                {
                    for (list<token*>::iterator i = tokens.begin(); i != tokens.end(); ++i)
                    {
                        delete *i;
                    }
 
                     delete gefunden;

                    stringstream fehler;

                    fehler << "Syntaxfehler bei " << rest;

                    throw runtime_error(fehler.str());
                }

                rest = &rest[1];
            }
            else if (*rest == ')')
            {
                if (level == 0)
                {
                    stringstream fehler;
 
                    fehler << "Syntaxfehler bei " << rest;

                    for (list<token*>::iterator i = tokens.begin(); i != tokens.end(); ++i)
                    {
                        delete *i;
                    }
 

                    throw runtime_error(fehler.str());
                }

                rest = &rest[1];

                break;
            }
            else if (*rest == '(')
            {
                if (tokens.size() != 0 && tokens.back()->typ == ZAHL)
                {
                    stringstream fehler;

                    fehler << "Syntaxfehler bei " << rest;

                    for (list<token*>::iterator i = tokens.begin(); i != tokens.end(); ++i)
                    {
                        delete *i;
                    }
 

                    throw runtime_error(fehler.str());
                }

                rest = &rest[1];

                token *klammer = new token;

                klammer->wert = taschenrechner(rest, level + 1);
                klammer->typ = ZAHL;

                tokens.push_back(klammer);
            }
            else if (strncmp(rest, "sqrt", 4) == 0)
            {
                if (tokens.size() != 0 && (tokens.back()->typ == ZAHL || tokens.back()->typ == OPERATOR && tokens.back()->operation == 'v'))
                {
                    stringstream fehler;
                    
                    fehler << "Syntaxfehler bei " << rest;

                    for (list<token*>::iterator i = tokens.begin(); i != tokens.end(); ++i)
                    {
                        delete *i;
                    }
 
                    throw runtime_error(fehler.str());
                }

                rest = &rest[4];

                token *wurzel = new token;

                wurzel->operation = 'v';
                wurzel->typ = OPERATOR;

                tokens.push_back(wurzel);
            }
            else
            {
                rest = &rest[1];
            }
        }

        if (*rest == 0 && level != 0 && !(*(rest - 1) == ')' && level == 1))
        {

            for (list<token*>::iterator i = tokens.begin(); i != tokens.end(); ++i)
            {
                delete *i;
            }

            throw runtime_error("Syntaxfehler: Kein geschlossener Term");
        }

        if (tokens.size() != 0 && ((tokens.front()->typ == OPERATOR && tokens.front()->operation != 'v') || tokens.back()->typ == OPERATOR))
        {

            for (list<token*>::iterator i = tokens.begin(); i != tokens.end(); ++i)
            {
                delete *i;
            }

            throw runtime_error("Syntaxfehler: Term beginnt oder endet mit einem Operator");
        }

        float ergebnis = 0.0f;
        char merken = '=';

        for (list<token*>::iterator i = tokens.begin(); i != tokens.end(); ++i)
        {
            if ((*i)->typ == OPERATOR)
            {
                if((*i)->operation == 'v')
                {
                    list<token*>::iterator x = i;

                    ++x;

                    (*i)->wert = sqrtf((*x)->wert);
                    (*i)->typ = ZAHL;

                    delete *x;

                    tokens.erase(x);
                }
                else if((*i)->operation == '^')
                {
                    list<token*>::iterator x = i, y = i;

                    --x;
                    ++y;

                    (*i)->wert = pow((*x)->wert,(*y)->wert);
                    (*i)->typ = ZAHL;

                    delete *x;
                    delete *y;

                    tokens.erase(x);
                    tokens.erase(y);
                }
            }
        }

        for (list<token*>::iterator i = tokens.begin(); i != tokens.end(); ++i)
        {
            if ((*i)->typ == OPERATOR && ((*i)->operation == '*' || (*i)->operation == '/'))
            {
                list<token*>::iterator x = i, y = i;

                --x;
                ++y;

                if ((*i)->operation == '*')
                {
                    ergebnis = (*x)->wert * (*y)->wert;
                }
                else if ((*i)->operation == '/')
                {
                    if ((*y)->wert == 0.0f)
                    {
                        for (list<token*>::iterator i = tokens.begin(); i != tokens.end(); ++i)
                        {
                            delete *i;
                        }
 

                        throw runtime_error("Division durch 0 nicht erlaubt");
                    }

                    ergebnis = (*x)->wert / (*y)->wert;
                }

                delete *x;
                delete *y;

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
                merken = (*i)->operation;
            }
        }

        for (list<token*>::iterator i = tokens.begin(); i != tokens.end(); ++i)
        {
            delete *i;
        }

        return ergebnis;
}