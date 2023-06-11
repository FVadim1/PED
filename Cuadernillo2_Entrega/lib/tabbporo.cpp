#include "tabbporo.h"


//////////////////[ TNodoABB ]///////////////////


//Constructor por defecto
TNodoABB::TNodoABB(){
    /*NOTA: Como las variables de esta clase son objetos de otras clases 
    pues automáticamente se llamará al constructor por defecto de las 
    otras clases, por lo que aquí no hay que hacer nada. */
}

//Constructor de copia
TNodoABB::TNodoABB(const TNodoABB &t){

    item = t.item;
    iz = t.iz;
    de = t.de;

}

//Destructor
TNodoABB::~TNodoABB(){
    /*NOTA: Como las variables de esta clase son objetos de otras clases 
    pues automáticamente se llamará al destructor por defecto de las 
    otras clases, por lo que aquí no hay que hacer nada. */
}

//Sobrecarga del operador asignación
TNodoABB & TNodoABB::operator=(TNodoABB &t){

    if(this != &t){
        (*this).~TNodoABB();
        item = t.item;
        iz = t.iz;
        de = t.de;
    }
    return *this;
}



//////////////////[ TABBPoro ]///////////////////

    //FORMA CANÓNICA

//Constructor por defecto
TABBPoro::TABBPoro(){ 
    nodo=NULL; 
}

//Constructor de copia
TABBPoro::TABBPoro(const TABBPoro &t){
    if(t.nodo){
        this->nodo = new TNodoABB(*t.nodo);
    }
}

//Destructor
TABBPoro::~TABBPoro(){
    if(nodo){ //nodo != NULL
        delete nodo;
        nodo = NULL;
    }
} 

//Sobrecarga del operador asignación
TABBPoro & TABBPoro::operator= (const TABBPoro &t){

    if(this != &t){

        (*this).~TABBPoro();
        
        if(t.nodo){
            this->nodo = new TNodoABB(*t.nodo);
        }

    }
    return *this;
}


    //MÉTODOS

//Devuelve TRUE si el árbol está vacío, FALSE en caso contrario
bool TABBPoro::EsVacio(){
    return !nodo ? true : false; //if(nodo!==null){return true;}else{return false;}
} 

//Inserta el elemento en el árbol
/* La idea es insertar el poro si se ha llegado a un nodo que no apunta a nada.
Se va "bajando" por la izquierda o derecha según el volumen (izquierda si volumen menor)
y (derecha si volumen mayor) hasta llegar a encontrar un nodo que no apùnta a nada. */
bool TABBPoro::Insertar(TPoro &nuevoItem){
    
    if(Buscar(nuevoItem)){return false;}

    bool insertado = false;

    if(!this->nodo){ 
        TNodoABB * nuevoNodo = new TNodoABB();
        nuevoNodo->item = nuevoItem;
        this->nodo = nuevoNodo;
        insertado = true;
    }else{

        double volumenItemActual = this->nodo->item.Volumen();
        double volumenItemNuevo = nuevoItem.Volumen();

        //voy a la izquierda o la derecha según el volumen
        insertado = volumenItemNuevo < volumenItemActual ?
                    nodo->iz.Insertar(nuevoItem) : nodo->de.Insertar(nuevoItem);
    }

    return insertado;  
} 

//Borra el elemento en el árbol
bool TABBPoro::Borrar(TPoro &item_a_Borrar){

    bool borrado = false;

    if(this->nodo){ //si el nodo apunta a algo,es decir, no sea NULL

        TPoro itemActual = this->nodo->item;

        if(itemActual == item_a_Borrar){ //encuentro el nodo a borrar
            
            if(esHoja(this->nodo)){ //no tiene hijos
                delete this->nodo;
                nodo=NULL;
                borrado = true;
            }else{ //si tiene hijos
                bool tieneHijoIzquierdo = this->nodo->iz.nodo;
                bool tieneHijoDerecho = this->nodo->de.nodo;
                bool tieneAmbosHijos = tieneHijoIzquierdo && tieneHijoDerecho;

                if(tieneAmbosHijos){
                /*  DOS FORMAS DE HACERLO para que siga ordenado: buscando el poro con el mínimo valor en el 
                    subarbol derecho o buscando el poro con el máximo valor en el subarbol izquierdo*/

                    //Obtengo el item más a la izquierda del subarbol derecho
                    TPoro poroMenor = ObtenerMenorDerecha(nodo->de.nodo); //hago copia
                    borrado = Borrar(poroMenor); //borro el menor dentro del arbol
                    this->nodo->item = poroMenor;


                }else{ //solo tiene 1 hijo
                    /* La idea es que el padre de este nodo me seguirá apuntando a mí
                    pero ahora yo me convertiré en uno de mis hijos */

                    /* Me convierto +en mi hijo izquierdo o derecho, según cual tenga */
                    tieneHijoIzquierdo ? this->nodo = this->nodo->iz.nodo : this->nodo = this->nodo->de.nodo;
                    borrado=true;
                }
            }

        }else{ //sigo buscando

            double volumenItemActual = this->nodo->item.Volumen();
            double volumenItemBuscado = item_a_Borrar.Volumen();

            //voy a la izquierda o la derecha según el volumen
            borrado = volumenItemBuscado < volumenItemActual ?
                this->nodo->iz.Borrar(item_a_Borrar) : this->nodo->de.Borrar(item_a_Borrar);               
        }
    }

    return borrado;
} 

