#ifndef _hola
#define _hola
#include <iostream>
#include "tcomplejo.h"
using namespace std;
class TListaNodo;
class TListaPos;
class TListaCom{
	friend class TListaNodo;//para poder acceder a los metodos privados
	private:
		TListaNodo *primero;
		TListaNodo *ultimo;
	public:
		TListaCom(); //
		TListaCom(const TListaCom &);//
		~TListaCom();//
		TListaCom &operator=(const TListaCom &);//
		bool operator==(const TListaCom &) const;//
		bool operator!=(const TListaCom &) const;//
		TListaCom operator+(const TListaCom &) const;//
		TListaCom operator-(const TListaCom &) const;//
		bool EsVacia() const;//
		bool InsCabeza(const TComplejo &);//
		bool InsertarI(const TComplejo &, const TListaPos &);//
		bool InsertarD(const TComplejo &, const TListaPos &);//
		bool Borrar(const TComplejo &); //
		bool BorrarTodos(const TComplejo &);
		bool Borrar(TListaPos &);
		TComplejo Obtener(const TListaPos &) const;//
		bool Buscar(const TComplejo &) const;//
		int Longitud() const; //
		TListaPos Primera() const;//
		TListaPos Ultima() const;//
		friend ostream &operator<<(ostream &,const TListaCom &);//
};


class TListaNodo
{
	friend class TListaCom; //para acceder a los metodos privados
	friend class TListaPos;
	private:
		TComplejo e;
		TListaNodo *anterior;
		TListaNodo *siguiente;
	public:
		TListaNodo();
		TListaNodo(const TListaNodo &);
		~TListaNodo();
		TListaNodo &operator=(const TListaNodo &);
		friend ostream & operator<<(ostream &, const TListaCom &);
};

class TListaPos
{
	friend class TListaCom;
	private:
		TListaNodo *pos;
	public:
		TListaPos();
		~TListaPos();
		TListaPos(const TListaPos &);
		TListaPos operator=(const TListaPos &);
		bool operator==(const TListaPos &) const;
		bool operator!=(const TListaPos &) const;
		TListaPos Anterior() const;
		TListaPos Siguiente() const;
		bool EsVacia() const;
};

#endif
