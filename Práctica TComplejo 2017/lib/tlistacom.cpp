#include "tlistacom.h"
#include "tcomplejo.h"
#include <iostream>
using namespace std;

//METODOS DE LA LISTA TLISTANODO

TListaNodo::TListaNodo()
{
	anterior = siguiente = NULL;
}

TListaNodo::TListaNodo(const TListaNodo &n)
{
	anterior = n.anterior;
	siguiente = n.siguiente;
	e = n.e;
}

TListaNodo::~TListaNodo()
{
	anterior = siguiente = NULL;
}

TListaNodo &TListaNodo::operator=(const TListaNodo &de)
{
	if(this != &de)
	{
		siguiente = de.siguiente;
		anterior = de.anterior;
		e = de.e;
	}
	return *this;
}

TListaCom::TListaCom()
{
	primero = ultimo = NULL;
}

TListaCom::TListaCom(const TListaCom &l)
{
//	primero = ultimo = NULL;
//  *this = l;

	TListaNodo *ptL;

	primero = ultimo = NULL;
	ptL = l.ultimo;
	while(ptL){
		InsCabeza(ptL->e);
		ptL = ptL->anterior;
	}		
}

// operador asignacion:
// sin utilizar TListaPos.
TListaCom &TListaCom::operator=(const TListaCom &l)
{
	TListaNodo *ptL;
	if(this != &l)
	{
		this->~TListaCom();
		ptL = l.ultimo;
		while(ptL)
		{
			InsCabeza(ptL->e);
			ptL = ptL->anterior;
		}		
	}
	/*
	TPosicion p = l.Ultima();
	while(p.EsVacia() == false){
		InsCabeza(l.Obtener(p));
		p = p.Anterior();
	}
	*/
	return *this;
}

// operador asignacion:
// utizando TListaPos

TListaCom::~TListaCom()
{
	TListaNodo *aux;
	
	aux = primero;
	while(primero)
	{
		primero = primero->siguiente;
		delete aux;
		aux = primero;
	}
	primero = ultimo = NULL;
/*
	while(primero != null){
		aux = primero;
		primero = primero->siguiente;
		delete aux;
	}
	ultimo = NULL;
*/
}

bool TListaCom::EsVacia() const{
	bool enc = false;
	if(primero == NULL){
		enc = true;
	}
	return enc;
	// return primero == ultimo && primero == NULL;
}                                                         

bool TListaCom::InsCabeza(const TComplejo &c)
{
	bool devuelve = false;
	TListaNodo *ptN;
	
	ptN = new TListaNodo;
	if(ptN)
	{
		devuelve = true;
		ptN->siguiente = primero;
		if(primero)
			primero->anterior = ptN;
		else
			ultimo = ptN;
		ptN->e = c;                                   
		primero = ptN;
	}
	return devuelve;
}

bool TListaCom::InsertarI(const TComplejo &c, const TListaPos &p)
{
	bool insertado = false;
	TListaNodo *ptN, *ptL;

	bool encontrada;
	encontrada = false;
	ptL = primero;
	while(ptL && !encontrada)
	{
		if(ptL == p.pos)
			encontrada = true;
		else
			ptL = ptL->siguiente;
	}
	if(encontrada == true){
		if(p.pos != NULL){
			if(p.pos == primero)
				insertado = InsCabeza(c);
			else
			{
				ptN = new TListaNodo;
				if(ptN)
				{
					insertado = true;
					ptN->e = c;
					ptN->siguiente = p.pos;
					ptN->anterior = p.pos->anterior;
					p.pos->anterior->siguiente = ptN;
					p.pos->anterior = ptN;
				}
			}
		}
	}
	return insertado;
}

bool TListaCom::InsertarD(const TComplejo &c, const TListaPos &p)
{
	bool insertado = false;
    TListaNodo *ptN, *ptL;
	bool encontrada = false;	
	
	ptL = primero;
	while(ptL && !encontrada){
		if(ptL == p.pos)
			encontrada = true;
		else
			ptL = ptL->siguiente;
	}
	if(encontrada == true){
		if(!p.EsVacia())
		{
			ptN = new TListaNodo;
			if(ptN)
			{
				insertado = true;
				// al final.
				ptN->e = c;
				ptN->siguiente = p.pos->siguiente;
				ptN->anterior = p.pos;
				if(p.pos->siguiente == NULL)
					ultimo = ptN;
				else
					p.pos->siguiente->anterior = ptN;
				p.pos->siguiente = ptN;
			}
		}
	}
	return insertado;
}
TListaPos TListaCom::Primera() const
{
    TListaPos aux;
	aux.pos = primero;
	return aux;
}

TListaPos TListaCom::Ultima() const
{
	TListaPos aux;
	aux.pos = ultimo;
	return aux;
}

