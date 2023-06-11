#ifndef TAVLPORO_H_
#define TAVLPORO_H_
#include "tporo.h"
#include "tvectorporo.h"
#include <queue>
class TNodoAVL;
class TAVLPoro{
    friend ostream & operator<<(ostream &os, const TAVLPoro &tavlp);
    private:
        TNodoAVL *raiz;
        void InordenAux(TVectorPoro &tvp, int &pos) const;
        void PreordenAux(TVectorPoro &tvp, int &pos) const;
        void PostordenAux(TVectorPoro &tvp, int &pos) const;
        bool InsertarAux(const TPoro &tp, bool &creceArbol);
        bool BorrarAux(const TPoro &tp, bool &decreceArbol);
        TPoro ObtenerMayorIzquierda() const;
        bool MismoVolumen(const TPoro &tp) const;
        void DD();
        void II();
        void DI();
        void ID();
    public:
        TAVLPoro();
        TAVLPoro(const TAVLPoro &tavlp);
        ~TAVLPoro();
        TAVLPoro & operator=(const TAVLPoro &tavlp);
        bool operator==(const TAVLPoro &tabbp);
        bool operator!=(const TAVLPoro &tabbp); 
        bool EsVacio() const;
        bool Insertar(const TPoro &tp);
        bool Buscar(const TPoro &tp) const;
        bool Borrar(const TPoro &tp);
        int Altura() const;
        TPoro Raiz() const;
        int Nodos() const;
        int NodosHoja() const;
        TVectorPoro Inorden() const;
        TVectorPoro Preorden() const;
        TVectorPoro Postorden() const;
        // **** SOLO PARA PRUEBAS ***
        //TVectorPoro Niveles() const;
};
class TNodoAVL{
    friend class TAVLPoro;
    private:
        TPoro item;
        TAVLPoro iz, de;
        int fe;
    public:
        TNodoAVL();
        TNodoAVL(const TNodoAVL &tnavl);
        ~TNodoAVL();
        TNodoAVL & operator=(const TNodoAVL &tnavl);
};
#endif
