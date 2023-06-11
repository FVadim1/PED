#include "tabbporo.h"
// ------------------------ TNODOABB -------------------------
TNodoABB::TNodoABB(){}
TNodoABB::TNodoABB(const TNodoABB &tnabb){
    item = tnabb.item;
    iz = tnabb.iz;
    de = tnabb.de;
}
TNodoABB::~TNodoABB(){}
TNodoABB & TNodoABB::operator=(const TNodoABB &tnabb){
    if(this != &tnabb){
        (*this).~TNodoABB();
        item = tnabb.item;
        iz = tnabb.iz;
        de = tnabb.de;
    }
    return *this;
}
// --------------------- TABBPORO ----------------------
TABBPoro::TABBPoro(){
    nodo = NULL;
}

TABBPoro::TABBPoro(const TABBPoro &tabbp){ // REVISAR IMPLEMENTACION
    nodo = NULL;
    if(tabbp.nodo){
        nodo = new TNodoABB(*tabbp.nodo);
    }
}

TABBPoro::~TABBPoro(){
    if(nodo != NULL){
        delete nodo;
        nodo = NULL;
    }
}

TABBPoro & TABBPoro::operator=(const TABBPoro &tabbp){
    if(this != &tabbp){
        this->~TABBPoro();
        if(tabbp.nodo){
            nodo = new TNodoABB;
            *nodo = *tabbp.nodo;
        }
    }
    return *this;
}
// ESTE OPERADOR SE PUEDE HACER IGUALANDO 2 RECORRIDOS YA SEA EL INORDER POSTORDEN PREORDEN O NIVELES
bool TABBPoro::operator==(const TABBPoro &tabbp) const{
    bool iguales = false;
    TVectorPoro implicito = this->Inorden();
    TVectorPoro referencia = tabbp.Inorden();
    if(implicito == referencia){ 
        iguales = true;
    }
    return iguales;
}

bool TABBPoro::EsVacio() const{
    return nodo == NULL;
}

bool TABBPoro::MismoVolumen(const TPoro &tp) const{
    if(nodo == NULL){
        return false;
    }
    else{
        if(nodo->item.Volumen() == tp.Volumen()){
            return true;
        }
        else{
            if(nodo->item.Volumen() > tp.Volumen()){
                return nodo->iz.Buscar(tp);
            }
            else{
                return nodo->de.Buscar(tp);
            }
        }
    }
}

bool TABBPoro::Insertar(const TPoro &tp){
    bool insertado = false;
    bool mismoVol;
    bool encontrado;
    TNodoABB *nodoNuevo = new TNodoABB();
    encontrado = Buscar(tp);
    mismoVol = MismoVolumen(tp);
    if(!encontrado && !mismoVol){
        insertado = true;
        if(nodo == NULL){ // si el arbol (nodo) esta vacio se inserta el nuevoNodo en el nodo
            nodoNuevo->item = tp;
            nodo = nodoNuevo;
            insertado = true;
        }
        else{
            if(tp.Volumen() < nodo->item.Volumen()){ // si el valor nuevo es menor que el del nodo actual seguimos buscando en la iz
                nodo->iz.Insertar(tp);
            }
            else{
                nodo->de.Insertar(tp); // sino en la derecha
            }
        }
    }  
    else{
        insertado = false;
    }
    return insertado;
}
/*
    POSIBLES CASO DE BORRADO
        - Borrar nodo hoja
        - Borrar nodo con un subárbol hijo
        - Borrar nodo con 2 subarboles hijos
*/

TPoro TABBPoro::ObtenerMayorIzquierda() const{ 
    TPoro poro;
    if(nodo != NULL){ 
        if(nodo->de.nodo == NULL){ // Le pasamos el derecha por que en el arbol izquieda sus mayores estan a la derecha
            poro = nodo->item;
        }
        else{
            poro = nodo->de.ObtenerMayorIzquierda();
        }
    }
    return poro;
}

