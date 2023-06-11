#include <tlistaporo.h>


// TListaNodo ----------------------------------------------------------------------------------------------------------//


//Constructor por defecto
TListaNodo::TListaNodo(){anterior=NULL,siguiente=NULL;}

//Constructor de copia
TListaNodo::TListaNodo(const TListaNodo &t){
    e = t.e;
    anterior = t.anterior;
    siguiente = t.siguiente;
}

//Destructor
TListaNodo::~TListaNodo(){
     if(anterior != NULL) {anterior = NULL;}
     if(siguiente != NULL) { siguiente = NULL;}
     e.~TPoro();
}

 //Sobrecarga del operador asignación
TListaNodo & TListaNodo::operator=(const TListaNodo &t){

    if(this != &t){
        (*this).~TListaNodo();
        e = t.e;
        anterior = t.anterior;
        siguiente = t.siguiente;
    }

    return *this;
}



// TListaPosicion ------------------------------------------------------------------------------------------------------//

    // FORMA CANÓNICA
//COnstructor por defecto
TListaPosicion::TListaPosicion(){
    pos = NULL;
}

//COnstructor de copia  
TListaPosicion::TListaPosicion(const TListaPosicion &t){
    pos = t.pos;
}  

//Destructor
TListaPosicion::~TListaPosicion(){
    if(pos != NULL){ pos = NULL;}   
}

 //Sobrecarga deñ operador asignación
TListaPosicion & TListaPosicion::operator=(const TListaPosicion &t){

    if(this != &t){
        (*this).~TListaPosicion();
        pos = t.pos;
    }

    return *this;
}

    //MÉTODOS


//Sobrecarga deñ operador igualdad: Dos posiciones son iguales si apuntan a la misma posición de la lista.
bool TListaPosicion::operator==(const TListaPosicion &t) const{
    return pos==t.pos ? true : false;
}

/*
En los métodos Anterior() y Siguiente(), si la posición actual es la primera o la última de la lista
se tiene que devolver una posición vacía.
*/
//Devuelve la posición anterior
TListaPosicion TListaPosicion::Anterior() const{

    TListaPosicion aux;

    if(pos != NULL && pos->anterior != NULL){aux.pos = pos->anterior;} 
    else{aux.pos = NULL;} //es la primera

    return aux;
}

//Devuelve la posición siguiente
TListaPosicion TListaPosicion::Siguiente() const{

    TListaPosicion t;

    if(pos != NULL && pos->siguiente != NULL){t.pos = pos->siguiente;} 
    else{t.pos = NULL;} //es la última

    return t;
}

//Devuelve TRUE si la posición no apunta a una lista (es decir, si el puntero interno 
// ("pos") es NULL), FALSE en caso contrario
bool TListaPosicion::EsVacia() const{

    return pos == NULL ? true : false;
}

// TListaPoro ----------------------------------------------------------------------------------------------------------//


    //FORMA CANÓNICA

//COnstructor por defecto: crea una lista vacía
TListaPoro::TListaPoro(){ primero = NULL; ultimo = NULL;} 

//COnstructor de copia: tiene que realizar una copia exacta
TListaPoro::TListaPoro(const TListaPoro &t){
    primero = t.primero;
    ultimo = t.ultimo;
}

//Destructor: tiene que liberar toda la memoria que ocupe la lista
TListaPoro::~TListaPoro(){


    TListaPosicion aux;

    TListaPosicion posActual = Primera(); // i = 0
    while(posActual.EsVacia() == false){ // vacia = fin de la lista

        aux = posActual.Siguiente();
        if(posActual.pos != NULL){delete posActual.pos; posActual.pos=NULL;}
        posActual = aux;  
    }


    if(primero != NULL){ primero = NULL;}   
    if(ultimo != NULL){ ultimo = NULL;}   

}

 //Sobrecarga deñ operador asignación:  si se asigna una lista a una lista no vacía,
 //se destruye la lista inicial. La asignación tiene que realizar una copia exacta.
TListaPoro & TListaPoro::operator=(const TListaPoro &asignado){

    if(this != &asignado){
        (*this).~TListaPoro();

        TListaPosicion posActual = asignado.Primera(); // i = 0
        while(posActual.EsVacia() == false){ // vacia = fin de la lista
            Insertar(posActual.pos->e);
            posActual = posActual.Siguiente();
        }       
    }

    return *this;
}

    //MÉTODOS

//Sobrecarga del operador igualdad: dos listas son iguales si poseen los mismos elementos
//en el mismo orden
bool TListaPoro::operator==(const TListaPoro &l) {

    TListaPosicion posActual = Primera();
    TListaPosicion posActualparametros = l.Primera();

    if(Longitud() != l.Longitud()){return false;}

    while (posActual.EsVacia() == false)
    {
        if(posActual.pos->e != posActualparametros.pos->e){
            return false;
        }

        posActual = posActual.Siguiente();
        posActualparametros = posActualparametros.Siguiente();
    }

    return true;
}

