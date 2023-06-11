#include "tvectorcom.h"


TVectorCom::TVectorCom(){
	c = NULL;
	tamano = 0;
}

TVectorCom::TVectorCom(int tam){
	if(tam > 0){
		c = new TComplejo[tam];
		tamano = tam;
	}
	else{
		tamano = 0;
		c = NULL;
	}
}

TVectorCom::TVectorCom(const TVectorCom &aux){
	if(aux.tamano != 0 && aux.c != NULL){
		c = new TComplejo [aux.tamano];
		tamano = aux.tamano;
		for(int i = 0; i < aux.tamano; i++)
			c[i] = aux.c[i];
	}
	else{
		c = NULL;
		tamano = 0;
	}
}

TVectorCom::~TVectorCom(){
	if(c != NULL)
		delete [] c;
	c = NULL;
	tamano = 0;
}

TVectorCom &TVectorCom::operator=(const TVectorCom &aux){
	if(this != &aux){
		this->~TVectorCom();
		if(aux.tamano != 0){
			c = new TComplejo [aux.tamano];
			tamano = aux.tamano;
			for(int i = 0; i < tamano; i++)
				c[i] = aux.c[i];	
		}
	}
	return *this;
}

bool TVectorCom::operator==(const TVectorCom &aux) const {
	bool iguales = false;

	if(this->tamano == aux.tamano){
		iguales = true;
		for(int i = 0; i < tamano; i++)
			if(!(aux.c[i] == c[i]))
				iguales = false;
	}

	return iguales;
}

bool TVectorCom::operator!=(const TVectorCom &aux)const{
	return !(aux == *this);
}

TComplejo &TVectorCom::operator[](int pos){
	if(pos >= 1 && pos <= tamano && c != NULL)	
		return c[pos - 1];
	else
		return error;
}


TComplejo TVectorCom::operator[](int pos) const{
	if(pos <= tamano && c != NULL && pos >= 1)
		return c[pos - 1];
	else
		return error;
}

int TVectorCom::Tamano() const{
	return tamano;	
}

int TVectorCom::Cantidad() const{
	int cont = 0;
	
	for(int i = 0; i < tamano; i++)
		if(c[i].Re() != 0 || c[i].Im() != 0)
			cont++;

	return cont;
}

bool TVectorCom::ExisteCom(const TComplejo &c) const
{
	bool existe = false;

	for (int i=0; i < tamano && !existe; i++)
		if(this->c[i] == c)
			existe = true;
	
	return existe;
}

bool TVectorCom::Redimensionar(int tam){
	bool exito = false;
	TComplejo *aux = NULL;
	
	if(tamano != tam && tam > 0){
		exito = true;
		aux = new TComplejo [tam];
		for(int i = 0; i < tam && i < tamano; i++){
			aux[i] = c[i];
		}
		if(c != NULL){
			delete []c;
			c = NULL;
		}
		c = aux;
		tamano = tam;
	} 
	return exito;
}


void TVectorCom::MostrarComplejos(double re) const{
	bool primero = true;
	
	cout << "[";
	for(int i = 0; i < tamano; i++){
		if(c[i].Re() >= re){
			if(primero){
				cout << c[i];
				primero = false;
			}
			else{
				cout << ", " << c[i];
			}
		}
	}
	cout << "]";
}

int TVectorCom::Ocupadas() const{
	int numOcupadas = 0, i;
	
	for(i = 0; i < tamano; i++){
			if(c[i].Re() != 0 || c[i].Im() != 0){
				numOcupadas++;
			}
	}
	return numOcupadas;
}

ostream &operator << (ostream &o, const TVectorCom &t)
{
	o<<"[";
	if(t.c && t.tamano>0)
	{
		for (int i=0;i<t.tamano;i++)
		{
			o << "(" << i + 1 << ") " << t.c[i];
			if(i < t.tamano-1)
				o << ", ";
		}
	}
	o<<"]";

	return o;
}