bool TABBPoro::Borrar(const TPoro &tp){ // REVISAR
    bool borrado;
    bool encontrado; 
    TNodoABB *padre = new TNodoABB(); // PADRE
    encontrado = Buscar(tp);
    if(encontrado){ // EL ELEMENTO EXISTE EN ARBOL
        if(Raiz() == tp){ // hemos encontrado el elemento
            if(nodo->iz.EsVacio() && nodo->de.EsVacio()){ // ES HOJA
                nodo = NULL;
                delete nodo;
                borrado = true;
            }
            else{
                if(!nodo->iz.EsVacio() && !nodo->de.EsVacio()){ // TIENE LOS 2 HIJOS // REVISAR
                    // HAY QUE BUSCAR EL MAYOR DE LA IZQUIERDA
                    TPoro mayorIzquierda = nodo->iz.ObtenerMayorIzquierda();
                    nodo->item = mayorIzquierda;
                    borrado = nodo->iz.Borrar(mayorIzquierda);
                }
                else{
                    if(!nodo->iz.EsVacio() || !nodo->de.EsVacio()){ // TIENE SOLO UN HIJO
                        padre = nodo; 
                        // comprobamos cual es el que no esta vacio
                        if(!nodo->iz.EsVacio()){
                            nodo = nodo->iz.nodo;
                            padre->iz.nodo = NULL;
                        }
                        else{
                            if(!nodo->de.EsVacio()){
                                nodo = nodo->de.nodo;
                                padre->de.nodo = NULL;
                            }
                        }
                        delete padre;
                        borrado = true;
                    }
                    else{
                        borrado = false;
                    }
                }
            }
        }
        else{ // Buscamos el elemento
            if(tp.Volumen() < nodo->item.Volumen()){
                borrado = nodo->iz.Borrar(tp);
            }
            else{
                borrado = nodo->de.Borrar(tp);
            }
        }
    }
    else{ // EL ELEMENTO NO EXISTE EN ARBOL
        borrado = false;
    }
    return borrado;
}

bool TABBPoro::Buscar(const TPoro &tp) const{
    if(nodo == NULL){
        return false;
    }
    else{
        if(nodo->item == tp){
            return true;
        }
        else{
            if(nodo->item.Volumen() > tp.Volumen()){
                return nodo->iz.Buscar(tp);
            }
            else{
                return nodo->de.Buscar(tp);
            }
        }
    }
}

TPoro TABBPoro::Raiz() const{
    TPoro aux;
    if(!EsVacio()){
        aux = nodo->item; 
    }
    return aux;
}

int TABBPoro::Altura() const{
    int altura;
    if(nodo == NULL){
        return 0;
    }
    else{
        if(nodo->iz.Altura() < nodo->de.Altura()){
            altura = 1 + nodo->de.Altura();
        }
        else{
            altura = 1 + nodo->iz.Altura();
        }
    }
    return altura;
}

int TABBPoro::Nodos() const{
    int cantidadNodos;
    if(nodo == NULL){
        return 0;
    }
    else{
        cantidadNodos = 1 + nodo->de.Nodos() + nodo->iz.Nodos();
    }
    return cantidadNodos;
}

int TABBPoro::NodosHoja() const{ 
    int hojas;
    if(nodo == NULL){
        return 0;
    }
    else{
        if(nodo->iz.EsVacio() && nodo->de.EsVacio()){
            return 1;
        }
        else{
            hojas = nodo->iz.NodosHoja() + nodo->de.NodosHoja();    
        }
    }
    return hojas;
}

TVectorPoro TABBPoro::Inorden() const{
    TVectorPoro vectorInorden(Nodos());
    int pos = 1;
    InordenAux(vectorInorden, pos);
    return vectorInorden;
}

void TABBPoro::InordenAux(TVectorPoro &tvp, int &posicion) const{
    if(nodo != NULL){
        nodo->iz.InordenAux(tvp, posicion);
        tvp[posicion] = nodo->item;
        posicion++;
        nodo->de.InordenAux(tvp, posicion);
    }
}

TVectorPoro TABBPoro::Preorden() const{
    TVectorPoro vectorPreorden(Nodos());
    int pos = 1;
    PreordenAux(vectorPreorden, pos);
    return vectorPreorden;
}

void TABBPoro::PreordenAux(TVectorPoro &tvp, int &posicion) const{
    if(nodo != NULL){
        tvp[posicion] = nodo->item;
        posicion++;
        nodo->iz.PostordenAux(tvp, posicion);
        nodo->de.PostordenAux(tvp, posicion);
    }
}

TVectorPoro TABBPoro::Postorden() const{
    TVectorPoro vectorPostorden(Nodos());
    int pos = 1;
    PreordenAux(vectorPostorden, pos);
    return vectorPostorden;
}

