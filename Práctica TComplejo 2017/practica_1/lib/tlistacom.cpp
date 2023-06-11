#include "tlistacom.h"
#include "tcomplejo.h"
#include <iostream>
using namespace std;

//////////////// TListaCom //////////////////////////

// Constructor por defecto
TListaCom::TListaCom(){ primero=NULL; ultimo = NULL;}

// Constructor de copia
TListaCom::TListaCom(const TListaCom &copia){ primero=NULL; ultimo = NULL;  *this=copia;}

// Destructor
TListaCom::~TListaCom(){

	TListaNodo *actual;

	while(primero != NULL){
		actual=primero;
		primero = primero->siguiente;
		delete actual;
	}

	ultimo=NULL;
}

// Sobrecarga del operador asignación
TListaCom &TListaCom::operator=(const TListaCom &asignado)
{
	if(this != &asignado)
	{	
		this->~TListaCom(); //se destruye la lista inicial
		
		//voy insertando en la cabeza
		TListaNodo *nodo = asignado.ultimo;	
		while(nodo){ InsCabeza(nodo->e); nodo=nodo->anterior;}		
	}
	
	return *this;
}

// Sobrecarga del operador igualdad
bool TListaCom::operator==(const TListaCom &opDercha) const
{
	bool mismoNodo=true, UnalistaSinAcabar=false;
	
	TListaNodo *nodothis = primero; 
	TListaNodo *nodoParametro = opDercha.primero;

	while(nodothis != NULL && nodoParametro != NULL && mismoNodo == true){
		//si no encuentra ninguno diferente hasta que termine una de las dos listas se devolvera true
		if(nodothis->e == nodoParametro->e){
			
			nodothis = nodothis->siguiente;
			nodoParametro = nodoParametro->siguiente;
			
		}else{ mismoNodo=false;}
	}

	//compruebo si solo hay una lista terminada
	if( (nodothis != NULL) || (nodoParametro != NULL) ){ UnalistaSinAcabar=true;}
	
	//si hay solo una lista terminada pues no son mismo todo y devolvere false
	if(UnalistaSinAcabar){ mismoNodo=false;}
	
	return mismoNodo;
}

// Sobrecarga del operador desigualdad
bool TListaCom::operator!=(const TListaCom &opDercha) const
{
	bool desIgualdad=false;
	if(*this != opDercha){ desIgualdad=true;}
	return desIgualdad;
}

// Sobrecarga del operador suma
TListaCom TListaCom::operator+(const TListaCom &opDercha) const{
	
	TListaCom listaRetornar(*this);
	TListaNodo *nodoParametro = opDercha.primero;

	while(nodoParametro != NULL){

		//En la primera posicion inserto el primer nodo del operando de la derecha
		//Una vez insertado el primero voy insertando a la derecha de la lista a retornar (cogiendo la posicion ultima de esta)
		if(listaRetornar.EsVacia()){ listaRetornar.InsCabeza(nodoParametro->e);}
		else{ listaRetornar.InsertarD(nodoParametro->e, listaRetornar.Ultima());}
		
		nodoParametro = nodoParametro->siguiente;
	}
	
	return listaRetornar;
}

// Sobrecarga del operador resta
TListaCom TListaCom::operator-(const TListaCom &opDercha) const{
	
	TListaCom listaRetornar;
	TListaNodo *nodoParametro = primero;

	while(nodoParametro != NULL){
		
		//mete en la lista los elementos que no existen en la lista pasada por parametros (operando derecha)
		if(opDercha.Buscar(nodoParametro->e) == false){
			
			//En la primera posicion inserto el primer nodo del operando de la derecha
			//Una vez insertado el primero voy insertando a la derecha de la lista a retornar (cogiendo la posicion ultima de esta)
			if(listaRetornar.EsVacia()){ listaRetornar.InsCabeza(nodoParametro->e);}
			else{ listaRetornar.InsertarD(nodoParametro->e, listaRetornar.Ultima());}
		}
		
		nodoParametro = nodoParametro->siguiente;
	}
	return listaRetornar;
}

// Devuelve true si la lista está vacía, false en caso contrario
bool TListaCom::EsVacia() const{
	
	bool esVacia = false;
	if(primero == NULL){ esVacia = true;}
	return esVacia;
} 

