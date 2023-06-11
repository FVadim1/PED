#ifndef Tabbporo_h
#define Tabbporo_h
#include <cstring>
#include <iostream> //para poder usar ostream
#include <tporo.h>
#include <tvectorporo.h>
using namespace std; //para poder usar ostream

#include <queue>

class TNodoABB;

class TABBPoro{

    friend class TNodoABB;

    friend ostream & operator<<(ostream &, TABBPoro &);

    private:

        TNodoABB *nodo; //Puntero al nodo
        void InordenAux(TVectorPoro &, int &) const; //AUXILIAR: Devuelve el recorrido en inorden
        void PreordenAux(TVectorPoro &, int &) const; //AUXILIAR: Devuelve el recorrido en preorden
        void PostordenAux(TVectorPoro &, int &) const; //AUXILIAR: Devuelve el recorrido en postorden

        //MIAS
        bool esHoja(const TNodoABB *);
        TPoro ObtenerMenorDerecha(TNodoABB *);


    public:

        //FORMA CANÓNICA
        TABBPoro(); //Constructor por defecto
        TABBPoro(const TABBPoro &); //Constructor de copia
        ~TABBPoro(); //Destructor
        TABBPoro & operator= (const TABBPoro &); //Sobrecarga del operador asignación

        //MÉTODOS
        bool operator==(const TABBPoro &) const; //Sobrecarga del operador igualdad
        bool EsVacio(); //Devuelve TRUE si el árbol está vacío, FALSE en caso contrario
        bool Insertar(TPoro &); //Inserta el elemento en el árbol
        bool Borrar(TPoro &); //Borra el elemento en el árbol
        bool Buscar(TPoro &); //Devuelve TRUE si el elemento está en el árbol, FALSE en caso contrario
        TPoro Raiz(); //Devuelve el elemento en la raiz del árbol
        int Altura(); //Devuelve la altura del árbol (la altura de un arbol vacío es 0)
        int Nodos() const; //Devuelve el número de nodos del árbol (un árbol vacío posee 0 nodos)
        int NodosHoja(); //Devuelve el número de nodos hoja en el árbol (la raiz puede ser nodo hoja)
        TVectorPoro Inorden() const; //Devuelve el recorrido en inorden
        TVectorPoro Preorden() const; //Devuelve el recorrido en preorden
        TVectorPoro Postorden() const; //Devuelve el recorrido en postorden
        TVectorPoro Niveles() const; //Devuelve el recorrido en niveles
        TABBPoro operator+(TABBPoro &); //Suma de dos ABB
        TABBPoro operator-(TABBPoro &); //Resta de dos ABB
};


class TNodoABB{

    friend class TABBPoro;

    private:

        TPoro item; //El elemento del nodo
        TABBPoro iz, de; //Subárbol izquierdo y derecho

    public:

        TNodoABB(); //Constructor por defecto
        TNodoABB(const TNodoABB &); //Constructor de copia
        ~TNodoABB(); //Destructor
        TNodoABB & operator=(TNodoABB &); //Sobrecarga del operador asignación
};



#endif