#ifndef Tavlporo_h
#define Tavlporo_h
#include <cstring>
#include <iostream> //para poder usar ostream
using namespace std; //para poder usar ostream
#include <tporo.h>
#include <tvectorporo.h>

class TNodoAVL;

class TAVLPoro{

    friend class TNodoAVL;
    friend ostream & operator<<(ostream &,const TAVLPoro &);

    private:

        TNodoAVL *raiz; //Puntero al nodo raíz

        //AUXILIAR: Devuelve el recorrido en Inorden
        void InordenAux(TVectorPoro &, int &) const;
        //AUXILIAR: Devuelve el recorrido en Preorden
        void PreordenAux(TVectorPoro &, int &) const;
        //AUXILIAR: Devuelve el recorrido en Postorden
        void PostordenAux(TVectorPoro &, int &) const;

        //MIAS
        bool esHoja(const TNodoAVL *);
        bool InsertarAux(TPoro &, bool &); //AUXILIAR: Inserta el elemento TPoro en el árbol
        bool borrarAux(TPoro &, bool &); //AUXILIAR: Borra el elemento TPoro en el árbol
        TPoro ObtenerMayorIzquierda();

        //rotación árbol derecho
        void rotacion_DD();
        void rotacion_DI();

        //rotación árbol izquierdo
        void rotacion_II();
        void rotacion_ID();     

    public:

        TAVLPoro(); //constructor por defecto
        TAVLPoro(const TAVLPoro &); //Connstructor de copia
        ~TAVLPoro(); //Destructor
        TAVLPoro & operator=(const TAVLPoro &); //Sobrecarga del operador asignación

        //MÉTODOS
        bool operator==(const TAVLPoro &) const; //Sobrecarga del operador igualdad
        bool operator!=(const TAVLPoro &) const; //Sobrecarga del operador desigualdad
        bool EsVacio(); //Devuelve TRUE si el árbol está vacio, FALSE en caso contrario
        bool Insertar(TPoro &); //Inserta el elemento TPoro en el árbol
        bool Buscar(TPoro &); //Devuelve TRUE si el elemento está en el árbol, FALSE en caso contrario
        bool Borrar(TPoro &); //Borra un elemento TPoro del árbol AVL
        int Altura() ; //Devuelve la altura del árbol (la altura de un árbol vacio es 0)
        TPoro Raiz(); //Devuelve el elemento TPoro raiz del árbol AVL
        int Nodos() const; //Devuelve el número de nodos del árbol (un árbol vacío posee 0 nodos)
        int NodosHoja();//Devuelve el número de nodos hoja en el árbol (la raiz puede ser nodo hoja)

        TVectorPoro Inorden() const; //Devuelve el recorrido en Inorden sobre un vector
        TVectorPoro Preorden() const;//Devuelve el Preorden en Inorden sobre un vector
        TVectorPoro Postorden() const;//Devuelve el Postorden en Inorden sobre un vector
};

class TNodoAVL{

    friend class TAVLPoro;

    private:

        /* Los Tporo en el árbol están ordenados en función del volumen*/
        TPoro item; //EL elemento del nodo
        TAVLPoro iz, de; //Subárbol izquierdo y derecho
        int fe; //Factor de equilibrio

    public:
        
        //FORMA CANÓNICA
        TNodoAVL(); //constructor por defecto
        TNodoAVL(const TNodoAVL &); //Connstructor de copia
        ~TNodoAVL(); //Destructor
        TNodoAVL & operator=(const TNodoAVL &); //Sobrecarga del operador asignación
};


#endif