//Sobrecarga del operador suma: une los elementos de dos listas en una nueva lista 
//(ordenada y sin repetirlos)
TListaPoro TListaPoro::operator+(const TListaPoro &t){

    TListaPoro nuevaLista;

    //meto en la nueva lista los elementos de la primera lista
    TListaPosicion posActualIzquierda = Primera(); // i = 0
    while(posActualIzquierda.EsVacia() == false){ // vacia = fin de la lista
        nuevaLista.Insertar(posActualIzquierda.pos->e);
        posActualIzquierda = posActualIzquierda.Siguiente();
    }

    //meto los elementos de la segunda lista juntos los elementos de la primera en una nueva lista
    TListaPosicion posActualDerecha = t.Primera(); // i = 0
    while(posActualDerecha.EsVacia() == false){ // vacia = fin de la lista
        nuevaLista.Insertar(posActualDerecha.pos->e);
        posActualDerecha = posActualDerecha.Siguiente();
    }

    return nuevaLista;

}

//Sobrecarga del operador resta: devuelve una lista nueva que contiene los elementos
//de la primera lista (operando de la izquierda) que no existen en la segunda 
//lista (operando de la derecha)
TListaPoro TListaPoro::operator-(const TListaPoro &t){

    TListaPoro nuevaLista;

    TListaPosicion posActualIzquierda = Primera(); // i = 0
    while(posActualIzquierda.EsVacia() == false){ // vacia = fin de la lista

        bool existe=false;
        
        TListaPosicion posActualDerecha = t.Primera(); // i = 0
        while(posActualDerecha.EsVacia() == false && !existe){ // vacia = fin de la lista
            
            if(posActualIzquierda.pos->e == posActualDerecha.pos->e){existe=true;}
            posActualDerecha = posActualDerecha.Siguiente();
        }

        if(!existe){nuevaLista.Insertar(posActualIzquierda.pos->e);}

        posActualIzquierda = posActualIzquierda.Siguiente();
    }

    return nuevaLista;
}

 //Devuelve true si la lista está vacía, false en caso contrario
bool TListaPoro::EsVacia() const{
    return (primero == NULL && ultimo == NULL) ? true : false;
}


/* Inserta el elemento en la lista.  
En el método Insertar, el nuevo elemento se inserta en la posición adecuada para que siga siendo
una lista ordenada. En caso de que el elemento a insertar contenga un VOLUMEN igual a uno ya existente en la
lista, el nuevo nodo se insertará DESPUÉS (en orden), al que ya existía.
Esta regla se seguirá cumpliendo a medida que se puedan insertar TPoros con igual VOLUMEN.
Devuelve TRUE si el elemento se puede insertar y FALSE en caso contrario (por ejemplo, porque ya exista en la
lista). */
bool TListaPoro::Insertar(TPoro &poroAinsertar){

    //########### INSERTAR SI LA LISTA ESTÁ VACÍA ###########
    if(EsVacia() == true){ 

        //creo un nuevo nodo con new para que NO desaparezca al terminar el método
        TListaNodo* nodo = new TListaNodo;
        nodo->e = poroAinsertar;
        //--> anterior y  siguiente ya se inician a null con el constructor por defecto, por lo que no lo hago

        //asigno la primero y último puntero de la lista a ese nodo, ya que es el único de la lista
        primero = nodo;
        ultimo = nodo;

        return true;
    }

    //########## INSERTAR SI LA LISTA NO ESTÁ VACÍA ###########
    if(EsVacia() == false){ 
        //Compruebo si el poro no está repetido

        if(Buscar(poroAinsertar) == false){ //si no está repetido

            //compruebo el volumen
            double volumenDelElementoNuevo = poroAinsertar.Volumen();

            TListaPosicion posActual = Primera(); // i = 0
            while(posActual.EsVacia() == false){ // vacia = fin de la lista

                if(volumenDelElementoNuevo < posActual.pos->e.Volumen()){

                    if(posActual == Primera()){
                        //########## INSERTAR AL PRINCIPIO ###########
                        TListaNodo * nodoNuevo = new TListaNodo();

                        nodoNuevo->e = poroAinsertar;
                        nodoNuevo->anterior = NULL;
                        nodoNuevo->siguiente = posActual.pos;

                        posActual.pos->anterior = nodoNuevo;

                        primero=nodoNuevo;
                        //#############################################
                        return true;
                    }else{
                        //##### INSERTAR ANTES DE LA POS ACTUAL #####
                        TListaNodo * nodoNuevo = new TListaNodo();

                        //aquí meto el nodo nuevo entre los 2 nodos que están unidos entre si
                        nodoNuevo->e = poroAinsertar;
                        nodoNuevo->anterior = posActual.pos->anterior;
                        nodoNuevo->siguiente = posActual.pos;

                        posActual.pos->anterior->siguiente = nodoNuevo;
                        posActual.pos->anterior=nodoNuevo;

                        //#############################################
                        return true;
                    }
                }else{

                    if(volumenDelElementoNuevo == posActual.pos->e.Volumen()){
                        //##### INSERTAR DESPUÉS DEL POS ACTUAL #####
                        /* Enunciado: si el volumen es igual, se inserta después */
                        TListaNodo * nodoNuevo = new TListaNodo();

                        //si el nodo siguiente es el último entonces el nuevo será el último
                        if(posActual.pos->siguiente == NULL){

                            posActual.pos->siguiente=nodoNuevo;

                            nodoNuevo->e = poroAinsertar;
                            nodoNuevo->anterior = posActual.pos;
                            nodoNuevo->siguiente = NULL;
                            
                            ultimo = nodoNuevo;

                            return true;

                        }else{
                            /* Teniendo en cuenta si hay 2 seguidos con el mismo volumen
                            solo entra aquí si el proxímo no tiene el mismo volumen, asi
                            me aseguro que se mete solo si llega al final de varios poros
                            con el mismo volumen */

                            if(volumenDelElementoNuevo != posActual.pos->siguiente->e.Volumen()){

                                //si el siguiente nodo no es el último lo meto entre el actual y el siguiente
                                posActual.pos->siguiente->anterior = nodoNuevo;
                                posActual.pos->siguiente=nodoNuevo;

                                nodoNuevo->e = poroAinsertar;
                                nodoNuevo->anterior = posActual.pos;
                                nodoNuevo->siguiente = posActual.pos->siguiente;

                                return true;
                            }
                        }

                    }
                }

                posActual = posActual.Siguiente();

                if(posActual.EsVacia()){
                //si llega al final y aún no se ha insertado entonces
                //significa que su volumen es el mayor
                    //############ INSERTAR AL FINAL ###############
                    TListaNodo * nodoNuevo = new TListaNodo();

                    ultimo->siguiente = nodoNuevo;

                    nodoNuevo->e = poroAinsertar;
                    nodoNuevo->anterior = ultimo;
                    nodoNuevo->siguiente = NULL;

                    ultimo=nodoNuevo;
                    //#############################################
                    return true;
                }
            }
        }
        //si es repetida se va al return false;
    }

    return false;
}