// Inserta el elemento en la cabeza de la lista
bool TListaCom::InsCabeza(const TComplejo &compParametro){
	
	bool inserta = false;
	TListaNodo *nodo = new TListaNodo;
	
	if(nodo){
		
		nodo->siguiente = primero;
		
		if(primero){ primero->anterior = nodo;}
		else{ ultimo = nodo;}
		
		nodo->e = compParametro;                                   
		primero=nodo;
		
		inserta=true;
	}
	
	return inserta;
}

// Inserta el elemento a la izquierda de la posición indicada
bool TListaCom::InsertarI(const TComplejo &compParametro, const TListaPos &posParametro)
{
	bool sePuedeInsertar=false,estaPos=false;
	TListaNodo *nodo=new TListaNodo;
	TListaNodo *nodothis=primero;

	if(posParametro.EsVacia() == false){
		
		if(posParametro.pos != NULL){
			
			//busco si esta la posicion pasada por parametro
			while(nodothis && estaPos==false){
				
				if(nodothis != posParametro.pos){ nodothis = nodothis->siguiente;}
				else{ estaPos=true;}
			}
			
			if(estaPos){

				if(posParametro.pos==primero){ sePuedeInsertar = InsCabeza(compParametro);}
				else
				{
					if(nodo)
					{
						nodo->e = compParametro;
						nodo->siguiente = posParametro.pos;
						nodo->anterior = posParametro.pos->anterior;
						posParametro.pos->anterior->siguiente = nodo;
						posParametro.pos->anterior = nodo;

						sePuedeInsertar = true;
					}
				}
			}
		}
	}
	
	return sePuedeInsertar;
}

// Inserta el elemento a la derecha de la posición indicada
bool TListaCom::InsertarD(const TComplejo &compParametro, const TListaPos &posParametro)
{
	bool sePuedeInsertar=false,estaPos=false;
	TListaNodo *nodo=new TListaNodo;
	TListaNodo *nodothis=primero;

	if(posParametro.EsVacia() == false){
		//busco si esta la posicion pasada por parametro
		while(nodothis && estaPos==false){

			if(nodothis != posParametro.pos){ nodothis = nodothis->siguiente;}
			else{ estaPos=true;}
		}

		if(estaPos){

			if(nodo)
			{
				nodo->e = compParametro;
				nodo->siguiente = posParametro.pos->siguiente;
				nodo->anterior = posParametro.pos;

				if(posParametro.pos->siguiente == NULL){ ultimo = nodo;}
				else{ posParametro.pos->siguiente->anterior = nodo;}

				posParametro.pos->siguiente = nodo;

				sePuedeInsertar = true;			
			}
		}
	}
	return sePuedeInsertar;
}

// Busca y borra la primera ocurrencia del elemento
bool TListaCom::Borrar(const TComplejo &compParametros)
{
	bool ocurrenciaEncontrada=false,igualEncontrado=false;
	TListaNodo 	*nodoactual=primero;

	while(nodoactual && igualEncontrado==false)
	{
		if(nodoactual->e == compParametros){ igualEncontrado=true;}
		else{nodoactual = nodoactual->siguiente;}
	}
	
	if(igualEncontrado)
	{
		ocurrenciaEncontrada=true;
		
		TListaNodo *nodoanterior=nodoactual->anterior, *nodosiguiente=nodoactual->siguiente;

		if(nodoanterior){ nodoanterior->siguiente = nodosiguiente;}
		else{primero = nodosiguiente;}
		if(nodosiguiente){ nodosiguiente->anterior = nodoanterior;}
		else{ultimo = nodoanterior;}
		
		delete nodoactual; //borra ocurencia
	}
	
	return ocurrenciaEncontrada;	
}

// Busca y borra todas las ocurrencias del elemento
bool TListaCom::BorrarTodos(const TComplejo &compParametros){

	bool borradosTodos=false;
	while(Buscar(compParametros)){ Borrar(compParametros); borradosTodos=true;}
	return borradosTodos;
}

// Borra el elemento que ocupa la posición indicada
bool TListaCom::Borrar(TListaPos &posArgumentos)
{
	bool elementoEncontrado=false,encborrado=false;

	if(posArgumentos.EsVacia()==false){

		TListaNodo *nodo=primero;

		while(nodo && elementoEncontrado==false){

			if(nodo==posArgumentos.pos){ elementoEncontrado=true;}
			else{nodo=nodo->siguiente;}
		}

		if(elementoEncontrado)
		{
			TListaNodo *nodoanterior=nodo->anterior, *nodosiguiente=nodo->siguiente;

			if(nodoanterior){ nodoanterior->siguiente = nodosiguiente;}
			else{primero = nodosiguiente;}
			if(nodosiguiente){ nodosiguiente->anterior = nodoanterior;}
			else{ultimo = nodoanterior;}

			delete nodo;
			posArgumentos.pos=NULL;

			encborrado=true;
		}
	}

	return encborrado;
}


