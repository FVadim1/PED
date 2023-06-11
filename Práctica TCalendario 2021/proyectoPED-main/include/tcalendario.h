#ifndef _tcalendario_ 
#define _tcalendario_

#include <iostream>
#include <string.h>
using namespace std;

class TCalendario {
    friend ostream & operator<< (ostream &, const TCalendario &);

    private:
        bool bisiesto (int);
        bool comprobarFecha (int, int, int);

        int dia, mes, anyo;
        char * mensaje;

    public:
        TCalendario();
        TCalendario(int, int, int, char *);
        TCalendario(const TCalendario &);
        ~TCalendario();

        TCalendario & operator= (const TCalendario &);
        
        TCalendario operator+ (int);
        TCalendario operator- (int);

        TCalendario operator++ (int);
        TCalendario & operator++ ();

        TCalendario operator-- (int);
        TCalendario & operator-- ();

        bool ModFecha(int, int, int);
        bool ModMensaje(char *);

        bool operator== (const TCalendario &);
        bool operator!= (const TCalendario &);
        bool operator> (const TCalendario &);
        bool operator< (const TCalendario &);

        bool EsVacio();

        int Dia(){return this->dia;}
        int Mes(){return this->mes;}
        int Anyo(){return this->anyo;}
        char * Mensaje(){return this->mensaje;}
};
#endif
        