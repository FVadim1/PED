#include <queue>
#include <iostream>
using namespace std;

#include "tabbcom.h"
#include "tcomplejo.h"
#include "tvectorcom.h"

///////////////////////////////////////////////////
//////////////////////TABBCom//////////////////////
///////////////////////////////////////////////////

TABBCom::TABBCom(){nodo=NULL;}//Constructor por defecto

TABBCom::TABBCom(const TABBCom &t){ //Constructor de copia
	if(t.nodo != NULL){ nodo = new TNodoABB(*t.nodo);}
	else{nodo=NULL;}
}

TABBCom::~TABBCom(){//Destructor
	if(nodo != NULL){ delete nodo;nodo = NULL;}
}

TABBCom &TABBCom::operator=(const TABBCom &elementoDerecho){//Sobrecarga del operador asignación

	if(this != &elementoDerecho){
		nodo = NULL;
		if(elementoDerecho.nodo){ nodo = new TNodoABB(*elementoDerecho.nodo);}
	}

	return *this;
}

bool TABBCom::operator==(const TABBCom &elementoDerecho) const{//Sobrecarga del operador igualdad
	bool iguales=false;
	if(Inorden() == elementoDerecho.Inorden()){iguales=true;}
	return iguales;
}

bool TABBCom::EsVacio() const{//Devuelve TRUE si el árbol está vacío, FALSE en caso contrario
	
	bool esVacio=false;
	if(nodo==NULL){esVacio=true;}
	return esVacio;
}

bool TABBCom::Insertar(const TComplejo &k){//Inserta el elemento en el árbol
	
	bool insertado,mayormod=false,igualmod=false,mayoreal=false,igualreal=false,mayorimaginaria=false;

	if(nodo==NULL){ nodo = new TNodoABB(); nodo->item = k; insertado=true;}
	else{
		if(k != nodo->item){
			
			if(k.Mod() > nodo->item.Mod()){mayormod=true;}
			if(k.Mod() == nodo->item.Mod()){igualmod=true;}
			if(k.Re() > nodo->item.Re()){mayoreal=true;}
			if(k.Re() == nodo->item.Re()){igualreal=true;}
			if(k.Im() > nodo->item.Im()){mayorimaginaria=true;}
			
			if(mayormod || mayoreal && igualmod || igualmod && igualreal || mayorimaginaria){  insertado = nodo->de.Insertar(k);}				
			else{insertado = nodo->iz.Insertar(k);}
			
		}else{insertado=false;}
	}

	return insertado;
}

bool TABBCom::Borrar(const TComplejo &c){//Borra el elemento en el árbol

	bool borrado,modigual=false,modmayor=false,realmayor=false,realigual=false,imayor=false;
	TComplejo cizqmayor;
	TNodoABB *n;

	if(nodo != NULL){
		if(c != nodo->item){
			if(c.Mod() > nodo->item.Mod()){ modmayor=true;}
			if(c.Mod() == nodo->item.Mod()){ modigual=true;}
			if(c.Re() > nodo->item.Re()){ realmayor=true;}
			if(c.Re() == nodo->item.Re()){ realigual=true;}
			if(c.Im() > nodo->item.Im()){ imayor=true;}
			
			if(modmayor || modigual && realmayor || modigual && realigual && imayor){ borrado = nodo->de.Borrar(c);}	
			else{borrado = nodo->iz.Borrar(c);}
		}
		else{
			borrado=true;
			if(nodo->iz.EsVacio() && nodo->de.EsVacio()){ delete nodo; nodo=NULL;}
			else{			
				if(nodo->de.EsVacio()){cizqmayor = nodo->iz.izqMayor(); nodo->iz.Borrar(cizqmayor); nodo->item = cizqmayor;}
				else{
					if(nodo->iz.EsVacio()){ n=nodo; nodo = nodo->de.nodo; n->de.nodo = NULL; delete n; n=NULL;}
					else{ n=nodo; nodo = nodo->iz.nodo; n->iz.nodo = NULL; delete n; n=NULL;}
				}	
			}
		}
	}else{borrado=false;}
	
	return borrado;
}

bool TABBCom::Buscar(const TComplejo &c) const{//Devuelve TRUE si el elemento está en el árbol, FALSE en caso contrario

	bool found;
	
	if(nodo!=NULL){
		
		if(c == nodo->item){found = true;}
		else{found = nodo->iz.Buscar(c) || nodo->de.Buscar(c);}
		
	}else{found=false;}
	
	return found;
}

