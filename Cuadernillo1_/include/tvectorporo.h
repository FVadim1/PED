#ifndef Tvectorporo_h
#define Tvectorporo_h
#include <cstring>
#include <iostream> //para poder usar ostream
using namespace std; //para poder usar ostream
#include<algorithm>

#include <tporo.h>

class TVectorPoro{

    friend ostream & operator<<(ostream &,const TVectorPoro &); // Sobrecarga del operador salida

private:

    int dimension; //Dimensión del vector
    TPoro *datos; // Datos del vector
    TPoro error; // Para cuando haya error en el operador[]

    void copiar(const TVectorPoro &);

public:

    //Forma canónica
    TVectorPoro(); // Constructor por defecto
    TVectorPoro(int); // Constructor a partir de una dimensión
    TVectorPoro(TVectorPoro &); // Constructor de copia
    ~TVectorPoro(); // Destructor

    TVectorPoro & operator=(const TVectorPoro &);

    //Métodos
    bool operator==(TVectorPoro &); // Sobrecarga del operador igualdad
    bool operator!=(TVectorPoro &); // Sobrecarga del operador igualdad
    TPoro & operator[](int); // sobrecarga del operador corchete (parte IZQUIERDA)
    TPoro operator[](int) const; // sobrecarga del operador corchete (parte DERECHA)
    int Longitud(); // devuelve la longitud (dimensión del vector)
    int Cantidad(); // devuelve la cantidad de posiciones ocupadas (no vacias) en el vector
    bool Redimensionar(int); // REDIMENSIONAR el vector de TPoro
};



#endif