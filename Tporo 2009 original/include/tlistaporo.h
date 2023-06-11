#ifndef TLISTAPORO_H_
#define TLISTAPORO_H_

#include "tporo.h"

class TListaPosicion;
class TListaNodo;

class TListaPoro {
	friend ostream & operator<<(ostream &os, const TListaPoro &tlp);
	private:
		TListaNodo *primero;
		TListaNodo *ultimo;
		// ----------------- METODOS DE INSERCIÓN -----------------
		bool InsertarVacia(const TPoro &tp);
		bool InsertarInicioLista(const TPoro &tp);
		bool InsertarFinalLista(const TPoro &tp);
		bool InsertarDetrasNodo(const TPoro &tpNuevo, const TListaPosicion &pos);
		// ------------------ METODOS DE BORRADO -------------------
		bool BorrarUnicoElemento();
		bool BorrarPrimerElemento(const TListaPosicion &tlp);
		bool BorrarUltimoElemento(const TListaPosicion &tlp);  
		bool BorrarElementoIntermedio(const TListaPosicion &tlp);
		// ----------------------------------------------------------
	public:
		TListaPoro();
		TListaPoro(const TListaPoro &tlp);
		~TListaPoro();
		TListaPoro & operator=(const TListaPoro &tlp);
		bool operator==(const TListaPoro &tlp) const;
		TListaPoro operator+(const TListaPoro &tlp) const; 
		TListaPoro operator-(const TListaPoro &tlp) const; 
		bool EsVacia() const;
		bool Insertar(const TPoro &tp);
		bool Borrar(const TPoro &tp);
		bool Borrar(TListaPosicion &tlp);
		TPoro Obtener(const TListaPosicion &tlp) const;
		bool Buscar(const TPoro &tp) const;
		int Longitud() const;
		TListaPosicion Primera() const;
		TListaPosicion Ultima() const;
		TListaPoro ExtraerRango(int, int);
};


class TListaPosicion{
	friend class TListaPoro;
	private:
		TListaNodo *pos;
	public:
		TListaPosicion();
		TListaPosicion(const TListaPosicion &tlp);
		~TListaPosicion();
		TListaPosicion & operator=(const TListaPosicion &tlp);
		bool operator==(const TListaPosicion &tlp);
		TListaPosicion Anterior() const;
		TListaPosicion Siguiente() const;
		bool EsVacia() const;
};

class TListaNodo{
	friend class TListaPosicion;
	friend class TListaPoro;
	private:
		TPoro e;
		TListaNodo *anterior;
		TListaNodo *siguiente;
	public:
		TListaNodo();
		TListaNodo(const TListaNodo &tln);
		~TListaNodo();
		TListaNodo & operator=(const TListaNodo &tln);
};

#endif
