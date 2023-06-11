#include "tvectorcom.h"

// Constructor por defecto
TVectorCom::TVectorCom(){
	c=NULL;
	tamano=0;
}

// Constructor a partir de un tamaño
TVectorCom::TVectorCom(int t){

	if(t > 0){
		c = new TComplejo[t];
		tamano=t;
	}
	else{
		c=NULL;
		tamano=0;
	}
}

// Constructor de copia
TVectorCom::TVectorCom(const TVectorCom &v){

	if( (v.tamano != 0) && (v.c!=NULL) ){

		c = new TComplejo[v.tamano];
		tamano = v.tamano;
		for(int i = 0; i < v.tamano; i++){ c[i] = v.c[i];}
	}
	else{
		c=NULL;
		tamano=0;
	}
}

// Destructor
TVectorCom::~TVectorCom(){
	
	if(c != NULL){ delete [] c;}
	c = NULL;
	tamano = 0;
}

// Sobrecarga del operador asignación
TVectorCom &TVectorCom::operator=(const TVectorCom &v){
	
	if(this != &v){

		this->~TVectorCom();

		if(v.tamano != 0){

			c = new TComplejo[v.tamano];
			tamano=v.tamano;
			for(int i = 0; i < tamano; i++){ c[i] = v.c[i];}
		}
	}
	
	return *this;
}
	
// Sobrecarga del operador igualdad
bool TVectorCom::operator==(const TVectorCom &v) const{
	
	bool vecIguales = true;
	
	if(this->tamano == v.tamano){
		for(int i = 0; i < tamano; i++){
			if(c[i] != v.c[i]){ vecIguales=false; }
		}
	}else{vecIguales=false;}

	return vecIguales;
}

// Sobrecarga del operador desigualdad
bool TVectorCom::operator!=(const TVectorCom &v) const{ 
	
	bool notEqual=false;
	if(v!=*this){ notEqual=true;}
	return notEqual;
}

// Sobrecarga del operador corchete (parte IZQUIERDA)
TComplejo &TVectorCom::operator[](int posicion){

	if(posicion >= 1 && posicion <= tamano && c != NULL) { return c[posicion - 1];}
	else{ return error;}
}

// Sobrecarga del operador corchete (parte DERECHA)
TComplejo TVectorCom::operator[](int posicion) const{
	
	if(posicion >= 1 && posicion <= tamano && c != NULL) { return c[posicion - 1];}
	else{ return error;}
}

// Tamaño del vector (posiciones TOTALES)
int TVectorCom::Tamano() const{	return tamano;}

// Cantidad de posiciones OCUPADAS (TComplejo NO VACIO) en el vector
int TVectorCom::Ocupadas() const{
	
	int cantidadOcupadas=0;
	
	for(int i = 0; i < tamano; i++){
		if(c[i].Re() != 0 || c[i].Im() != 0){ cantidadOcupadas++;}
	}
	return cantidadOcupadas;
	
}

// Devuelve TRUE si existe el TComplejo en el vector
bool TVectorCom::ExisteCom(const TComplejo &c) const{
	bool existeEnVector = false;

	for (int i=0; i < tamano; i++){
		if(this->c[i] == c){ existeEnVector = true;}
	}
	
	return existeEnVector;
}

// Mostrar por pantalla los elementos TComplejo del vector con PARTE REAL O POSTERIOR al argumento
void TVectorCom::MostrarComplejos(double a) const{

	bool esPrimero = true;

	cout << "[";

	for(int i = 0; i < tamano; i++){

		if(c[i].Re() >= a){

			if(esPrimero==true){ cout << c[i]; esPrimero = false;}
			else{ cout << ", " << c[i];}
		}
	}

	cout << "]";
}

// REDIMENSIONAR el vector de TComplejo	
bool TVectorCom::Redimensionar(int nuevoTamano){

	bool redimensionado = false;
	TComplejo *cnuevo = NULL;

	if(nuevoTamano>0){
		if(tamano!=nuevoTamano){

				cnuevo = new TComplejo[nuevoTamano];
				for(int i = 0; i < nuevoTamano && i < tamano; i++){ cnuevo[i] = c[i];}

				if(c!=NULL){ delete [] c; c=NULL;}

				c = cnuevo;
				tamano = nuevoTamano;

				redimensionado = true;
		}
	}
	
	return redimensionado;
}
		
// Sobrecarga del operador salida
ostream &operator<<(ostream &os,const TVectorCom &v){

	os<<"[";

	if(v.c && v.tamano>0){

		for (int i=0;i<v.tamano;i++){

			os << "(" << i + 1 << ") " << v.c[i];
			if(i < v.tamano-1){ os << ", ";}
		}
	}

	os<<"]";

	return os;
}
