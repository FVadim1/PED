#ifndef Tlistaporo_h
#define Tlistaporo_h

#include <tporo.h>


class TListaNodo{
    
    friend class TListaPosicion;
    friend class TListaPoro;

    private:

        TPoro e; //El elemento del nodo
        TListaNodo *anterior; //EL nodo anterior
        TListaNodo *siguiente; //El nodo siguiente

    public:

        TListaNodo(); //Constructor por defecto
        TListaNodo(const TListaNodo &); //Constructor de copia
        ~TListaNodo(); //Destructor
        TListaNodo & operator=(const TListaNodo &); //Sobrecarga deñ operador asignación

};

class TListaPosicion{

    friend class TListaPoro;
    friend class TListaNodo;

    private:

        TListaNodo *pos; //Para implementar la POSICIÓN a NODO de la LISTA de TPoro
   
    public:

        //FORMA CANÓNICA
        TListaPosicion(); //COnstructor por defecto
        TListaPosicion(const TListaPosicion &); //COnstructor de copia     
        ~TListaPosicion(); //Destructor
        TListaPosicion & operator=(const TListaPosicion &); //Sobrecarga deñ operador asignación

        //MÉTODOS
        bool operator==(const TListaPosicion &) const; //Sobrecarga deñ operador igualdad
        TListaPosicion Anterior() const; //Devuelve la posición anterior
        TListaPosicion Siguiente() const; //Devuelve la posición siguiente
        bool EsVacia() const; //Devuelve TRUE si la posición no apunta a una lista, FALSE en caso contrario

};

class TListaPoro{

    friend class TListaPosicion;
    friend class TListaNodo;
    friend ostream & operator<<(ostream &,const TListaPoro &);

    private:

        TListaNodo *primero; //Primer elemento de la lista
        TListaNodo *ultimo; //Ultimo elemento de la lista   

    public:

        //FORMA CANÓNICA
        TListaPoro(); //COnstructor por defecto 
        TListaPoro(const TListaPoro &); //COnstructor de copia     
        ~TListaPoro(); //Destructor
        TListaPoro & operator=(const TListaPoro &); //Sobrecarga deñ operador asignación

        //MÉTODOS
        bool operator==(const TListaPoro &) ; //Sobrecarga del operador igualdad
        TListaPoro operator+(const TListaPoro &); //Sobrecarga del operador suma
        TListaPoro operator-(const TListaPoro &); //Sobrecarga del operador resta
        bool EsVacia() const; //Devuelve true si la lista está vacía, false en caso contrario
        bool Insertar(TPoro &); //Inserta el elemento en la lista
        bool Borrar(TPoro &); //Busca y borra el elemento
        bool Borrar(TListaPosicion &) ; //Borra el elemento que ocupa la posición indicada
        TPoro Obtener(const TListaPosicion &) const ; //Obtiene el elemento que ocupa la posición indicada.
        bool Buscar(TPoro &); //Devuelve true si el elemento está en la lista, false en caso contrario.
        int Longitud() const; //Devuelve la longitud de la lista.
        TListaPosicion Primera() const;//Devuelve la primera posición de la lista.
        TListaPosicion Ultima() const;//Devuelve la última posición de la lista.
        TListaPoro ExtraerRango(int,int); //Extraer un rango de nodos de la lista

};



#endif