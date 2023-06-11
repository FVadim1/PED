#include "tavlporo.h"
// ----------- TNodoAVL -----------
TNodoAVL::TNodoAVL(){
    fe = 0;
}
TNodoAVL::TNodoAVL(const TNodoAVL &tnavl){
    iz = tnavl.iz;
    de = tnavl.de;
    item = tnavl.item;
    fe = tnavl.fe;
}
TNodoAVL::~TNodoAVL(){
    fe = 0;
}
TNodoAVL & TNodoAVL::operator=(const TNodoAVL &tnavl){
    iz = tnavl.iz;
    de = tnavl.de;
    item = tnavl.item;
    fe = tnavl.fe;
    return *this;
}

// --------- TAVLPoro -------------
TAVLPoro::TAVLPoro(){
    raiz = NULL;
}
TAVLPoro::TAVLPoro(const TAVLPoro &tavlp){
    raiz = NULL;
    if(tavlp.raiz){
        raiz = new TNodoAVL(*tavlp.raiz);
    }
}
TAVLPoro::~TAVLPoro(){
    if(raiz != NULL){
        delete raiz;
        raiz = NULL;
    }
}
TAVLPoro & TAVLPoro::operator=(const TAVLPoro &tavlp){
    if(this != &tavlp){
        this->~TAVLPoro();
        if(tavlp.raiz){
            raiz = new TNodoAVL;
            *raiz = *tavlp.raiz;
        }
    }
    return *this;
}

bool TAVLPoro::operator==(const TAVLPoro &tavlp){
    bool iguales = false;
    TVectorPoro implicito = this->Inorden();
    TVectorPoro referencia = tavlp.Inorden();
    if(implicito == referencia){ 
        iguales = true;
    }
    return iguales;
}        

bool TAVLPoro::operator!=(const TAVLPoro &tavlp){
    return !(*this == tavlp);
}

bool TAVLPoro::EsVacio() const{
    return raiz == NULL;
}

void TAVLPoro::DD(){
    TNodoAVL *tnavl;
	
	tnavl = raiz;
	raiz = tnavl->de.raiz;
	tnavl->de.raiz = raiz->iz.raiz;
	raiz->iz.raiz = tnavl;
	if(raiz->fe != 0){
		raiz->fe = 0;
		raiz->iz.raiz->fe = 0;
	}
	else{
		raiz->fe = -1;
		raiz->iz.raiz->fe = 1;
	}
}

void TAVLPoro::II(){
    TNodoAVL *tnavl;
	
	tnavl = raiz;
	raiz = tnavl->iz.raiz;
	tnavl->iz.raiz = raiz->de.raiz;
	raiz->de.raiz = tnavl;
	if(raiz->fe != 0){
		raiz->fe = 0;
		raiz->de.raiz->fe = 0;
	}
	else{
		raiz->fe = 1;
		raiz->de.raiz->fe = -1;
	}
}

void TAVLPoro::DI(){
    TNodoAVL *tnavl, *tnavlIzq, *tnavlDe;
	
	tnavl = raiz;
	raiz = raiz->de.raiz->iz.raiz;
	tnavlIzq = raiz->iz.raiz;
	tnavlDe = raiz->de.raiz;
	raiz->de.raiz = tnavl->de.raiz;
	raiz->iz.raiz = tnavl;
	tnavl->de.raiz = tnavl;
	raiz->de.raiz->iz.raiz = tnavlDe;
	if(raiz->fe != 0){
		if(raiz->fe == -1){
			raiz->fe = 0;
			raiz->iz.raiz->fe = 0;
			raiz->de.raiz->fe = 1;	
		}
		else{
			raiz->fe = 0;
			raiz->iz.raiz->fe = -1;
			raiz->de.raiz->fe = 0;	
		}
	}
	else{
		raiz->fe = raiz->iz.raiz->fe = raiz->de.raiz->fe = 0;
	}	
}

void TAVLPoro::ID(){
    TNodoAVL *tnavl, *tnavlIzq, *tnavlDe;
	
	tnavl = raiz;
	raiz = raiz->iz.raiz->de.raiz;
	tnavlIzq = raiz->iz.raiz;
	tnavlDe = raiz->de.raiz;
	raiz->iz.raiz = tnavl->iz.raiz;
	raiz->de.raiz = tnavl;
	tnavl->iz.raiz = tnavlDe;
	raiz->iz.raiz->de.raiz = tnavlIzq;
	if(raiz->fe != 0){
		if(raiz->fe == -1)
		{
			raiz->fe = 0;
			raiz->iz.raiz->fe = 0;
			raiz->de.raiz->fe = 1;	
		}
		else
		{
			raiz->fe = 0;
			raiz->iz.raiz->fe = -1;	
			raiz->de.raiz->fe = 0;	
		}
	}
	else{
		raiz->fe = raiz->iz.raiz->fe = raiz->de.raiz->fe = 0;
	}
}