//Devuelve la primera posición de la lista.
//Si la lista está vacía se tiene que devolver una posición vacía.
TListaPosicion TListaPoro::Primera() const{
    TListaPosicion t;
    t.pos = primero;
    return t;
}

//Devuelve la última posición de la lista.
////Si la lista está vacía se tiene que devolver una posición vacía.
TListaPosicion TListaPoro::Ultima() const{
    TListaPosicion t;
    t.pos = ultimo;
    return t;
}

/* Busca y borra el elemento
En el método Borrar(TPoro &), devuelve TRUE si el elemento se puede borrar y FALSE en caso contrario (por
ejemplo, porque el elemento no existe en la lista). */
bool TListaPoro::Borrar(TPoro &poroABorrar){

    if(Buscar(poroABorrar) == true){ //si existe

        TListaPosicion posActual = Primera(); // i = 0
        while(posActual.EsVacia() == false){ // vacia = fin de la lista

            if(posActual.pos->e == poroABorrar){ 
                return Borrar(posActual);
            }

            posActual = posActual.Siguiente();
        }   
    }

    return false;
}

/*Borra el elemento que ocupa la posición indicada.
En el método Borrar(TListaPosicion &), devuelve TRUE si el elemento se puede borrar (porque la posición apunta
a un nodo de la lista) y FALSE en caso contrario (por ejemplo, porque la posición no es válida). El paso por
referencia del parámetro es obligatorio, ya que una vez eliminado el elemento, la posición tiene que pasar a estar
vacía (no asignada a ninguna lista).
No es necesario comprobar que el objeto TListaPosicion apunte a un nodo de la lista.
Hay que comprobar que el objeto TListaPosicion no es vacío */
bool TListaPoro::Borrar(TListaPosicion &pos_A_Borrar){

    if(pos_A_Borrar.EsVacia()){return false;}

    //########## BORRAR LISTA CON UN ELEMENTO #############
    if(Longitud() == 1){ 
        if(pos_A_Borrar.pos != NULL){ delete pos_A_Borrar.pos; pos_A_Borrar.pos = NULL;}
        primero=NULL;
        ultimo=NULL;
        return true;
        //lista se queda vacía
    }

    //####### BORRAR LISTA CON MÁS DE UN ELEMENTO #########
    if(Longitud() > 1) {
        TListaPosicion posActual = Primera(); // i = 0
        while(posActual.EsVacia() == false){ // vacia = fin de la lista

            if(pos_A_Borrar.pos == posActual.pos){

                //####### BORRAR EL PRIMER ELEMENTO #########
                if(posActual == Primera()){
                    primero = primero->siguiente;
                    primero->anterior = NULL;
                    if(pos_A_Borrar.pos != NULL){ delete pos_A_Borrar.pos; pos_A_Borrar.pos = NULL;}
                    return true;
                
                }

                //####### BORRAR EL ÚLTIMO ELEMENTO #########
                if(posActual == Ultima()){
                    ultimo = ultimo->anterior;
                    ultimo->siguiente = NULL;
                    return true;
                }

                //##### BORRAR SI NO ES NI PRIMER NI ÚLTIMO ELEMENTO #####
                /*Si no ha entrado en ninguna de las dos condiciones anteriores
                entonces no es ni primero ni el último elemento */
            
                posActual.pos->anterior->siguiente = posActual.pos->siguiente;
                posActual.pos->siguiente->anterior = posActual.pos->anterior;

                if(pos_A_Borrar.pos != NULL){ delete pos_A_Borrar.pos; pos_A_Borrar.pos = NULL;}

                return true;
            }

            posActual = posActual.Siguiente();
        }
    }

    return false;
}

