#ifndef TABBPORO_H_
#define TABBPORO_H_
#include "tporo.h"
#include "tvectorporo.h"
#include "tlistaporo.h"
#include <queue>
class TNodoABB;
class TABBPoro{
    friend ostream &operator<<(ostream &os, const TABBPoro &tabbp);
    private:
        TNodoABB *nodo; // RAIZ DEL ARBOL
        void InordenAux(TVectorPoro &tvp, int &posicion) const;
        void PreordenAux(TVectorPoro &tvp, int &posicion) const;
        void PostordenAux(TVectorPoro &tvp, int &posicion) const;
        TPoro ObtenerMayorIzquierda() const;
        bool MismoVolumen(const TPoro &tp) const;
    public:
        TABBPoro();
        TABBPoro(const TABBPoro &tabbp);
        ~TABBPoro();
        TABBPoro & operator=(const TABBPoro &tabbp);
        bool operator==(const TABBPoro &tabbp) const;
        bool EsVacio() const;
        bool Insertar(const TPoro &tp);
        bool Borrar(const TPoro &tp);
        bool Buscar(const TPoro &tp) const;
        TPoro Raiz() const;
        int Altura() const;
        int Nodos() const;
        int NodosHoja() const;
        TVectorPoro Inorden() const;
        TVectorPoro Preorden() const;
        TVectorPoro Postorden() const;
        TVectorPoro Niveles() const;
        TABBPoro operator+(const TABBPoro &tabbp);
        TABBPoro operator-(const TABBPoro &tabbp);
        // EXAMENES DE PRACTICAS REPASO
        
        // JULIO 2015
        /*
        int* BuscaABB(const TListaPoro &tlp) const;
        void BuscaABBaux(int* &res, int &pos, const TPoro &tp) const;*/


        // JUNIO 2013
        /*int* examen(const TListaPoro &tlp) const;
        void examenAux(int* &vector, const TPoro &tp, int &posicion) const;*/
        
        
        // JUNIO 2014
        //bool existeCaminoDescendente(const TListaPoro &tlp) const;
        
        
        // Metodo que devuelve un vector con los nodos hoja que tiene el arbol
        //TVectorPoro extraerHojas() const;
        //void extraerHojasAux(int &pos, TVectorPoro &v) const;
        
        /*
            Comprobar que la lista es camino en el arbol, si la lista esta vacia
            devolveremos cierto
        */
       //bool caminico(const TListaPoro &lista) const;
       

       // Devuelve un vector de poros de forma que en la posicion i del vector
       // este el padre el poro que ocupa la posicion i de la lista, si el poro no
       // esta en el arbol, en esa posicion se guardara el poro vacio
       //TPoro *padresDe(const TListaPoro &lista) const;
       //TPoro padreDe(const TPoro &tp) const;

        // Funcion que devuelve tvectorporo los poros que se encuentran en el nivel n del arbol
        /*TVectorPoro extraerNodosNivel(int nivel) const;
        int cantidadPorosNivel(int nivel) const;
        void extraerNivel(TVectorPoro &v, int &pos, int nivel) const;*/

        // Mismo ejercicio que el anterior pero con devuelve una lista de poros
        //TListaPoro extraerNodosNivel(int nivel) const;
};
class TNodoABB{
    friend class TABBPoro;
    private:
        TPoro item; // DATOS DEL ARBOL
        TABBPoro iz, de; // ARBOL IZQUIERDA Y ARBOL DERECHA
    public:
        TNodoABB();
        TNodoABB(const TNodoABB &tnabb);
        ~TNodoABB();
        TNodoABB &operator=(const TNodoABB &tnabb);
};
#endif