void TABBPoro::PostordenAux(TVectorPoro &tvp, int &posicion) const{
    if(nodo != NULL){
        nodo->iz.PostordenAux(tvp, posicion);
        nodo->de.PostordenAux(tvp, posicion);
        tvp[posicion] = nodo->item;
        posicion++;
    }
}

TVectorPoro TABBPoro::Niveles() const{ // hay que usar queue (cola)
    TVectorPoro recorridoNiveles (Nodos()); 
    queue<TNodoABB *> cola;
    TNodoABB *aux;
    int pos = 1;
    cola.push(nodo);
    while(cola.empty() == false){
        aux = cola.front();
        cola.pop();
        if(aux != NULL){
            recorridoNiveles[pos] = aux->item;
            pos++;
            cola.push(aux->iz.nodo);
            cola.push(aux->de.nodo);
        }
    }
    return recorridoNiveles;
}

TABBPoro TABBPoro::operator+(const TABBPoro &tabbp){
    TABBPoro arbol = *this;
    TVectorPoro vectorArbol;
    vectorArbol = tabbp.Inorden();
    for(int i = 0; i <= vectorArbol.Cantidad(); i++){
        arbol.Insertar(vectorArbol[i]);
    }
    return arbol;
}

TABBPoro TABBPoro::operator-(const TABBPoro &tabbp){
    TABBPoro arbol = *this;
    TVectorPoro vectorArbol;
    vectorArbol = tabbp.Inorden();
    for(int i = 0; i <= vectorArbol.Cantidad(); i++){
        if(arbol.Buscar(vectorArbol[i])){
            arbol.Borrar(vectorArbol[i]);
        }
    }
    return arbol;
}

ostream & operator<<(ostream &os, const TABBPoro &tabbp){
    TVectorPoro aux = tabbp.Niveles();
    os << aux << endl;
}