bool TAVLPoro::MismoVolumen(const TPoro &tp) const{
    if(raiz == NULL){
        return false;
    }
    else{
        if(raiz->item.Volumen() == tp.Volumen()){
            return true;
        }
        else{
            if(raiz->item.Volumen() > tp.Volumen()){
                return raiz->iz.Buscar(tp);
            }
            else{
                return raiz->de.Buscar(tp);
            }
        }
    }
}

bool TAVLPoro::Insertar(const TPoro &tp){
    bool insertado;
    bool creceArbol;
	bool encontrado = Buscar(tp);
	bool mismoVolumen = MismoVolumen(tp); 
	if(!encontrado && !mismoVolumen){
		insertado = InsertarAux(tp, creceArbol);
	}
	else{
		insertado = false;
	}
    return insertado;
}

bool TAVLPoro::InsertarAux(const TPoro &tp, bool &creceArbol){
    bool creceArbIz, creceArbDe;
	bool insertado;

	creceArbIz = creceArbDe = false;	
	insertado = false;
	
	if(EsVacio()){
		raiz = new TNodoAVL;
		raiz->fe = 0;
		raiz->item = tp;
		creceArbol = true;
		insertado = true;
	}
	else{
		if(!(raiz->item == tp)){
			if(tp.Volumen() < raiz->item.Volumen()){
				insertado = raiz->iz.InsertarAux(tp, creceArbIz);
			}
			else{
				insertado = raiz->de.InsertarAux(tp, creceArbDe);
			}
			if(creceArbIz){
				raiz->fe--;
				switch(raiz->fe){
					case 0:
						creceArbol = false;
					break;
					case -2:
						creceArbol = false;
						switch(raiz->iz.raiz->fe){
							case -1:
								II();
							break;
							case +1:
								ID();
							break;						
						}
					break;
					case -1:
						creceArbol = true;
					break;
				}
			}
			else{
				if(creceArbDe){
					raiz->fe++;
					switch(raiz->fe){
						case 0:
							creceArbol = false;
						break;
						case 2:
							creceArbol = false;
							switch(raiz->de.raiz->fe)
							{
								case -1:
									DI();
								break;
								case +1:
									DD();
								break;
							}
						break;
						case 1:
							creceArbol = true;
						break;
					}
				}
			}
		}
	}
	return insertado;
}

bool TAVLPoro::Buscar(const TPoro &tp) const{
    if(raiz == NULL){
        return false;
    }
    else{
        if(raiz->item == tp){
            return true;
        }
        else{
            if(raiz->item.Volumen() > tp.Volumen()){
                return raiz->iz.Buscar(tp);
            }
            else{
                return raiz->de.Buscar(tp);
            }
        }
    }
}

TPoro TAVLPoro::ObtenerMayorIzquierda() const{ 
    TPoro poro;
    if(raiz != NULL){ 
        if(raiz->de.raiz == NULL){ // Le pasamos el derecha por que en el arbol izquieda sus mayores estan a la derecha
            poro = raiz->item;
        }
        else{
            poro = raiz->de.ObtenerMayorIzquierda();
        }
    }
    return poro;
}

bool TAVLPoro::Borrar(const TPoro &tp){
    bool decrece = false;
    bool borrado;
	borrado = BorrarAux(tp, decrece);
    return borrado;
}

bool TAVLPoro::BorrarAux(const TPoro &tp, bool &decreceArbol){
    bool borrado, decreceIz, decreceDe;
	TPoro mayorIz;
	TNodoAVL *tnavl, *tnavlRaiz;

	decreceArbol = false;
	decreceIz = decreceDe = false;
	if(!raiz){
		decreceArbol = borrado = false;
	}
	else{
		if(tp.Volumen() < raiz->item.Volumen()){
			borrado = raiz->iz.BorrarAux(tp, decreceIz);
		}
		else{
			if(tp.Volumen() > raiz->item.Volumen()){
				borrado = raiz->de.BorrarAux(tp, decreceDe);
			}
			else{
				if(raiz->item.Volumen() == tp.Volumen()){
					if(raiz->iz.EsVacio() && raiz->de.EsVacio()){
						delete raiz;
						raiz = NULL;
						decreceArbol = true;
						borrado = true;
					}
					else{
						if(raiz->iz.EsVacio() && !raiz->de.EsVacio()){
							tnavl = raiz;
							raiz = raiz->de.raiz;
							tnavl->iz.raiz = tnavl->de.raiz = NULL;
							delete tnavl;
							decreceArbol = true;
							borrado = true;
						}
						else{
							if(!raiz->iz.EsVacio() && raiz->de.EsVacio()){
								tnavl = raiz;
								raiz = raiz->iz.raiz;
								tnavl->iz.raiz = tnavl->de.raiz = NULL;
								delete tnavl;
								decreceArbol = true;
								borrado = true;
							}
							else{
								mayorIz = raiz->iz.ObtenerMayorIzquierda();
								tnavlRaiz = raiz;
								borrado = BorrarAux(mayorIz, decreceArbol);
								tnavlRaiz->item = mayorIz;
							}
						}
					}
				}
			}
		}
	}
	if(borrado){
		if(decreceIz){
			raiz->fe++;
			switch(raiz->fe){
				case 0:
					decreceArbol = true;
					break;
				case 1:
					decreceArbol = false;	
					break;
				case 2:
					switch(raiz->de.raiz->fe){
						case -1:
							DI();
							decreceArbol = true;	
						break;
						case 0:
							DD();
							decreceArbol = false;
						break;
						case 1:
							DD();
							decreceArbol = true;
						break;
					}
					break;
			}
		}
		else{
			if(decreceDe){
				raiz->fe--;
				switch(raiz->fe){
					case 0:
						decreceArbol = true;
						break;
					case -1:
						decreceArbol = false;
						break;
					case -2:
						switch(raiz->iz.raiz->fe){
							case -1:
								II();
								decreceArbol = true;
								break;
							case 0:
								II();
								decreceArbol = false;
								break;
							case 1:
								ID();
								decreceArbol = true;
								break;
						}
						break;
				}
			}
		}
	}
	return borrado;
}

