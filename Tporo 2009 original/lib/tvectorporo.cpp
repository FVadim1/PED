#include "tvectorporo.h"

TVectorPoro::TVectorPoro(){
	dimension = 0;
	datos = NULL;
}
TVectorPoro::TVectorPoro(int vd){
	if(vd > 0){
		dimension = vd;
		datos = new TPoro[dimension];
	}
	else{
		dimension = 0;
		datos = NULL;
	}
}
TVectorPoro::TVectorPoro(const TVectorPoro &tvp){
	if(tvp.dimension != 0){
		dimension = tvp.dimension;
		datos = new TPoro[tvp.dimension];
		for(int i = 0; i < tvp.dimension; i++){
			datos[i] = tvp.datos[i];
		}
	}
	else{
		dimension = 0;
		datos = NULL;
	}
}
TVectorPoro::~TVectorPoro(){
	dimension = 0;
	if(this->datos != NULL){
		delete [] datos;
	}
	datos = NULL;
}
TVectorPoro & TVectorPoro::operator=(const TVectorPoro &tvp) {
	if(this != &tvp){
		(*this).~TVectorPoro();
		this->dimension = tvp.dimension;
		this->datos = new TPoro[tvp.dimension];
		for(int i = 0; i < tvp.dimension; i++){
			datos[i] = tvp.datos[i];
		}
	}
	return *this;
}
bool TVectorPoro::operator==(const TVectorPoro &tvp) const{
	bool iguales;
	if(this->dimension == tvp.dimension){
		iguales = true;
		for(int i = 0; i < dimension && iguales; i++){
			if(this->datos[i] != tvp.datos[i]){
				iguales = false;
			}
		}
	}
	else{
		iguales = false;
	}
	return iguales;
}
bool TVectorPoro::operator!=(const TVectorPoro &tvp) const{
	return !(*this == tvp);
}
TPoro & TVectorPoro::operator[](int pos){
	if(pos >= 1 && pos <= dimension){
		return datos[pos - 1];
	}
	else{
		return error;
	}
}
TPoro TVectorPoro::operator[](int pos) const{
	if(pos >= 1 && pos <= dimension){
		return datos[pos - 1];
	}
	else{
		return error;
	}
}
int TVectorPoro::Longitud() const{
	return dimension;
}
int TVectorPoro::Cantidad() const{
	int vacias = 0;
	for(int i = 0; i < dimension; i++){
		if(!datos[i].EsVacio()){
			vacias++;
		}
	}
	return vacias;
}
bool TVectorPoro::Redimensionar(int nuevoTam){
	TPoro *aux = NULL;
	bool redimensionado = false;
	if(nuevoTam <= 0 || nuevoTam == Longitud()){
		redimensionado = false;
	}
	else{
		if(nuevoTam > 0 && nuevoTam > Longitud()){
			aux = new TPoro[nuevoTam];
			for(int i = 0; i < nuevoTam; i++){
				if(i < dimension){
					aux[i] = datos[i];
				}
				else{
					aux[i] = TPoro();
				}
			}
			if(datos != NULL){
				delete [] datos;
				datos = NULL;
			}
			dimension = nuevoTam;
			datos = aux;
			redimensionado = true;
		}
		else{
			if(nuevoTam > 0 && nuevoTam < Longitud()){
				aux = new TPoro[nuevoTam];
				for(int i = 0; i < nuevoTam; i++){
					aux[i] = datos[i];
				}
				if(datos != NULL){
					delete [] datos;
					datos = NULL;
				}
				dimension = nuevoTam;
				datos = aux;
				redimensionado = true;
			}
		}
	}
	return redimensionado;
}
ostream &operator<<(ostream &os, const TVectorPoro &tvp){
	os << "[";
	for(int i = 0; i < tvp.dimension; i++){
		os << i+1 << " " << tvp.datos[i];
		if(i < tvp.dimension - 1){
			os << " ";
		}
	}
	os << "]";
	return os;
}
/*
// FEBRERO 2008
int* TVectorPoro::Funcion2(const TListaPoro &tlp) const{
	int *v = NULL;
	int c, pos, encontrado;
	TListaPosicion p;
	if(datos != NULL){
		v = new int [dimension];
		for(int i = 0; i < dimension; i++){
			v[i] = -1;
		}
		if(tlp.EsVacia()){
			for(int i = 0; i < dimension; i++){
				// comprobamos si esta repetido en el vector
				for(int j = 0; j < dimension; j++){
					if(datos[i] == datos[j]){
						c++;
					}
				}
				if(c == 1){
					// NO ESTA REPETIDO 
					v[i] = 0;
				}
				else{
					// ESTA REPETIDISIMO
					// RECORREMOS LA LISTA
					pos = 1;
					p = tlp.Primera();
					encontrado = false;	
					while(!p.EsVacia() && !encontrado){
						if(datos[i] == tlp.Obtener(p)){
							encontrado = pos;
						}
						else{
							pos++;
							p = p.Siguiente();
						}
					}
					v[i] = encontrado;
				}
			}
		}
	}
	return v;
}
*/