TPoro TABBPoro::ObtenerMenorDerecha(TNodoABB * nodo){

    if(nodo){
        if(nodo->iz.nodo != NULL){// aun quedan hijos izquierdos
            return ObtenerMenorDerecha(nodo->iz.nodo);
        }else{
            
            return nodo->item; // ya no hay mas hijos izquierdos
        }
    }
}

 //Devuelve TRUE si el elemento está en el árbol, FALSE en caso contrario
bool TABBPoro::Buscar(TPoro &itemBuscado){

    bool encontrado = false;

    if(this->nodo){ //si el nodo apunta a algo,es decir, no sea NULL

        TPoro itemActual = this->nodo->item;

        if(itemActual == itemBuscado){

            encontrado = true;

        }else{ //sigo buscando

            double volumenItemActual = this->nodo->item.Volumen();
            double volumenItemBuscado = itemBuscado.Volumen();

            //voy a la izquierda o la derecha según el volumen
            encontrado = volumenItemBuscado < volumenItemActual ?
                this->nodo->iz.Buscar(itemBuscado) : this->nodo->de.Buscar(itemBuscado);               
        }
    }

    return encontrado;
}

//Devuelve el elemento en la raiz del árbol
/* Raíz devuelve el TPoro raíz del árbol. SI el árbol está vacío, devuelve TPoro vacío */
TPoro TABBPoro::Raiz(){
    return nodo ? this->nodo->item : TPoro() ; //if(nodo!=NULL){...}else{return TPoro();}
} 

//Devuelve la altura del árbol (la altura de un arbol vacío es 0)
int TABBPoro::Altura(){
    
    int altura = 0; //CASO BASE

    if(nodo){ // va sumando 1 hasta que el nodo sea null
        altura++;
        altura += nodo->iz.Altura() < nodo->de.Altura() ? nodo->de.Altura() : nodo->iz.Altura();
    }

    return altura;
} 

//Devuelve el número de nodos del árbol (un árbol vacío posee 0 nodos)
int TABBPoro::Nodos() const{ //RECURSIÓN
    return nodo ? 1 + nodo->iz.Nodos() + nodo->de.Nodos() : 0; //if(nodo!=NULL){...}else{return 0;}
} 

//Mi función propia que mira si iz y de son null
bool TABBPoro::esHoja(const TNodoABB *padre){
    return (!padre->iz.nodo && !padre->de.nodo) ? true : false;
}//si el abbporo izquierdo y el derecho no apuntan a nada (es decir,son null) devuelve false, si no, true

//Devuelve el número de nodos hoja en el árbol (la raiz puede ser nodo hoja)
int TABBPoro::NodosHoja(){
    
    int numNodosHoja = 0; //CASO BASE

    if(nodo){ //nodo != null
        numNodosHoja += esHoja(this->nodo) ? 1 : nodo->iz.NodosHoja() + nodo->de.NodosHoja();
    }
    return numNodosHoja;
    
} 

//Devuelve el recorrido en inorden
TVectorPoro TABBPoro::Inorden() const{

    int tamVector = this->Nodos(), 
    posVector = 1;
    TVectorPoro recoInorden(tamVector);
    InordenAux(recoInorden, posVector);
    return recoInorden;
}

 //AUXILIAR: Devuelve el recorrido en inorden
void TABBPoro::InordenAux(TVectorPoro &tvector, int &pos) const{

    if(!nodo){
        return; //CASO BASE
    }else{

        /* Primero procesará su hijo izquierdo (el cual procesará a sus hijos)*/
        nodo->iz.InordenAux(tvector,pos); 

        /* Se mete a así mismo en el vector */
        tvector[pos] = nodo->item;
        pos++;

        /* Luego procesará su hijo derecho (el cual procesará a sus hijos) */
        nodo->de.InordenAux(tvector,pos);
    }
}

//Devuelve el recorrido en preorden
TVectorPoro TABBPoro::Preorden() const {

    int tamVector = this->Nodos(), 
    posVector = 1;
    TVectorPoro recoPreorden(tamVector);
    PreordenAux(recoPreorden, posVector);
    return recoPreorden;
}

 //AUXILIAR: Devuelve el recorrido en preorden