TComplejo TListaCom::Obtener(const TListaPos &p) const
{
	TComplejo aux;
	TListaNodo *ptL;
	bool encontrado;
	
	encontrado = false;
	ptL = primero;
	while(ptL && !encontrado)
	{
		if(ptL == p.pos)
			encontrado = true;
		else
			ptL = ptL->siguiente;
	
	}
	if(encontrado)
		aux = ptL->e;
		
	return aux;
}

bool TListaCom::operator==(const TListaCom &de) const
{
	TListaNodo *ptL1, *ptL2;
	bool iguales;
	
	ptL1 = primero;		// operando izquierdo (implicito) 
	ptL2 = de.primero;  // operando derecho (explicito, parametro)
	iguales = true;
	while(ptL1 != NULL && ptL2 != NULL && iguales == true){
		if(ptL1->e != ptL2->e){
			iguales = false;
		}
		else{
			ptL1 = ptL1->siguiente;
			ptL2 = ptL2->siguiente;
		}
	}
	// hay una lista que no he acabado. 
	if(ptL1 != NULL || ptL2 != NULL){
		iguales = false;
	}
	return iguales;
/*
	ptL1 = primero;
	ptL2 = de.primero;
	while(ptL1 && ptL2 && ptL1->e == ptL2->e){
		ptL1 = ptL1->siguiente;
		ptL2 = ptL2->siguiente;
	}
	if(!ptL1 && !ptL2){
		iguales = true;
	}
	else{
		iguales = false;
	}
	return iguales;
*/
}

int TListaCom::Longitud() const
{
	int num = 0;
	TListaNodo *ptL = primero;
	
	while(ptL)
	{
		num++;
		ptL = ptL->siguiente;
	}
       return num;
}

bool TListaCom::operator!=(const TListaCom &de) const
{
	return !(*this == de);
}


/*
//             *   *
// *this = {1, 2, 3}
// de = {4, 5}

// aux = {4, 5}
// aux = {3, 4, 5}
// aux = {2, 3, 4, 5}
TListaCom TListaCom::operator+(const TListaCom &de) const
{
	TListaCom aux(de);
    TListaNodo *ptL;
	
	ptL = ultimo;
	while(ptL)
	{
		aux.InsCabeza(ptL->e);
		ptL = ptL->anterior;
	}
	
	return aux;
}
*/
TListaCom TListaCom::operator+(const TListaCom &de) const{
	TListaCom aux(*this);
	TListaNodo *ptl;

	ptl = de.primero;
	while(ptl != NULL){
		if(aux.EsVacia() == true){
			aux.InsCabeza(ptl->e);
		}
		else{
			aux.InsertarD(ptl->e, aux.Ultima());
		}		
		ptl = ptl->siguiente;
	}	
	return aux;
}

/*
TListaCom TListaCom::operator-(const TListaCom &de) const{
	TListaCom aux;
	TListaNodo *ptL;
	
	ptL = ultimo;
	while(ptL)
	{
		if(!(de.Buscar(ptL->e)))
			aux.InsCabeza(ptL->e);
		ptL = ptL->anterior;
	}
	return aux;
}
*/
TListaCom TListaCom::operator-(const TListaCom &de) const{
	TListaCom aux;
	TListaNodo *ptL;
	
	ptL = primero;
	while(ptL != NULL){
		if(de.Buscar(ptL->e) == false){
			if(aux.EsVacia() == true){
				aux.InsCabeza(ptL->e);
			}
			else{
				aux.InsertarD(ptL->e, aux.Ultima());
			}
		}
		ptL = ptL->siguiente;
	}
	return aux;
}




bool TListaCom::Buscar(const TComplejo &c) const{
	TListaNodo *ptL;
	bool encontrado;
	encontrado = false;
	ptL = primero;
	while(ptL != NULL && encontrado == false){
		if(ptL->e == c){
			encontrado = true;
		}
		else{
			ptL = ptL->siguiente;
		}
	}
	return encontrado;
}