int TAVLPoro::Altura() const{
    int altura;
    if(raiz == NULL){
        return 0;
    }
    else{
        if(raiz->iz.Altura() < raiz->de.Altura()){
            altura = 1 + raiz->de.Altura();
        }
        else{
            altura = 1 + raiz->iz.Altura();
        }
    }
    return altura;
}

TPoro TAVLPoro::Raiz() const{
    TPoro aux;
    if(!EsVacio()){
        aux = raiz->item; 
    }
    return aux;
}

int TAVLPoro::Nodos() const{
    int cantidadNodos;
    if(raiz == NULL){
        return 0;
    }
    else{
        cantidadNodos = 1 + raiz->de.Nodos() + raiz->iz.Nodos();
    }
    return cantidadNodos;
}

int TAVLPoro::NodosHoja() const{ 
    int hojas;
    if(raiz == NULL){
        return 0;
    }
    else{
        if(raiz->iz.EsVacio() && raiz->de.EsVacio()){
            return 1;
        }
        else{
            hojas = raiz->iz.NodosHoja() + raiz->de.NodosHoja();    
        }
    }
    return hojas;
}

TVectorPoro TAVLPoro::Inorden() const{
    TVectorPoro vectorInorden(Nodos());
    int pos = 1;
    InordenAux(vectorInorden, pos);
    return vectorInorden;
}

void TAVLPoro::InordenAux(TVectorPoro &tvp, int &posicion) const{
    if(raiz != NULL){
        raiz->iz.InordenAux(tvp, posicion);
        tvp[posicion] = raiz->item;
        posicion++;
        raiz->de.InordenAux(tvp, posicion);
    }
}

TVectorPoro TAVLPoro::Preorden() const{
    TVectorPoro vectorPreorden(Nodos());
    int pos = 1;
    PreordenAux(vectorPreorden, pos);
    return vectorPreorden;
}

void TAVLPoro::PreordenAux(TVectorPoro &tvp, int &posicion) const{
    if(raiz != NULL){
        tvp[posicion] = raiz->item;
        posicion++;
        raiz->iz.PreordenAux(tvp, posicion);
        raiz->de.PreordenAux(tvp, posicion);
    }
}

TVectorPoro TAVLPoro::Postorden() const{
    TVectorPoro vectorPostorden(Nodos());
    int pos = 1;
    PostordenAux(vectorPostorden, pos);
    return vectorPostorden;
}

void TAVLPoro::PostordenAux(TVectorPoro &tvp, int &posicion) const{
    if(raiz != NULL){
        raiz->iz.PostordenAux(tvp, posicion);
        raiz->de.PostordenAux(tvp, posicion);
        tvp[posicion] = raiz->item;
        posicion++;
    }
}
/*
// ******* SOLOR PARA PRUEBAS *********
TVectorPoro TAVLPoro::Niveles() const{ // hay que usar queue (cola)
    TVectorPoro recorridoNiveles (Nodos()); 
    queue<TNodoAVL *> cola;
    TNodoAVL *aux;
    int pos = 1;
    cola.push(raiz);
    while(cola.empty() == false){
        aux = cola.front();
        cola.pop();
        if(aux != NULL){
            recorridoNiveles[pos] = aux->item;
            pos++;
            cola.push(aux->iz.raiz);
            cola.push(aux->de.raiz);
        }
    }
    return recorridoNiveles;
}
*/

ostream & operator<<(ostream &os, const TAVLPoro &tavlp){
    TVectorPoro aux = tavlp.Inorden();
    os << aux << endl;
}