void TABBPoro::PreordenAux(TVectorPoro &tvector, int &pos) const{

    if(!nodo){
        return; //CASO BASE
    }else{

        tvector[pos] = nodo->item;
        pos++;

        nodo->iz.PreordenAux(tvector,pos);       
        nodo->de.PreordenAux(tvector,pos);
    }
}

//Devuelve el recorrido en postorden
TVectorPoro TABBPoro::Postorden() const{

    int tamVector = this->Nodos(), 
    posVector = 1;
    TVectorPoro recoPostorden(tamVector);
    PostordenAux(recoPostorden, posVector);
    return recoPostorden;
} 
 //AUXILIAR: Devuelve el recorrido en postorden
void TABBPoro::PostordenAux(TVectorPoro &tvector, int &pos) const{

    if(!nodo){
        return; //CASO BASE
    }else{

        nodo->iz.PostordenAux(tvector,pos);       
        nodo->de.PostordenAux(tvector,pos);

        tvector[pos] = nodo->item;
        pos++;
    }
}

/* 
 -> Queue:[Primero, Segundo, Último] 
 Queue.front() -> Primero;
 Queue.back() -> Último;

 Queue.pop(); //eliminar el que está en la pos 0
 -> Queue:[Segundo, Último]
*/

//Devuelve el recorrido en niveles
TVectorPoro TABBPoro::Niveles() const {
    
    int tamVector = this->Nodos(), 
        pos = 1;
    TVectorPoro vec_recorridoNiveles(tamVector);
    queue<TNodoABB *> queue;
    TNodoABB *queueFront;

    queue.push(this->nodo); 

    /* La idea es: Primero proceso el nodo actual en el vector, luego
    meto primero a su hijo izquierdo y luego a su hijo derecho en la cola.
    En la siguiente iteración proceso al hijo izquierdo en el vector, y meto
    en la cola a sus dos hijos, luego proceso al hijo derecho de la iteración anterior
    y meto sus dos hijos en la cola. Así voy procesando a todos los hijos, hijo por hijo desde
    la izquierda a la derecha */

    while(!queue.empty()){

        queueFront = queue.front(); 
        vec_recorridoNiveles[pos] = queueFront->item;

        if(queueFront->iz.nodo){ queue.push(queueFront->iz.nodo); };
        if(queueFront->de.nodo){ queue.push(queueFront->de.nodo); }; 

        queue.pop(); 
        pos++;
        
    }

    return vec_recorridoNiveles;
 } 

//Sobrecarga del operador igualdad
/* En el operador==, dos árboles son iguales si poseen los mismos elementos independientemente
de la estructura interna del árbol (NO se exige que la estructura de ambos sea la misma) */
bool TABBPoro::operator==(const TABBPoro &t) const{

/* Si los ordeno de la misma manera puedo mirar si son iguales 
    utilizando el == de tvectorporo  */
    bool iguales = false;

    if(this->Nodos() == t.Nodos()){
        TVectorPoro thisVector = this->Preorden();
        TVectorPoro argsVector = t.Preorden();

        if(thisVector == argsVector){ iguales=true;}
    }

    return iguales;
}

/* En el operador "+" , primero se tiene que sacar una copia del operando (árbol)
de la izquierda y a continuación insertar los elementos del operando (árbol)
de la derecha según su recorrido por Inorden */
//Suma de dos ABB

TABBPoro TABBPoro::operator+(TABBPoro &opDerecha){

    TABBPoro opIzquierda = *this;
    TVectorPoro vec_opDerechaInorden = opDerecha.Inorden();

    for(int i = 1; i <= vec_opDerechaInorden.Cantidad(); i++){
        opIzquierda.Insertar(vec_opDerechaInorden[i]);
    }

    return opIzquierda;
} 
 
/* EN el operador "-", se recorre el operando (árbol) de la izquierda por Inorden
y si el elemento NO está en el operando (árbol) de la derecha, se inserta en el
árbol resultando (inicialmente vacío) y el proceso se repite para todos los elementos
del operando de la izquierda */

//Resta de dos ABB
TABBPoro TABBPoro::operator-(TABBPoro &opDerecha){

    TABBPoro resultante ;
    TVectorPoro vec_opIzquierda = Inorden();

    for(int i = 1; i <= vec_opIzquierda.Cantidad(); i++){
        if(!opDerecha.Buscar(vec_opIzquierda[i])){
            resultante.Insertar(vec_opIzquierda[i]);
        }
    }
    
    return resultante; 

} 

ostream & operator<<(ostream &os,const  TABBPoro &t){

    os<< t.Niveles();
    return os;
}


