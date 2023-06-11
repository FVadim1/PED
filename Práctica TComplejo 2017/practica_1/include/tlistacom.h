#ifndef _TListaCom
#define _TListaCom
#include "tcomplejo.h"
#include <iostream>
using namespace std;

class TListaNodo;
class TListaPos;

class TListaCom{
	
	//Acceso a los elementos privados de tlnodo
	friend class TListaNodo;

	private:
	
		TListaNodo *primero;// Primer elemento de la lista
		TListaNodo *ultimo;// Ultimo elemento de la lista
		
	public:
	
		//FORMA CANONICA
		TListaCom();// Constructor por defecto
		TListaCom(const TListaCom &);// Constructor de copia
		~TListaCom();// Destructor
		TListaCom &operator=(const TListaCom &);// Sobrecarga del operador asignación
		
		//METODOS
		bool operator==(const TListaCom &) const;// Sobrecarga del operador igualdad
		bool operator!=(const TListaCom &) const;// Sobrecarga del operador desigualdad
		
		TListaCom operator+(const TListaCom &) const;// Sobrecarga del operador suma
		TListaCom operator-(const TListaCom &) const;// Sobrecarga del operador resta
		
		bool EsVacia() const;// Devuelve true si la lista está vacía, false en caso contrario
		bool InsCabeza(const TComplejo &);// Inserta el elemento en la cabeza de la lista
		bool InsertarI(const TComplejo &, const TListaPos &);// Inserta el elemento a la izquierda de la posición indicada
		bool InsertarD(const TComplejo &, const TListaPos &);// Inserta el elemento a la derecha de la posición indicada
		bool Borrar(const TComplejo &);// Busca y borra la primera ocurrencia del elemento
		bool BorrarTodos(const TComplejo &);// Busca y borra todas las ocurrencias del elemento
		bool Borrar(TListaPos &);// Borra el elemento que ocupa la posición indicada
		TComplejo Obtener(const TListaPos &) const;// Obtiene el elemento que ocupa la posición indicada
		bool Buscar(const TComplejo &) const;// Devuelve true si el elemento está en la lista, false en caso contrario
		int Longitud() const;// Devuelve la longitud de la lista
		TListaPos Primera() const;// Devuelve la primera posición en la lista
		TListaPos Ultima() const;// Devuelve la última posición en la lista
		
		friend ostream &operator<<(ostream &,const TListaCom &);
};

class TListaNodo
{
	//Acceso a los elementos privados de tlcom y tlpos
	friend class TListaCom;
	friend class TListaPos;

	private:

		TComplejo e;// El elemento del nodo
		TListaNodo *anterior;// El nodo anterior
		TListaNodo *siguiente;// El nodo siguiente

	public:

		TListaNodo();// Constructor por defecto
		TListaNodo(const TListaNodo &);// Constructor de copia
		~TListaNodo();// Destructor
		TListaNodo &operator=(const TListaNodo &);// Sobrecarga del operador asignación

		friend ostream &operator<<(ostream &, const TListaCom &);
};

class TListaPos
{
	friend class TListaCom;

	private:

		TListaNodo *pos;// Puntero a un nodo de la lista

	public:

		TListaPos();// Constructor por defecto
		TListaPos(const TListaPos &);// Constructor de copia		
		~TListaPos();// Destructor
		TListaPos operator=(const TListaPos &);// Sobrecarga del operador asignación
		bool operator==(const TListaPos &) const;// Sobrecarga del operador igualdad
		bool operator!=(const TListaPos &) const;// Sobrecarga del operador desigualdad
		TListaPos Anterior() const;// Devuelve la posición anterior
		TListaPos Siguiente() const;// Devuelve la posición siguiente
		bool EsVacia() const;// Devuelve TRUE si la posición no apunta a una lista, FALSE en caso contrario
};

#endif
