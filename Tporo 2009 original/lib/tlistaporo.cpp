
#include "tlistaporo.h"

// --------------------------- TLISTANODO ----------------------------------
TListaNodo::TListaNodo(){
	anterior = siguiente = NULL;
}

TListaNodo::TListaNodo(const TListaNodo &tln){
	e = tln.e;
	anterior = tln.anterior;
	siguiente = tln.siguiente;
}


TListaNodo::~TListaNodo(){
	anterior = siguiente = NULL;
}

TListaNodo & TListaNodo::operator=(const TListaNodo &tln){
	if(this != &tln){
		(*this).~TListaNodo();
		this->e = tln.e;
	}
	return *this;
}

// --------------------------- TLISTAPOSICION ----------------------------------
TListaPosicion::TListaPosicion(){
	pos = NULL;
}

TListaPosicion::TListaPosicion(const TListaPosicion &tlp){
	pos = tlp.pos;
}

TListaPosicion::~TListaPosicion(){
	pos = NULL;
}

TListaPosicion & TListaPosicion::operator=(const TListaPosicion &tlp){
	if(this != &tlp){
		(*this).~TListaPosicion();
		pos = tlp.pos;
	}
	return *this;
}

bool TListaPosicion::operator==(const TListaPosicion &tlp){
	bool iguales = false;
	if(pos == tlp.pos){
		iguales = true;
	}
	return iguales;
}

TListaPosicion TListaPosicion::Anterior()const{
	TListaPosicion aux;
	if(pos == NULL){
		aux.pos = NULL;
	}
	else{
		aux.pos = pos->anterior;
	}
	return aux;
}

TListaPosicion TListaPosicion::Siguiente()const{
	TListaPosicion aux;
	if(pos == NULL){
		aux.pos = NULL;
	}
	else{
		aux.pos = pos->siguiente;
	}
	return aux;
}

bool TListaPosicion::EsVacia() const{
	return (pos == NULL);
}

// ---------------------------- TLISTAPORO -----------------------------
TListaPoro::TListaPoro(){
	primero = NULL;
	ultimo = NULL;
}
TListaPoro::TListaPoro(const TListaPoro &tlp){
	primero = tlp.primero;
	ultimo = tlp.ultimo;
}
TListaPoro::~TListaPoro(){
	TListaPosicion p, q;
	q = Primera();
	while(!q.EsVacia()){
		p = q;
		q = q.Siguiente();
		delete p.pos;
	}
	primero = NULL;
	ultimo = NULL;
}
TListaPoro &TListaPoro::operator=(const TListaPoro &tlp){
	if(this != &tlp){
		(*this).~TListaPoro();
		primero = NULL;
		ultimo = NULL;
		for(TListaPosicion actual = tlp.Primera(); !actual.EsVacia(); actual = actual.Siguiente()){
			Insertar(actual.pos->e);
		}
	}
	return *this;
}

bool TListaPoro::operator==(const TListaPoro &tlp) const{
	TListaPosicion aux = tlp.Primera();
	bool iguales = true;
	for(TListaPosicion actual = Primera(); !actual.EsVacia() && iguales; actual = actual.Siguiente()){
		if(aux.EsVacia() || actual.pos->e != aux.pos->e){
			iguales = false;
		}
		aux = aux.Siguiente();
	}
	return iguales;
} 
TListaPoro TListaPoro::operator+(const TListaPoro &tlp) const{
	TListaPoro nueva;
	for(TListaPosicion actual = Primera(); !actual.EsVacia(); actual = actual.Siguiente()){
		nueva.Insertar(actual.pos->e);
	}
	for(TListaPosicion actual = tlp.Primera(); !actual.EsVacia(); actual = actual.Siguiente()){
		nueva.Insertar(actual.pos->e);
	}
	return nueva;
}

TListaPoro TListaPoro::operator-(const TListaPoro &tlp) const{
	TListaPoro nueva = *this;
	for(TListaPosicion actual = Primera(); !actual.EsVacia(); actual = actual.Siguiente()){
		if(tlp.Buscar(actual.pos->e)){
			nueva.Borrar(actual.pos->e);
		}
	}
	return nueva;
}

bool TListaPoro::EsVacia() const{
	return (primero == NULL && ultimo == NULL);
}

bool TListaPoro::InsertarVacia(const TPoro &tp){
	bool insertado = false;
	TListaNodo *nodoNuevo = new TListaNodo();
	nodoNuevo->e = tp;
	primero = ultimo = nodoNuevo;
	insertado = true;
	return insertado;
}

bool TListaPoro::InsertarInicioLista(const TPoro &tp){
	bool insertado = false;
	TListaNodo *nodoNuevo = new TListaNodo();
	nodoNuevo->e = tp;
	primero->anterior = nodoNuevo;
	nodoNuevo->siguiente = primero;
	primero = nodoNuevo;
	insertado = true;
	return insertado;
}

bool TListaPoro::InsertarFinalLista(const TPoro &tp){
	bool insertado = false;
	TListaNodo *nodoNuevo = new TListaNodo();
	nodoNuevo->e = tp;
	ultimo->siguiente = nodoNuevo;
	nodoNuevo->anterior = ultimo;
	ultimo = nodoNuevo;
	insertado = true;
	return insertado;
}