bool TListaCom::Borrar(const TComplejo &c)
{
	bool encontrado;
	TListaNodo 	*ptL,	// al sitio
			*ptA,	// al anterior
			*ptS;	// al siguiente
	ptL = primero;
	encontrado = false;
	while(ptL && !encontrado)
	{
		if(ptL->e == c)
			encontrado = true;
		else
			ptL = ptL->siguiente;
	}
	if(encontrado)
	{
		ptA = ptL->anterior;
		ptS = ptL->siguiente;
/*
	ptA		ptL		ptS
	sig				ant
*/
		if(ptA)
			ptA->siguiente = ptS;
		else
			primero = ptS;
		if(ptS)
			ptS->anterior = ptA;
		else
			ultimo = ptA;
		delete ptL;
	}
	return encontrado;	
}
/*
bool TListaCom::Borrar(TListaPos &p)
{
	bool encontrada = false;
	TListaNodo *ptL, *ptA, *ptS;

	if(!p.EsVacia())
	{
		encontrada = false;
		ptL = primero;
		while(ptL && !encontrada)
		{
			if(ptL == p.pos)
				encontrada = true;
			else
				ptL = ptL->siguiente;
		}
		if(encontrada)
		{
			ptA = ptL->anterior;
			ptS = ptL->siguiente;
			if(ptA)
				ptA->siguiente = ptS;
			else
				primero = ptS;
			if(ptS)
				ptS->anterior = ptA;
			else
				ultimo = ptA;
			delete ptL;
			p.pos = NULL;
		}
	}
	return encontrada;
}
*/
// quitar en la entrega que esto es otra forma de hacerla :) viva auladoce!!
bool TListaCom::Borrar(TListaPos &p){
	bool encontrada = false;
	TListaNodo *ptL;
	if(!p.EsVacia()){
		encontrada = false;
		ptL = primero;
		while(ptL && !encontrada)
		{
			if(ptL == p.pos)
				encontrada = true;
			else
				ptL = ptL->siguiente;
		}
		if(encontrada){
			if(ptL == primero){ // primero.
				primero = primero->siguiente;
				if(primero != NULL){
					primero->anterior = NULL;
				}									
			}
			else{
				if(ptL == ultimo){
					ultimo = ultimo->anterior;
					if(ultimo != NULL){
						ultimo->siguiente = NULL;
					}
				}
				else{
					ptL->anterior->siguiente = ptL->siguiente;
					ptL->siguiente->anterior = ptL->anterior;
				}
			}
			delete ptL;
			p.pos = NULL;
		}
	}
	return encontrada;
}
bool TListaCom::BorrarTodos(const TComplejo &c){
	bool borrado;

	borrado = Borrar(c);
	while(Borrar(c));
	return borrado;
}


/*
bool TListaCom::BorrarTodos(const TComplejo &c){
	bool borrado = false;

	while(Buscar(c)){
		Borrar(c);
		borrado = true;
	}

	return borrado;
}
*/
/*
bool TListaCom::BorrarTodos(const TComplejo &c){
	bool borrado;
	borrado = false;
	while(Borrar(c)){
		borrado = true;	
	}
	return borrado;
}
*/
/*
bool TListaCom::BorrarTodos(const TComplejo &c){
	bool borrado;
	int borrados;	
	borrados = 0;
	while(Borrar(c)){
		borrados++;	
	}
	if(borrado > 0){
		borrado = true;
	}
	else{
		borrado = false;
	}
	return borrado;
}
*/


/*
bool TListaCom::BorrarTodos(const TComplejo &c){
	bool borrado;
	TListaNodo *ptL, *ptA, *ptS, *ptB;

	ptL = primero;
	borrado = false;
	while(ptL){
		if(ptL->e == c)
		{
			borrado = true;
			ptA = ptL->anterior;
			ptS = ptL->siguiente;
			ptB = ptL;
			if(ptA)
			{
				ptA->siguiente = ptS;
				ptL = ptS;
			}
			else
			{
				primero = ptS;
				ptL = primero;
			}
			if(ptS)
				ptS->anterior = ptA;
			else
				ultimo = ptA;
			delete ptB;
		}
		else
			ptL = ptL->siguiente;			
	}
	return borrado;
}
*/

ostream & operator<<(ostream &o, const TListaCom &l)
{
	TListaNodo *ptL;

	if(l.primero != NULL)
	{
		o << "{";
		ptL = l.primero;
		while(ptL)
		{
			o << ptL->e;
			if(ptL->siguiente)
				o << ' ';
			ptL = ptL->siguiente;
		}
		o << "}";
	}
	else
		o << "{}";
	
	return o;
}

TListaPos::TListaPos()
{
	pos = NULL;
}

TListaPos::~TListaPos()
{
	pos = NULL;
}

TListaPos::TListaPos(const TListaPos &p){
	pos = p.pos;
}

TListaPos TListaPos::operator=(const TListaPos &p){
	pos = p.pos;
	return *this;
}

bool TListaPos::operator==(const TListaPos &de) const
{
	return pos == de.pos;
}

bool TListaPos::operator!=(const TListaPos &de) const
{
	return pos != de.pos;
}

TListaPos TListaPos::Anterior() const
{
	TListaPos aux;
	
	if(pos)
		aux.pos = pos->anterior;

	return aux;
}

TListaPos TListaPos::Siguiente() const
{
	TListaPos aux;
	
	if(pos)
		aux.pos = pos->siguiente;

	return aux;

}

bool TListaPos::EsVacia() const
{
	return pos == NULL;
}
