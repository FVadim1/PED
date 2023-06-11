#include <iostream>
using namespace std;

#include "../include/tabbcalendario.h"

//Uso de layering
TNodoABB::TNodoABB() : item(), de(), iz(){}

void TNodoABB::Copia(const TNodoABB &nodo){
    //Usando el operador= de la clase TABBCalendario
    this->item = nodo.item;
    this->iz = nodo.iz;
    this->de = nodo.de;
}

TNodoABB::TNodoABB(const TNodoABB &nodo) : item(nodo.item), iz(nodo.iz), de(nodo.de){}

TNodoABB::~TNodoABB(){}

TNodoABB & TNodoABB::operator=(const TNodoABB &nodo){
    if(this != &nodo){      //Protección contra autoasignación
        this->~TNodoABB();
        Copia(nodo);
    }
    return *this;
}

TABBCalendario::TABBCalendario(){
    this->raiz = NULL;
}

void TABBCalendario::Copia(const TABBCalendario &abb){
    if(!abb.EsVacio()){
        this->raiz = new TNodoABB();
        this->raiz->item = abb.raiz->item;
        this->raiz->iz.Copia(abb.raiz->iz);
        this->raiz->de.Copia(abb.raiz->de);
    }
    else this->raiz = NULL;
}

TABBCalendario::TABBCalendario(const TABBCalendario &abb){
    this->raiz = NULL;
    Copia(abb);
}

TABBCalendario::~TABBCalendario(){
    TNodoABB *aux = new TNodoABB();
    
    while(!EsVacio()){
        aux = this->raiz;   
        raiz->iz.~TABBCalendario();
        raiz->de.~TABBCalendario();

        delete this->raiz;
        this->raiz = NULL;
    }
}

TABBCalendario & TABBCalendario::operator= (const TABBCalendario &abb){
    if(this != &abb){
        this->~TABBCalendario();
        this->Copia(abb);
    }

    return *this;
}

bool TABBCalendario::operator==(const TABBCalendario &abb) const{
    if(this->Inorden() == abb.Inorden())
        return true;
    else return false;
}

bool TABBCalendario::EsVacio() const{
    return (this->raiz == NULL);
}

bool TABBCalendario::Insertar(const TCalendario &cal){
    if(this->EsVacio()){
        TNodoABB *nuevoNodo = new TNodoABB();
        nuevoNodo->item = cal;
        this->raiz = nuevoNodo;
        return true;
    }
    else if(!this->Buscar(cal)){
        if(this->raiz->item < cal)
            return this->raiz->de.Insertar(cal);
        else return this->raiz->iz.Insertar(cal);
    }
    return false;
}

TCalendario TABBCalendario::Ordenar() const{
    TCalendario cal;
    if(!this->EsVacio()){
        if(this->raiz->de.EsVacio())
            return this->raiz->item;
        else return this->raiz->de.Ordenar();
    }

    return cal;
}

bool TABBCalendario::Borrar(const TCalendario &cal){
    if(!this->EsVacio() && this->Buscar(cal)){
        if(this->raiz->item > cal)
            return this->raiz->iz.Borrar(cal);

        else if(this->raiz->item < cal)
            return this->raiz->de.Borrar(cal);

        //Nodo hoja
        else if(this->raiz->iz.EsVacio() && this->raiz->de.EsVacio() ){
            this->raiz = NULL;
            return true;
        }

        else if(this->raiz->iz.EsVacio() && !this->raiz->de.EsVacio()){
            this->raiz = this->raiz->de.raiz;
            return true;
        }

        else if(!this->raiz->iz.EsVacio() && this->raiz->de.EsVacio()){
            this->raiz = this->raiz->iz.raiz;
            return true;
        }

        else if(!this->raiz->iz.EsVacio() && !this->raiz->de.EsVacio()){
            TCalendario izq = this->raiz->iz.Ordenar();
            this->raiz->item = izq;
            this->raiz->iz.Borrar(izq);
        }

        else return false;

    }
    else return false;
}

bool TABBCalendario::Buscar(const TCalendario &cal) const{
    if(!this->EsVacio()){
        if(this->raiz->item == cal)
            return true;
        else{
            if(this->raiz->de.Buscar(cal) || this->raiz->iz.Buscar(cal))
                return true;
            else return false; 
        }
    }
    return false;
}

TCalendario TABBCalendario::Raiz() const{
    return EsVacio() ? TCalendario() : this->raiz->item;
}

int TABBCalendario::Altura() const{
    return EsVacio() ? 0 : 1 + max(this->raiz->iz.Altura(), this->raiz->de.Altura());
}

int TABBCalendario::Nodos() const{
    return EsVacio() ? 0 : 1 + this->raiz->iz.Nodos() + this->raiz->de.Nodos();
}