bool TListaPoro::InsertarDetrasNodo(const TPoro &tpnuevo, const TListaPosicion &posaux){
	bool insertado = false;
	TListaNodo *nuevoNodo = new TListaNodo();
	nuevoNodo->e = tpnuevo;
	nuevoNodo->siguiente = posaux.pos;
	nuevoNodo->anterior = posaux.pos->anterior;
	posaux.pos->anterior->siguiente = nuevoNodo;
	posaux.pos->anterior = nuevoNodo;
	insertado = true;
	return insertado;
}

bool TListaPoro::Insertar(const TPoro &tp){
	bool insertado = false;
	bool existe;
	double volumenNuevo = tp.Volumen();
	double volumenActual;
	TListaPosicion posaux;
	if(EsVacia()){
		insertado = InsertarVacia(tp);
	}
	else{
		existe = Buscar(tp);
		if(!existe){
			TListaPosicion actual = Primera();
			while(!actual.EsVacia() && !insertado){
				volumenActual = actual.pos->e.Volumen();
				if(volumenNuevo < volumenActual){
					if(actual == Primera()){
						insertado = InsertarInicioLista(tp);
					}
					else{
						insertado = InsertarDetrasNodo(tp, actual);
					}
				}
				else{
					actual = actual.Siguiente();
				}
			}
			if(!insertado){
				insertado = InsertarFinalLista(tp);
			}
		}
	}
	return insertado;
}

bool TListaPoro::Borrar(const TPoro &tp){ 
	bool borrado = false;
	bool existe = Buscar(tp);
	if(existe){
		for(TListaPosicion actual = Primera(); !actual.EsVacia() && !borrado; actual = actual.Siguiente()){
			if(actual.pos->e == tp){
				borrado = Borrar(actual);
			}
		}
	}
	return borrado;
}

bool TListaPoro::BorrarUnicoElemento(){
	bool borrado = false;
	primero = ultimo = NULL;
	borrado = true;
	return borrado;
}

bool TListaPoro::BorrarPrimerElemento(const TListaPosicion &tlp){
	bool borrado = false;
	primero = primero->siguiente;
	primero->anterior = NULL;
	borrado = true;
	return borrado;
}

bool TListaPoro::BorrarUltimoElemento(const TListaPosicion &tlp){
	bool borrado = false;
	ultimo = ultimo->anterior;
	ultimo->siguiente = NULL;
	borrado = true;
	return borrado;
}

bool TListaPoro::BorrarElementoIntermedio(const TListaPosicion &tlp){
	bool borrado = false;
	for(TListaPosicion actual = Primera(); !actual.EsVacia(); actual = actual.Siguiente()){
		if(actual == tlp){
			actual.pos->siguiente->anterior = actual.pos->anterior;
			actual.pos->anterior->siguiente = actual.pos->siguiente;
			borrado = true;
		}
	}
	return borrado;
}

bool TListaPoro::Borrar(TListaPosicion &tlp){
	bool borrado = false;
	if(Longitud() == 1){
		borrado = BorrarUnicoElemento();
	}
	else{
		if(tlp == Primera()){
			borrado = BorrarPrimerElemento(tlp);
		}
		else{
			if(tlp == Ultima()){
				borrado = BorrarUltimoElemento(tlp);
			}
			else{
				borrado = BorrarElementoIntermedio(tlp);
			}
		}
	}
	if(borrado){
		delete tlp.pos;
		tlp.pos = NULL;
	}
	return borrado;
}

TPoro TListaPoro::Obtener(const TListaPosicion &tlp) const{
	TPoro tp;
	bool encontrado = false;
	for(TListaPosicion actual = Primera(); !actual.EsVacia() && !encontrado; actual = actual.Siguiente()){
		if(actual == tlp){
			tp = tlp.pos->e;
			encontrado = true;
		}
	}
	return tp;
}
bool TListaPoro::Buscar(const TPoro &tp) const{
	bool esta = false;
	for(TListaPosicion actual = Primera(); !actual.EsVacia() && !esta; actual = actual.Siguiente()){
		if(actual.pos->e == tp){
			esta = true;
		}
	}
	return esta;
}
int TListaPoro::Longitud() const{
	int longitud = 0;
	for(TListaPosicion actual = Primera(); !actual.EsVacia(); actual = actual.Siguiente()){
		longitud++;
	}
	return longitud;
}

TListaPosicion TListaPoro::Primera() const{
	TListaPosicion aux;
	aux.pos = primero;
	return aux;
}

TListaPosicion TListaPoro::Ultima() const{
	TListaPosicion aux;
	aux.pos = ultimo;
	return aux;
}

TListaPoro TListaPoro::ExtraerRango(int n1, int n2){
	TListaPoro listaRango;
	TListaPosicion actual = Primera();
	TListaPosicion aux;
	int contador = 1;
	int longitud = Longitud();
	if(n1 <= n2){
		if(n1 <= 0){
			n1 = 1;
		}
		if(n2 > longitud){
			n2 = longitud;
		}
		while(!actual.EsVacia()){
			if(n1 <= contador && n2 >= contador){
				listaRango.Insertar(Obtener(actual));
				aux = actual;
				actual = actual.Siguiente();
				Borrar(aux);
			}
			else{
				actual = actual.Siguiente();
			}
			contador++;
		}
	}
	return listaRango;
}

ostream &operator<<(ostream &os, const TListaPoro &tlp){
	os << "(";
	for(TListaPosicion actual = tlp.Primera(); !actual.EsVacia(); actual = actual.Siguiente()){ 
		os << tlp.Obtener(actual);
		if(!(actual == tlp.Ultima())){
			os << " ";
		}
	}
	os << ")";
	return os;
}