//Obtiene el elemento que ocupa la posición indicada.
TPoro TListaPoro::Obtener(const TListaPosicion &posIndicada) const{

    TPoro poro_obtenido;

    TListaPosicion posActual = Primera(); 
    while(posActual.EsVacia() == false){ // vacia = fin de la lista

        if(posIndicada == posActual){
            poro_obtenido = posIndicada.pos->e;
            break;
        }

        posActual = posActual.Siguiente();
    }

    return poro_obtenido;

}

//Devuelve true si el elemento está en la lista, false en caso contrario.
bool TListaPoro::Buscar(TPoro &poroBuscado){

    TListaPosicion posActual = Primera(); // i = 0
    while(posActual.EsVacia() == false){ // vacia = fin de la lista

        if(posActual.pos->e == poroBuscado) {
            return true;
        } //si son el mismo

        posActual = posActual.Siguiente();
    }

    return false; 
}

//Devuelve la longitud de la lista.
int TListaPoro::Longitud() const{

    int cont = 0;

    TListaPosicion posActual = Primera(); // i = 0
    while(posActual.EsVacia() == false){ // vacia = fin de la lista
        cont++;
        posActual = posActual.Siguiente();
    }

    return cont;
}



ostream & operator<<(ostream &os,const TListaPoro &t){

    os<<"(";

    TListaPosicion posActual = t.Primera(); // i = 0
    while(posActual.EsVacia() == false){ // vacia = fin de la lista
        os<<t.Obtener(posActual);
        if(!(posActual == t.Ultima())){ os<<" ";}

        posActual = posActual.Siguiente();
    }
    os << ")";
    return os;
}



//Extraer un rango de nodos de la lista
/*
•En el método ExtraerRango:
 Devuelve una lista con los elementos TPoro comprendidos entre las posiciones n1 y n2 (ambas
 incluidas) de la lista que invoca a la función. Los nodos comprendidos entre n1 y n2 (ambos incluidos)
 deben borrarse de la lista que invoca a la función.
 Cosas a tener en cuenta:
    • Se comienza a numerar las posiciones de la lista a partir de 1.
    • Si n2 sobrepasa la longitud de la lista invocante “por exceso” : se seleccionan sólo los
      elementos contenidos entre n1 y la longitud de la lista.
    • Si n1 es menor o igual a 0: se seleccionan sólo los elementos contenidos entre la posición 1
      de la lista y n2 .
    • Si n1 = n2 : devolverá una lista con 1 sólo elemento, extrayéndolo de la lista llamante.
    • Si n1 > n2 : devolverá una lista VACÍA sin modificar a la llamante, pues los límites no engloban
                   elemento alguno. */
TListaPoro TListaPoro::ExtraerRango(int n1,int n2){

    //correcion valores rango
    if(n1 <= 0) { n1 = 1;}
    int longitud = Longitud();
    if(n2 > longitud){ n2 = longitud;}

     
    TListaPoro listaPorosRango;

    if(n1 > n2){return listaPorosRango;}

    int i = 1;
    TListaPosicion aux;
    TListaPosicion posActual = Primera(); // i = 0
    while(posActual.EsVacia() == false){ // vacia = fin de la lista

        if(i >= n1 && i <= n2){
            listaPorosRango.Insertar(posActual.pos->e);
            
            aux = posActual;
            posActual = posActual.Siguiente();
            Borrar(aux);
            i++;

            if(n1==n2){return listaPorosRango;}

        }else{

            posActual = posActual.Siguiente();
            i++;
        }


    }

    return listaPorosRango;
}