// EXAMEN JULIO 2015
/*
void TABBPoro::BuscaABBaux(int* &res, int &pos, const TPoro &tp) const{
    int valor;
    TNodoABB *padre = new TNodoABB();
    if(nodo == NULL){
        valor = 0;
        res[pos] = valor;
        pos++;
    }
    else{
        if(Raiz() == tp){
            valor = 3;
            res[pos] = valor;
            pos++;
        }
        else{
            padre = nodo;
            if(padre->de.Raiz() == tp){
                valor = 2;
                res[pos] = valor;
                pos++;
            }
            else{
                if(padre->iz.Raiz() == tp){
                    valor = 1;
                    res[pos] = valor;
                    pos++;
                }
                else{
                    if(nodo->item.Volumen() > tp.Volumen()){
                       nodo->iz.BuscaABBaux(res, pos, tp);
                    }
                    else{
                        nodo->de.BuscaABBaux(res, pos, tp);
                    }
                }
            }
        }
    }
}

int* TABBPoro::BuscaABB(const TListaPoro &tlp) const{
    int *res = NULL;
    int pos;
    if(tlp.EsVacia()){
        return res;
    }
    else{
        if(this->EsVacio()){
            res = new int[tlp.Longitud()];
            pos = 0;
            for(TListaPosicion actual = tlp.Primera(); !actual.EsVacia(); actual = actual.Siguiente()){
                res[pos] = 0;
                pos++;
            }
            return res;
        }
        else{
            TPoro t;
            res = new int[tlp.Longitud()];
            pos = 0;
            for(TListaPosicion actual = tlp.Primera(); !actual.EsVacia(); actual = actual.Siguiente()){
                t = tlp.Obtener(actual);
                BuscaABBaux(res, pos, t);
            }
            return res;
        }
    }
}*/
// EXAMEN JUNIO 2013
/*
int* TABBPoro::examen(const TListaPoro &tlp) const{
    int *v = NULL;
    int pos;
    if(tlp.EsVacia()){ // LA LISTA ES VACIA
        return v;
    }
    else{
        pos = 0;
        v = new int[tlp.Longitud()];    
        TPoro tp;
        for(TListaPosicion actual = tlp.Primera(); !actual.EsVacia(); actual = actual.Siguiente()){
            if(this->EsVacio()){ // EL ARBOL ESTA VACIO
                v[pos] = 0;
                pos++;
            }
            else{ // EL ARBOL NO ESTA VACIO
                tp = tlp.Obtener(actual);
                examenAux(v, tp, pos);
            }    
        } 
    }
    return v;
}*/
/*
    -- SI EL VOLUMEN DEL ELEMENTO EN EL ARBOL nodo->item.Volumen() > tp.Volumen()
        * se buscar por la izquierda nodo->iz.examenAux(...)
    -- SINO
        * se buscar por la derecha nodo->de.examenAux(...)  
    Añade a la posicion (pos) del vector (v) 
        - 0 si el elemento (tp) no tiene hijos o no se encuentra en el ABB
        - 1 si el elemento (tp) tiene 1 hijo
        - 2 si el elemento (tp) tiene 2 hijos 
*/
/*
void TABBPoro::examenAux(int* &v, const TPoro &tp, int &pos) const{
    bool encontrado = Buscar(tp);
    if(!encontrado){
        v[pos] = 0;
        pos++;
    }
    else{
        if(tp.Volumen() == nodo->item.Volumen()){
            if(nodo->iz.EsVacio() && nodo->de.EsVacio()){ // NO TIENE HIJOS
                v[pos] = 0;
                pos++;
            }
            else{
                if(!nodo->iz.EsVacio() && !nodo->de.EsVacio()){ // TIENE 2 HIJOS
                    v[pos] = 2;
                    pos++;
                }   
                else{
                    if(nodo->iz.EsVacio() || nodo->de.EsVacio()){ // TIENE 1 HIJOS
                        v[pos] = 1;
                        pos++;
                    }
                }
            }
        }
        else{
            if(tp.Volumen() < nodo->item.Volumen()){
                nodo->iz.examenAux(v, tp, pos);
            }
            else{
                nodo->de.examenAux(v, tp, pos);
            }
        }    
    }
}*/
// JUNIO 2014
/*
bool TABBPoro::existeCaminoDescendente(const TListaPoro &tlp) const{
    bool existeCamino;
    bool primero;
    bool segundo;
    TNodoABB *posArbol; // Nodo para ir controlando la posicion
    if(EsVacio() || tlp.EsVacia()){
        existeCamino = false;
    }
    else{ 
        TPoro minimo = tlp.Obtener(tlp.Primera());
        TPoro maximo = tlp.Obtener(tlp.Ultima());
        // Buscamos el minimo
        primero = false;
        posArbol = nodo;
        while(posArbol && !primero){ // BUSCO EL PRIMERO EN EL ARBOL
            if(posArbol->item == minimo){
                primero = true;
            }
            else{
                if(posArbol->item.Volumen() < minimo.Volumen()){
                    posArbol = posArbol->de.nodo;   
                }
                else{
                    posArbol = posArbol->iz.nodo;
                }
            }
        }
        if(primero){ // SI ENCUENTRO EL PRIMERO
            segundo = false;
            while(posArbol && !segundo){ // BUSCO EL SEGUNDO
                if(posArbol->item == maximo){
                    segundo = true;
                }
                else{
                    if(posArbol->item.Volumen() < maximo.Volumen()){
                        posArbol = posArbol->de.nodo;   
                    }
                    else{  
                        posArbol = posArbol->iz.nodo;
                    }   
                }
            }
            if(segundo){ // SI ENCUENTRO EL SEGUNDO ES QUE EXISTE EL CAMINO DESCENDENTE
                existeCamino = true;
            }
        }
        else{
            existeCamino = false;
        }
    }
    return existeCamino;
} 
*/
/*
// Metodo que devuelve un vector con los nodos hoja que tiene el arbol
TVectorPoro TABBPoro::extraerHojas() const{
    TVectorPoro resultado(NodosHoja());
    int pos = 1;
    extraerHojasAux(pos, resultado);
    return resultado;
}
void TABBPoro::extraerHojasAux(int &pos, TVectorPoro &v) const{
    if(!Raiz().EsVacio()){    
        if(nodo->iz.EsVacio() && nodo->de.EsVacio()){ // hemos alcanzado la hoja
            v[pos] = nodo->item;
            pos++; 
        }
        else{
            nodo->iz.extraerHojasAux(pos, v);
            nodo->de.extraerHojasAux(pos, v);
        }
    }
}
*/
/*
bool TABBPoro::caminico(const TListaPoro &lista) const{
    bool es, encontrado;
    TPoro minimo, maximo;
    TNodoABB *parbol;
    TListaPosicion pos;
    if(lista.EsVacia()){
        es = true;
    }
    else{
        es = false;
        parbol = nodo;
        pos = lista.Primera();
        encontrado = false;
        while(!parbol && !pos.EsVacia() && !encontrado){
            if(lista.Obtener(pos) == parbol->item){
                encontrado = true;
            } 
            else{
                if(lista.Obtener(pos).Volumen() < parbol->item.Volumen()){
                    parbol = parbol->iz.nodo;
                }
                else{
                    parbol = parbol->de.nodo;
                }
            }
        }
        if(encontrado){
            while(!parbol && pos.EsVacia() && parbol->item == lista.Obtener(pos)){
                pos = pos.Siguiente();
                if(!pos.EsVacia()){
                    if(lista.Obtener(pos).Volumen() < parbol->item.Volumen()){
                      parbol = parbol->iz.nodo;
                    }
                    else{
                        parbol = parbol->de.nodo;
                    }
                }
            }
            if(pos.EsVacia()){
                es = true;
            }
        }
    }
    return es;
}*/

