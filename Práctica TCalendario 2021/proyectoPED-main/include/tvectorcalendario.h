#ifndef _tvectorcalendario_ 
#define _tvectorcalendario_

#include <iostream>
#include <sstream>
using namespace std;

#include "tcalendario.h"

class TVectorCalendario {
    friend ostream & operator<<(ostream &, const TVectorCalendario &);

    private:
        TCalendario *c;
        int tamano;
        TCalendario error;

        bool bisiesto (int);
        bool comprobarFecha (int, int, int);
    
    public:
        TVectorCalendario();
        TVectorCalendario(int);
        TVectorCalendario(const TVectorCalendario &);
        ~TVectorCalendario();

        TVectorCalendario & operator= (const TVectorCalendario &);

        bool operator==(const TVectorCalendario &) const;
        bool operator!=(const TVectorCalendario &) const;

        // Sobrecarga del operador corchete (parte IZQUIERDA)
        TCalendario & operator[](int);

        // Sobrecarga del operador corchete (parte DERECHA)
        TCalendario operator[](int) const;

        // Tamaño del vector (posiciones TOTALES)
        int Tamano(){return this->tamano;};
        // Cantidad de posiciones OCUPADAS (no vacías) en el vector
        int Ocupadas();
        // Devuelve TRUE si existe el calendario en el vector
        bool ExisteCal(TCalendario &);
        // Mostrar por pantalla mensajes de TCalendario en el vector, de fecha IGUAL O POSTERIOR a la pasada
        void MostrarMensajes(int,int,int);
        // REDIMENSIONAR el vectorde TCalendario
        bool Redimensionar(int);
};
#endif