TComplejo TABBCom::Raiz() const{//Devuelve el elemento en la raíz del árbol
	TComplejo c;
	if(nodo != NULL){c = nodo->item;}
	return c;
}

int TABBCom::Altura() const{//Devuelve la altura del árbol (la altura de un árbol vacío es 0)
	
	int altura=0, izqAltura, derAltura;

	if(nodo != NULL){//si arbol no es vacio
		izqAltura = nodo->iz.Altura();
		derAltura = nodo->de.Altura();

		if(derAltura > izqAltura){altura = derAltura+1;}	
		else{altura = izqAltura+1;}
	}
	return altura;
}

int TABBCom::Nodos() const{//Devuelve el número de nodos del árbol (un árbol vacío posee 0 nodos)
	int nodos=0;
	if(nodo != NULL){nodos = nodo->iz.Nodos() + nodo->de.Nodos() + 1;}
	return nodos;
}

int TABBCom::NodosHoja() const{//Devuelve el número de nodos hoja en el árbol (la raíz puede ser nodo hoja)
	
	int n=0,iz=0,de=0;
	if(nodo != NULL){
		if(nodo->iz.EsVacio() && nodo->de.EsVacio()){ n = 1;}
		else{
			iz= nodo->iz.NodosHoja();
			de= nodo->de.NodosHoja();
			n = iz + de;
		}
	}
	return n;
}

TVectorCom TABBCom::Inorden() const{//Devuelve el recorrido en inorden
	
	int pos=1;
	TVectorCom v(Nodos());
	InordenAux(v,pos);
	return v;
}

void TABBCom::InordenAux(TVectorCom &v, int &pos) const{// AUXILIAR : Devuelve el recorrido en inorden

	if(nodo != NULL){
		nodo->iz.InordenAux(v,pos);
		v[pos] = nodo->item;
		pos++;
		nodo->de.InordenAux(v,pos);
	}
}

TVectorCom TABBCom::Preorden() const{//Devuelve el recorrido en preorden
	
	int pos=1;
	TVectorCom v(Nodos());
	PreordenAux(v,pos);
	return v;
}

void TABBCom::PreordenAux(TVectorCom &v, int &pos) const{// AUXILIAR : Devuelve el recorrido en preorden
	
	if(nodo != NULL){
		v[pos] = nodo->item;
		pos++;
		nodo->iz.PreordenAux(v,pos);
		nodo->de.PreordenAux(v,pos);
	}
}

TVectorCom TABBCom::Postorden() const{//Devuelve el recorrido en postorden
	
	int pos=1;
	TVectorCom v(Nodos());
	PostordenAux(v,pos);
	return v;
}

void TABBCom::PostordenAux(TVectorCom &v, int &pos) const{// AUXILIAR : Devuelve el recorrido en postorden
	if(nodo != NULL){
		nodo->iz.PostordenAux(v, pos);
		nodo->de.PostordenAux(v, pos);
		v[pos] = nodo->item;
		pos++;
	}
}

TVectorCom TABBCom::Niveles() const{//Devuelve el recorrido en niveles
	
	TNodoABB *n;
	int pos=1;
	TVectorCom vec(Nodos());
	queue<TNodoABB *> cola; cola.push(nodo);

	while(cola.empty()==false){
		n = cola.front();
		cola.pop();		
		if(n != NULL){ vec[pos] = n->item; pos++; cola.push(n->iz.nodo); cola.push(n->de.nodo);}	
	}
	return vec;
}

ostream &operator<<(ostream &o, const TABBCom &a){//Sobrecarga del operador salida
	o << a.Niveles();
	return o;
}

TComplejo TABBCom::izqMayor() const{
	
	TComplejo c;
	
	if(nodo->de.EsVacio()){c = nodo->item;}
	else{c = nodo->de.izqMayor();}
	
	return c;
}

///////////////////////////////////////////////////
//////////////////////TNodoABB//////////////////////
///////////////////////////////////////////////////

TNodoABB::TNodoABB(){}// Constructor por defecto
TNodoABB::TNodoABB(const TNodoABB &n):item(n.item), iz(n.iz), de(n.de){}// Constructor de copia
TNodoABB::~TNodoABB(){}// Destructor
TNodoABB::TNodoABB(const TComplejo &c){item=c;}// Sobrecarga del operador asignación