// Obtiene el elemento que ocupa la posición indicada
TComplejo TListaCom::Obtener(const TListaPos &p) const{
	
	TComplejo elemento;
	TListaNodo *nodo = primero;
	bool elementoEncontrado = false;

	while(nodo && elementoEncontrado==false)
	{
		if(nodo == p.pos){ elementoEncontrado = true;}
		else{nodo = nodo->siguiente;}
	}

	if(elementoEncontrado){ elemento = nodo->e;}

	return elemento;
}

// Devuelve true si el elemento está en la lista, false en caso contrario
bool TListaCom::Buscar(const TComplejo &compParametros) const{

	bool esta=false;
	TListaNodo *nodo=primero;

	while(nodo != NULL && !esta){

		if(nodo->e == compParametros){ esta=true;}
		else{nodo = nodo->siguiente;}
	}

	return esta;
}

// Devuelve la longitud de la lista
int TListaCom::Longitud() const{

	int longitudLista = 0;
	TListaNodo *nodo=primero;

	while(nodo){ longitudLista++; nodo = nodo->siguiente;}

	return longitudLista;
}

// Devuelve la primera posición en la lista
TListaPos TListaCom::Primera() const{

    TListaPos primera;
	primera.pos = primero;
	return primera;
}

// Devuelve la última posición en la lista
TListaPos TListaCom::Ultima() const{

	TListaPos ultima;
	ultima.pos = ultimo;
	return ultima;
}

ostream &operator<<(ostream &os, const TListaCom &lista){

	TListaNodo *nodo=lista.primero;

	if(lista.primero != NULL)
	{
		os << "{";
		
		while(nodo){ os << nodo->e; if(nodo->siguiente){ os << ' ';} nodo = nodo->siguiente;}
		
		os << "}";
		
	}else{ os << "{}";}
	
	return os;
}


//////////////// TListaNodo /////////////////////////

// Constructor por defecto
TListaNodo::TListaNodo(){ anterior=NULL; siguiente = NULL;}

// Constructor de copia
TListaNodo::TListaNodo(const TListaNodo &nodo){ e = nodo.e; anterior = nodo.anterior; siguiente = nodo.siguiente;}

// Destructor
TListaNodo::~TListaNodo(){ anterior=NULL; siguiente = NULL;}

// Sobrecarga del operador asignación
TListaNodo &TListaNodo::operator=(const TListaNodo &nod){

	if(this != &nod){ siguiente = nod.siguiente; anterior = nod.anterior; e = nod.e;}
	return *this;
}


//////////////// TListaPos /////////////////////////

// Constructor por defecto
TListaPos::TListaPos(){ pos=NULL;}

// Constructor de copia	
TListaPos::TListaPos(const TListaPos &p){ pos=p.pos;}

// Destructor
TListaPos::~TListaPos(){ pos=NULL;}

// Sobrecarga del operador asignación
TListaPos TListaPos::operator=(const TListaPos &p){ pos=p.pos; return *this;}

// Sobrecarga del operador igualdad
bool TListaPos::operator==(const TListaPos &p) const{
	
	bool igualdad=false;
	if(pos==p.pos){ igualdad=true;}
	return igualdad;
}

// Sobrecarga del operador desigualdad
bool TListaPos::operator!=(const TListaPos &p) const{
	
	bool desigualdad=false;
	if(pos!=p.pos){ desigualdad=true;}
	return desigualdad;
}

// Devuelve la posición anterior
TListaPos TListaPos::Anterior() const{
	
	TListaPos posAnterior;
	if(pos){ posAnterior.pos = pos->anterior;}
	return posAnterior;
}

// Devuelve la posición siguiente
TListaPos TListaPos::Siguiente() const{
	
	TListaPos posAnterior;
	if(pos){ posAnterior.pos = pos->siguiente;}
	return posAnterior;
}

// Devuelve TRUE si la posición no apunta a una lista, FALSE en caso contrario
bool TListaPos::EsVacia() const{
	
	bool esVacia=false;
	if(pos==NULL){ esVacia=true;}
	return esVacia;
}
