#ifndef _tavldir
#define _tavldir
#include <iostream>
#include "tcomplejo.h"
#include "tvectorcom.h"
#include <queue>

using namespace std;

class TAVLNodo;
class TAVLCom
{
	public:
		TAVLCom();					// Constructor por defecto.
		TAVLCom(const TAVLCom &);			// Constructor de copia.
		~TAVLCom();					// Destructor.
		TAVLCom &operator=(const TAVLCom &);		// Operador asignaci�.
		bool operator==(const TAVLCom &) const;	// Sobrecarga del operador igualdad.
		bool operator!=(const TAVLCom &) const;	// Sobrecarga del operador distinto.
		bool EsVacio() const;				// Devuelve true si el arbol esta vacio, false en caso contrario.
		bool Insertar(const TComplejo &c);		// Inserta el elemento en el arbol.
		bool Buscar(const TComplejo &)const;		// Devuelve true si el elemento esta en el arbol y false en caso contrario.
		int Altura() const;			// Devuelve la altrua del arbol (la altura del arbol vacio es 0).
		int Nodos() const;			// Devuelve el numero de nodos del arbol, arbol vacio = 0 nodos.
		int NodosHoja() const;			// Devuelve el numero de nodos hojas.
		TVectorCom Inorden() const;		// Recorrido inorden.
		TVectorCom Postorden() const;		// Recorrido postorden.
		TVectorCom Preorden() const;		// Recorrido preorden.
		TVectorCom Niveles() const;		// Recorrido niveles.
		bool Borrar(const TComplejo &);
	private: 
		TComplejo BuscarMayor() const;
		bool Borrar(const TComplejo &, bool &);
		bool Insertar(const TComplejo &, bool &);
		void InordenAux(TVectorCom &, int &) const;
		void PostordenAux(TVectorCom &, int &) const;
		void PreordenAux(TVectorCom &, int &) const;
		void II();
		void ID();
		void DD();
		void DI();
		TAVLNodo *raiz;
};

class TAVLNodo
{
	friend class TAVLCom;
	private:
		TAVLCom iz, de;
		TComplejo item;
		int fe;
	public:
		TAVLNodo();
		TAVLNodo(const TAVLNodo &);
		~TAVLNodo();
		TAVLNodo &operator=(const TAVLNodo &);
};

class TColaAVLNodo
{
	private:
		struct TNodo
		{
			void *item;
			TNodo *sig;		
		};
		TNodo *tope, *fondo;
	public:
		TColaAVLNodo();
		~TColaAVLNodo();
		void * Desencolar();
		void Encolar(void *);
		bool EsVacia() const {return tope == NULL;}
};

#endif