// Devuelve un vector de poros de forma que en la posicion i del vector
// este el padre el poro que ocupa la posicion i de la lista, si el poro no
// esta en el arbol, en esa posicion se guardara el poro vacio
       /*
TPoro *TABBPoro::padresDe(const TListaPoro &lista) const{
    TPoro *v = NULL;
    TListaPosicion p;
    v = NULL;
    int i;
    if(!lista.EsVacia()){
        v = new TPoro[lista.Longitud()];
        i = 0;
        p = lista.Primera();
        while(!p.EsVacia()){
            v[i] = padreDe(lista.Obtener(p));
            p = p.Siguiente();
            i++;
        }
    }
    return v;
}*/
// Devuelve el padre de tp en el arbol
/*
TPoro TABBPoro::padreDe(const TPoro &tp) const{
    TNodoABB *pant, *ptl;
    TPoro poroPadre;
    bool encontrado;
    pant = NULL;
    ptl = NULL;
    encontrado = false;
    while(!ptl != NULL && !encontrado){
        if(ptl->item == tp){
            encontrado = true;
        }
        else{
            if(tp.Volumen() < ptl->item.Volumen()){
                pant = ptl;
                ptl = ptl->iz.nodo;
            }
            else{
                pant = ptl;
                ptl = ptl->de.nodo;
            }
        }
    }
    if(pant){
        poroPadre = pant->item;
    }
    return poroPadre;
}*/

/*
// FUNCION QUE EXTRAR LOS NODOS DEL NIVEL QUE LE PASAS COMO PARAMETRO
TVectorPoro TABBPoro::extraerNodosNivel(int nivel) const{
    TVectorPoro tv(cantidadPorosNivel(nivel));
    int pos = 1;
    extraerNivel(tv, pos, nivel);
    return tv;
}

// Funcion auxiliar que cuenta los poros que hay en un nivel, para asi 
// darle tamaño al vector de poros
int TABBPoro::cantidadPorosNivel(int nivel) const{
    int cantidad;
    if(nodo == NULL){
        return 0;
    }
    else{
        if(nivel == 1){
            return 1;
        }
        else{
            cantidad = nodo->iz.cantidadPorosNivel(nivel - 1) + nodo->de.cantidadPorosNivel(nivel - 1);
        }
    }
    return cantidad;
}

// Funcion que extrae los poros del nivel
void TABBPoro::extraerNivel(TVectorPoro &tvp, int &pos, int nivel) const{
    if(nodo != NULL){
        if(nivel == 1){
            tvp[pos] = nodo->item;
            pos++;
        }
        else{
            nodo->iz.extraerNivel(tvp, pos, nivel - 1);
            nodo->de.extraerNivel(tvp, pos, nivel - 1);
        }
    }
}*/
/*
TListaPoro TABBPoro::extraerNodosNivel(int nivel) const{
    TListaPoro res;
    if(nodo != NULL){
        if(nivel == 1){
            res.Insertar(nodo->item);
        }
        else{
            // EN LA LISTA PODEMOS USAR EL OPERADOR + PARA SUMAR 2 LISTAS 
            // ES DECIR AÑADIR LOS ELEMENTOS DE UNA EN LA OTRA
            res = nodo->de.extraerNodosNivel(nivel - 1) + nodo->iz.extraerNodosNivel(nivel - 1); 
        }
    }
    return res;
}*/