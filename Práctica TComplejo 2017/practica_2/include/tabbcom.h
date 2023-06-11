#ifndef tabbcom
#define tabbcom
#include <iostream>
using namespace std;

#include "tcomplejo.h"
#include "tvectorcom.h"
class TABBCom;
class TNodoABB;

class TABBCom
{
	private:
	
		TNodoABB *nodo;// Puntero al nodo
		TComplejo izqMayor() const;// AUXILIAR : Devuelve el mayor de la izquierda
		void InordenAux(TVectorCom &, int &) const;// AUXILIAR : Devuelve el recorrido en inorden
		void PreordenAux(TVectorCom &, int &) const;// AUXILIAR : Devuelve el recorrido en preorden
		void PostordenAux(TVectorCom &, int &) const;// AUXILIAR : Devuelve el recorrido en postorden
        
	public:

		//FORMA CANÓNICA
		TABBCom();//Constructor por defecto
		TABBCom(const TABBCom &);//Constructor de copia
		~TABBCom();//Destructor
		TABBCom &operator=(const TABBCom &);//Sobrecarga del operador asignación
		
		// MÉTODOS
		bool operator==(const TABBCom &) const;//Sobrecarga del operador igualdad
		bool EsVacio() const;//Devuelve TRUE si el árbol está vacío, FALSE en caso contrario
		bool Insertar(const TComplejo &);//Inserta el elemento en el árbol
		bool Borrar(const TComplejo &);//Borra el elemento en el árbol
		bool Buscar(const TComplejo &) const;//Devuelve TRUE si el elemento está en el árbol, FALSE en caso contrario
		TComplejo Raiz() const;//Devuelve el elemento en la raíz del árbol
		int Altura() const;//Devuelve la altura del árbol (la altura de un árbol vacío es 0)
		int Nodos() const;//Devuelve el número de nodos del árbol (un árbol vacío posee 0 nodos)
		int NodosHoja() const;//Devuelve el número de nodos hoja en el árbol (la raíz puede ser nodo hoja)
		TVectorCom Inorden() const;//Devuelve el recorrido en inorden
		TVectorCom Preorden() const;//Devuelve el recorrido en preorden
		TVectorCom Postorden() const;//Devuelve el recorrido en postorden
		TVectorCom Niveles() const;//Devuelve el recorrido en niveles
		friend ostream &operator<<(ostream &os, const TABBCom &de);//Sobrecarga del operador salida
    
};

class TNodoABB{

    friend class TABBCom;//Clase amiga

    private:

        TComplejo item;//El elemento del nodo
        TABBCom iz,de;//Subárbol izquierdo y derecho

    public:

        TNodoABB();// Constructor por defecto
        TNodoABB(const TNodoABB &);// Constructor de copia
        ~TNodoABB();// Destructor
	TNodoABB(const TComplejo &);// Sobrecarga del operador asignación
};
#endif