int TABBCalendario::NodosHoja() const{
    if (!this->EsVacio()){
        if(!this->raiz->iz.EsVacio() || !this->raiz->iz.EsVacio())
            return this->raiz->iz.NodosHoja() + this->raiz->de.NodosHoja();
        else
            return 1;
    }   
    else return 0;
}

void TABBCalendario::InordenAux(TVectorCalendario &v, int &pos) const{
    if(!this->EsVacio()){
        this->raiz->iz.InordenAux(v, pos);
        v[pos++] = this->Raiz();
        this->raiz->de.InordenAux(v, pos);
    }
}
               
TVectorCalendario TABBCalendario::Inorden() const{
    int pos = 1;
    TVectorCalendario v (this->Nodos());
    this->InordenAux(v, pos);
    return v;
}

void TABBCalendario::PreordenAux(TVectorCalendario &v, int &pos) const{
    if(!this->EsVacio()){
        v[pos++] = this->Raiz();
        this->raiz->iz.PreordenAux(v, pos);        
        this->raiz->de.PreordenAux(v, pos);
    }
}

TVectorCalendario TABBCalendario::Preorden() const{
    int pos = 1;
    TVectorCalendario v (this->Nodos());
    this->PreordenAux(v, pos);
    return v;
}

void TABBCalendario::PostordenAux(TVectorCalendario &v, int &pos) const{
    if(!this->EsVacio()){ 
        this->raiz->iz.PostordenAux(v, pos);        
        this->raiz->de.PostordenAux(v, pos);
        v[pos++] = this->Raiz();
    }
}

TVectorCalendario TABBCalendario::Postorden() const{
    int pos = 1;
    TVectorCalendario v (this->Nodos());
    this->PostordenAux(v, pos);
    return v;
}

TVectorCalendario TABBCalendario::Niveles() const{
    queue<TABBCalendario> queue;
    TVectorCalendario vectorCal(this->Nodos());

    TABBCalendario abb = *this;
    queue.push(abb);

    int i = 1;
    while(!queue.empty()){
        vectorCal[i] = abb.raiz->item;
        abb = queue.front();
        
        if(!abb.raiz->iz.EsVacio())
            queue.push(abb.raiz->iz);

        if(!abb.raiz->de.EsVacio())
            queue.push(abb.raiz->de);
        i++;
    }
    return vectorCal;
}

TABBCalendario TABBCalendario::operator+ (TABBCalendario &abb){
    TABBCalendario result(*this);
    TABBCalendario aux(abb);

    TVectorCalendario listaNodos = aux.Inorden();

    for(int i = 1; i <= listaNodos.Tamano(); i++)
        result.Insertar(listaNodos[i]);

    return result;
}

TABBCalendario TABBCalendario::operator- (TABBCalendario &abb){
    TVectorCalendario listaNodos = this->Inorden();
    TABBCalendario result;

    for(int i = 1; i <= listaNodos.Tamano(); i++){
        TCalendario cal = listaNodos[i];

        if(!abb.Buscar(cal))
            result.Insertar(cal);
    }
    return result;
}


//FUNCION DEL EXAMEN
TVectorCalendario TABBCalendario::ABBCamino(TListaCalendario &l){
    TVectorCalendario v;

    if(!l.EsVacia() && !this->EsVacio()){

        for(TListaPos i = l.Primera(); !i.EsVacia(); i = i.Siguiente()){ 
            //Si encontramos el elemento que toca en la lista no hacemos nada, si no existe ...
            if(!this->Buscar(l.Obtener(i))){

                //Lo insertamos en el árbol
                this->Insertar(l.Obtener(i)); 

                //Nos guardamos el elemento insertado en el ABB 
                TCalendario buscado =  l.Obtener(i);         

                //Pasamos el elemento a buscar, así como el vector
                //El vector se ampliará ya que está pasado por referencia
                this->ElegirSubarbol(buscado, v);
            }
        }

        return v;
    }
    else{
        return v;
    }
}

void TABBCalendario::ElegirSubarbol(TCalendario &buscado, TVectorCalendario &v){
        
        //Si el elemento que buscamos es menor que la raiz...
        if(!this->EsVacio() && buscado < this->raiz->item){
            //Añadimos un hueco en el vector, y en él añadimos la raiz, que formará parte del camino
            v.Redimensionar(v.Tamano() + 1);
            v[v.Tamano()] = this->raiz->item;

            //Escogemos el subarbol izquierda ya que así encontraremos el elemento en el ABB
            this->raiz->iz.ElegirSubarbol(buscado, v);
        }

        else if(!this->EsVacio()){
            v.Redimensionar(v.Tamano() + 1);
            v[v.Tamano()] = this->raiz->item;

            this->raiz->de.ElegirSubarbol(buscado, v);
        }  
}


ostream& operator<<(ostream &s, const TABBCalendario &obj){
    TABBCalendario abb(obj);
    s << abb.Niveles();
    return s;
}
