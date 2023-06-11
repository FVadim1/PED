#ifndef Tporo_h
#define Tporo_h
#include <cstring>
#include <iostream> //para poder usar ostream
using namespace std; //para poder usar ostream

class TPoro{

    friend ostream & operator<<(ostream &,const TPoro &);

    private:

        int x;
        int y;
        double volumen;
        char* color;

        void copiar(const TPoro &);

    public:


    //Métodos: modificadores
    void Posicion(int , int); //Modifica la posición
    void Volumen(double); //Modifica el volumen
    void Color(char*); //Modifica el color

    //Métodos: getters
    int PosicionX(); //Devuelva la coordenada x de la posicion
    int PosicionY(); //Devuelva la coordenada y de la posicion
    double Volumen(); //Devuelve el volumen
    char* Color(); //Devuelve el color
    bool EsVacio() const; //Devuelve cierto si el poro está vacio


    //Forma canónica
    TPoro(); //constructor por defecto
    TPoro(int , int , double); //constructor a partir de una posición y un volumen
    TPoro(int , int , double , char*); //constructor a partir de una posición, un volumen y un color
    TPoro(const TPoro &); //Connstructor de copia

    ~TPoro(); //Destructor

    //Métodos: sobrecargas
    bool operator==(const TPoro &) const; //Sobrecarga del operador igualdad
    bool operator!=(const TPoro &) const; //Sobrecarga del operador desigualdad
    TPoro & operator=(const TPoro &); //Sobrecarga del operador asignación


};

#endif