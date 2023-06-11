#include <tavlporo.h>


//======================== TNodoAVL ======================== 


/*___________________FORMA CANÓNICA__________________________ */
/* Los TPoro en el árbol están ordenados en función del volumen */
//constructor por defecto
TNodoAVL::TNodoAVL(){ 
    /*NOTA: Como las variables de esta clase son objetos de otras clases 
    pues automáticamente se llamará al constructor por defecto de las 
    otras clases, por lo que aquí no hay que hacer nada. */
}

//Connstructor de copia
TNodoAVL::TNodoAVL(const TNodoAVL &nodoavl){
    item = nodoavl.item;
    iz = nodoavl.iz;
    de = nodoavl.de;
    fe = nodoavl.fe;
}

//Destructor
TNodoAVL::~TNodoAVL(){
    /*NOTA: Como las variables de esta clase son objetos de otras clases 
    pues automáticamente se llamará al destructor por defecto de las 
    otras clases, por lo que aquí no hay que hacer nada. */
}

//Sobrecarga del operador asignación
TNodoAVL & TNodoAVL::operator=(const TNodoAVL &nodoavl){

    if(this != &nodoavl){

        (*this).~TNodoAVL();

        item = nodoavl.item;
        iz = nodoavl.iz;
        de = nodoavl.de;
        fe = nodoavl.fe;
    }

    return *this;

}

//======================== TAVLPoro ======================== 


/*___________________FORMA CANÓNICA__________________________ */
//constructor por defecto
TAVLPoro::TAVLPoro(){
    raiz = NULL;
}

//Connstructor de copia
TAVLPoro::TAVLPoro(const TAVLPoro &avlporo){
    if(avlporo.raiz){
        this->raiz = new TNodoAVL(*avlporo.raiz); //creo nuevo puntero con la copia de los objetos de este
    }
}

//Destructor
TAVLPoro::~TAVLPoro(){
    if(raiz){ //raiz != NULL
        delete raiz;
        raiz = NULL;
    }
}

//Sobrecarga del operador asignación
TAVLPoro & TAVLPoro::operator=(const TAVLPoro &t){
    if(this != &t){

        (*this).~TAVLPoro();
        
        if(t.raiz){
            this->raiz = new TNodoAVL(*t.raiz);
        }
    }
    return *this;
}

/*___________________MÉTODOS__________________________ */

//Sobrecarga del operador igualdad
bool TAVLPoro::operator==(const TAVLPoro &t) const{

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

//Sobrecarga del operador desigualdad
bool TAVLPoro::operator!=(const TAVLPoro &avlporo) const{
    return !(*this==avlporo);
}

//Devuelve TRUE si el árbol está vacio, FALSE en caso contrario
bool TAVLPoro::EsVacio(){
    return !raiz ? true : false; //if(nodo==null){return true;}else{return false;}
} 

//Devuelve TRUE si el elemento está en el árbol, FALSE en caso contrario
bool TAVLPoro::Buscar(TPoro &itemBuscado){

    bool encontrado = false;

    if(this->raiz){ //si el nodo apunta a algo,es decir, no sea NULL

        TPoro itemActual = this->raiz->item;

        if(itemActual == itemBuscado){

            encontrado = true;

        }else{ //sigo buscando

            double volumenItemActual = this->raiz->item.Volumen();
            double volumenItemBuscado = itemBuscado.Volumen();

            //voy a la izquierda o la derecha según el volumen
            encontrado = volumenItemBuscado < volumenItemActual ?
                this->raiz->iz.Buscar(itemBuscado) : this->raiz->de.Buscar(itemBuscado);               
        }
    }

    return encontrado;
}


//Devuelve el elemento TPoro raiz del árbol AVL
TPoro TAVLPoro::Raiz(){
    return raiz ? this->raiz->item : TPoro() ; //if(nodo!=NULL){...}else{return TPoro();}
}

//Devuelve el número de nodos del árbol (un árbol vacío posee 0 nodos)
int TAVLPoro::Nodos() const{
    return raiz ? 1 + raiz->iz.Nodos() + raiz->de.Nodos() : 0; //if(nodo!=NULL){...}else{return 0;}
}


//Mi función propia que mira si iz y de son null
bool TAVLPoro::esHoja(const TNodoAVL *padre){
    return (!padre->iz.raiz && !padre->de.raiz) ? true : false;
}//si el abbporo izquierdo y el derecho no apuntan a nada (es decir,son null) devuelve false, si no, true

//Devuelve el número de nodos hoja en el árbol (la raiz puede ser nodo hoja)
int TAVLPoro::NodosHoja(){
    int numNodosHoja = 0; //CASO BASE

    if(raiz){ //nodo != null
        numNodosHoja += esHoja(this->raiz) ? 1 : raiz->iz.NodosHoja() + raiz->de.NodosHoja();
    }
    return numNodosHoja;
}

//Devuelve el recorrido en Inorden sobre un vector
TVectorPoro TAVLPoro::Inorden() const{

    int tamVector = this->Nodos(), 
    posVector = 1;
    TVectorPoro recoInorden(tamVector);
    InordenAux(recoInorden, posVector);
    return recoInorden;

}
void TAVLPoro::InordenAux(TVectorPoro &tvector, int &pos) const{

    if(!raiz){
        return; //CASO BASE
    }else{

        /* Primero procesará su hijo izquierdo (el cual procesará a sus hijos)*/
        raiz->iz.InordenAux(tvector,pos); 

        /* Se mete a así mismo en el vector */
        tvector[pos] = raiz->item;
        pos++;

        /* Luego procesará su hijo derecho (el cual procesará a sus hijos) */
        raiz->de.InordenAux(tvector,pos);
    }
}

//Devuelve el Preorden en Inorden sobre un vector
TVectorPoro TAVLPoro::Preorden() const{

    int tamVector = this->Nodos(), 
    posVector = 1;
    TVectorPoro recoPreorden(tamVector);
    PreordenAux(recoPreorden, posVector);
    return recoPreorden;

}

void TAVLPoro::PreordenAux(TVectorPoro &tvector, int &pos) const{

    if(!raiz){
        return; //CASO BASE
    }else{

        tvector[pos] = raiz->item;
        pos++;

        raiz->iz.PreordenAux(tvector,pos);       
        raiz->de.PreordenAux(tvector,pos);
    }

}

//Devuelve el Postorden en Inorden sobre un vector
TVectorPoro TAVLPoro::Postorden() const{

    int tamVector = this->Nodos(), 
    posVector = 1;
    TVectorPoro recoPostorden(tamVector);
    PostordenAux(recoPostorden, posVector);
    return recoPostorden;

}

void TAVLPoro::PostordenAux(TVectorPoro &tvector, int &pos) const{

    if(!raiz){
        return; //CASO BASE
    }else{

        raiz->iz.PostordenAux(tvector,pos);       
        raiz->de.PostordenAux(tvector,pos);

        tvector[pos] = raiz->item;
        pos++;
    }
}

//Inserta el elemento TPoro en el árbol
bool TAVLPoro::Insertar(TPoro &item_a_Insertar){

    bool insertado = false;
    bool crece = false;

    if(Buscar(item_a_Insertar) == false){//COMPRUEBO QUE NO EXISTE

        insertado = InsertarAux(item_a_Insertar, crece);

    } 
    return insertado;
}

//AUXILIAR: Inserta el elemento TPoro en el árbol
/* Tomando el ejemplo del pdf de teoría [Tema3.2 -> página 7] */
bool TAVLPoro::InsertarAux(TPoro &item_a_Insertar, bool &crece){

    bool insertado = false;
    bool creceIz = false;
    bool creceDe = false;

    if(!this->raiz){ // (this->raiz == NULL) [ENCONTRADO NULL]

        TNodoAVL * nuevoNodo = new TNodoAVL();
        nuevoNodo->item = item_a_Insertar;
        this->raiz = nuevoNodo;
        this->raiz->fe = 0;
        
        crece = true;  //aquí es donde pongo si crece izq o der según cual entre por parametros
        insertado = true;

    }else{ // (this->raiz != NULL)   [SIGO BUSCANDO NULL]

        double volumenItemActual = this->raiz->item.Volumen();
        double volumenItemNuevo = item_a_Insertar.Volumen();

        if(volumenItemActual == volumenItemNuevo){return false;}//COMPRUEBO MISMO VOLUMEN

        //TIENEN DIFERENTE VOLUMEN, CONTINUO
        if(volumenItemNuevo < volumenItemActual){ // [Voy por la izquierda]

            insertado = raiz->iz.InsertarAux(item_a_Insertar,creceIz);

        }else{ // [Voy por la derecha]

            insertado = raiz->de.InsertarAux(item_a_Insertar,creceDe);
        }

        if(insertado){

            if(creceIz){

                raiz->fe--; //si ha crecido mi subarbol izquierdo reduzco mi FE

                if(raiz->fe == -2){ // [HAY DESEQUILIBRIO , TOCA ROTACIÓN]

                    if(this->raiz->iz.raiz->fe == -1){

                        rotacion_II();

                    }else{

                        if(this->raiz->iz.raiz->fe == 1)

                            rotacion_ID();
                    }

                    crece = false; //Solo una rotación por inserción

                }else{

                    if(raiz->fe == -1){ // HABRÁ DESEQUILIBRIO EN EL PADRE DE ESTE
                        crece = true; //para bajar el FE del padre de this en la recursión
                    }
                }
                

                //SI ES 0 NO SE HACE NADA MÁS (así está en los pdf se hacen rotaciones
                //solo si tiene que ver algo el 2 o el 1 (tambień combinando los negativos))

            }else{

                if(creceDe){

                    raiz->fe++; //si ha crecido mi subarbol derecho aumento mi FE 

                    if(raiz->fe == 2){ // [HAY DESEQUILIBRIO , TOCA ROTACIÓN]

                        if(this->raiz->de.raiz->fe == 1){

                            rotacion_DD();

                        }else{

                            if(this->raiz->de.raiz->fe == -1)

                                rotacion_DI();
                        }

                        crece = false; //Solo una rotación por inserción

                    }else{ //AÚN NO HAY DESEQUILIBRIO PERO PUEDE HABERLO EN EL PADRE DE ESTE

                        if(raiz->fe == 1){ // HABRÁ DESEQUILIBRIO EN EL PADRE DE ESTE
                            crece = true; //para bajar el FE del padre de this en la recursión
                        }
                    }
                }
            }
        }
    }

    return insertado;

}

//rotación árbol derecho  -->
void TAVLPoro::rotacion_DD(){

    TNodoAVL * yo = this->raiz; //guardo mi posicion en un AUX
    this->raiz = this->raiz->de.raiz; //le doy mi posición a mi hijo derecho
    yo->de.raiz = this->raiz->iz.raiz; 
    this->raiz->iz.raiz = yo; //ahora yo seré el hijo izquierdo de mi hijo derecho (anteriormente)
    yo = NULL; //pongo el AUX a NULL ya que no lo voy a necesitar más


    //ACTUALIZO LOS FE
    this->raiz->fe = this->raiz->de.Altura() - this->raiz->iz.Altura(); //actualizo al this
    this->raiz->iz.raiz->fe = this->raiz->iz.raiz->de.Altura() - this->raiz->iz.raiz->iz.Altura();  //actualizo al derecho
    //el derecho no lo he tocado por lo que no hace falta actualizar  
}

//rotación árbol derecho  -->
void TAVLPoro::rotacion_DI(){

    TNodoAVL * yo = this->raiz; //guardo mi posicion en un AUX
    //Guardo los hijos izquierdo y derecho del hijo derecho de mi hijo izquierdo
    TNodoAVL * hijoDer_hijoIzq_hijoIzq = this->raiz->de.raiz->iz.raiz->iz.raiz;
    TNodoAVL * hijoDer_hijoIzq_hijoDer = this->raiz->de.raiz->iz.raiz->de.raiz;

    this->raiz = this->raiz->de.raiz->iz.raiz; //le doy mi posición al hijo derecho de mi hijo izquierdo

    this->raiz->de.raiz = yo->de.raiz; //mi hijo izquierdo ahora será el hijo izq de la nueva this-raiz
    this->raiz->iz.raiz = yo; //yo estaré a la derecha del nuevo this

    //me llevo a los hijos y los convierto en mis hijos a mi nueva posicion (derecha del nuevo this)
    this->raiz->de.raiz->iz.raiz = hijoDer_hijoIzq_hijoDer;
    this->raiz->iz.raiz->de.raiz = hijoDer_hijoIzq_hijoIzq;

    //ACTUALIZO LOS FE
    this->raiz->fe = this->raiz->de.Altura() - this->raiz->iz.Altura(); //actualizo al this
    this->raiz->de.raiz->fe = this->raiz->de.raiz->de.Altura() - this->raiz->de.raiz->iz.Altura();  //actualizo al derecho
    this->raiz->iz.raiz->fe = this->raiz->iz.raiz->de.Altura() - this->raiz->iz.raiz->iz.Altura();  //actualizo al izquierdo

}

//rotación árbol izquierdo  <--
void TAVLPoro::rotacion_II(){

    TNodoAVL * yo = this->raiz; //guardo mi posicion en un AUX
    this->raiz = this->raiz->iz.raiz; //le doy mi posición a mi hijo izquierdo
    yo->iz.raiz = this->raiz->de.raiz; //ahora mi hizo izquierdo apunta al hijo derecho de mi hijo izquierdo en vez de mi hijo izquierdo
    this->raiz->de.raiz = yo; //ahora yo seré el hijo derecho de mi hijo izquierdo (anteriormente)
    yo = NULL; //pongo el AUX a NULL ya que no lo voy a necesitar más


    //ACTUALIZO LOS FE
    this->raiz->fe = this->raiz->de.Altura() - this->raiz->iz.Altura(); //actualizo al this
    this->raiz->de.raiz->fe = this->raiz->de.raiz->de.Altura() - this->raiz->de.raiz->iz.Altura();  //actualizo al derecho
    //el izquierdo no lo he tocado por lo que no hace falta actualizar  
}

//rotación árbol izquierdo <--
void TAVLPoro::rotacion_ID(){

    TNodoAVL * yo = this->raiz; //guardo mi posicion en un AUX
    //Guardo los hijos izquierdo y derecho del hijo derecho de mi hijo izquierdo
    TNodoAVL * hijoIzq_hijoDer_hijoIzq = this->raiz->iz.raiz->de.raiz->iz.raiz;
    TNodoAVL * hijoIzq_hijoDer_hijoDer = this->raiz->iz.raiz->de.raiz->de.raiz;

    this->raiz = this->raiz->iz.raiz->de.raiz; //le doy mi posición al hijo derecho de mi hijo izquierdo

    this->raiz->iz.raiz = yo->iz.raiz; //mi hijo izquierdo ahora será el hijo izq de la nueva this-raiz
    this->raiz->de.raiz = yo; //yo estaré a la derecha del nuevo this

    //me llevo a los hijos y los convierto en mis hijos a mi nueva posicion (derecha del nuevo this)
    this->raiz->de.raiz->iz.raiz = hijoIzq_hijoDer_hijoDer;
    this->raiz->iz.raiz->de.raiz = hijoIzq_hijoDer_hijoIzq;

    //ACTUALIZO LOS FE
    this->raiz->fe = this->raiz->de.Altura() - this->raiz->iz.Altura(); //actualizo al this
    this->raiz->de.raiz->fe = this->raiz->de.raiz->de.Altura() - this->raiz->de.raiz->iz.Altura();  //actualizo al derecho
    this->raiz->iz.raiz->fe = this->raiz->iz.raiz->de.Altura() - this->raiz->iz.raiz->iz.Altura();

}

//Devuelve la altura del árbol (la altura de un árbol vacio es 0)
int TAVLPoro::Altura(){
    
    int altura = 0;

    if(this->raiz){

        altura++;

        int alturaIzq = 0;
        int alturaDer = 0;

        if(this->raiz->iz.raiz){
            alturaIzq = this->raiz->iz.Altura();
        }

        if(this->raiz->de.raiz){
            alturaDer = this->raiz->de.Altura();
        }

        if(alturaIzq > alturaDer){
            altura += alturaIzq;
        }else{
            altura += alturaDer;
        }
    }


    return altura;
}


//Borra un elemento TPoro del árbol AVL
bool TAVLPoro::Borrar(TPoro &item_a_Borrar){

    bool borrado = false;
    bool decrece = false;

    if(Buscar(item_a_Borrar)){//COMPRUEBO EXISTE
        borrado = borrarAux(item_a_Borrar, decrece);
    } 

    return borrado;
}

//AUXILIAR: Borra el elemento TPoro en el árbol
bool TAVLPoro::borrarAux(TPoro &item_a_Borrar, bool &decrece){

    bool borrado = false;
    bool decreceIz = false;
    bool decreceDe = false;

    TNodoAVL * yo;

    if(this->raiz){ //si el raiz apunta a algo,es decir, no sea NULL

        TPoro itemActual = this->raiz->item;

        if(itemActual == item_a_Borrar){ //encuentro el nodo a borrar

            if(esHoja(this->raiz)){ //no tiene hijos

                delete this->raiz;
                raiz=NULL;
                borrado = true;
                decrece = true;

            }else{ //si tiene hijos
                bool tieneHijoIzquierdo = this->raiz->iz.raiz;
                bool tieneHijoDerecho = this->raiz->de.raiz;
                bool tieneAmbosHijos = tieneHijoIzquierdo && tieneHijoDerecho;

                if(tieneAmbosHijos){
                /*  DOS FORMAS DE HACERLO para que siga ordenado: buscando el poro con el mínimo valor en el 
                    subarbol derecho o buscando el poro con el máximo valor en el subarbol izquierdo*/

                    //Obtengo el item más a la izquierda del subarbol derecho
                    TPoro poroMayorIzquierda = raiz->iz.ObtenerMayorIzquierda(); //hago copia
                    borrado = borrarAux(poroMayorIzquierda, decrece); //borro el menor dentro del arbol
                    this->raiz->item = poroMayorIzquierda;

                }else{ //solo tiene 1 hijo
                    
                    TNodoAVL * yo = this->raiz;

                    if(tieneHijoIzquierdo){this->raiz = raiz->iz.raiz;}
                    else{
                        if(tieneHijoDerecho){this->raiz = raiz->de.raiz;}
                    }

                    yo->iz.raiz = NULL;
                    yo->de.raiz = NULL;
                    delete yo;  

                    decrece=true;
                    borrado=true;
                }
            }

        }else{  //sigo buscando

            double volumenItemActual = itemActual.Volumen();
            double volumenItemBuscado = item_a_Borrar.Volumen();

            //voy a la izquierda o la derecha según el volumen
            borrado = volumenItemBuscado < volumenItemActual ?
                this->raiz->iz.borrarAux(item_a_Borrar,decreceIz) : this->raiz->de.borrarAux(item_a_Borrar,decreceDe);
        }
    } 

    //DESPUÉS DE BORRAR FALTA COMPROBAR ROTACIÓN
    if(borrado){

        if(decreceIz){

            this->raiz->fe++; //si ha decrecido mi subarbol izquierdo aumento mi FE

            if(this->raiz->fe == 2){ // [HAY DESEQUILIBRIO , TOCA ROTACIÓN]

                switch (this->raiz->de.raiz->fe)
                {
                    case -1:
                        rotacion_DI();
                        decrece=true;
                        break;
                
                    case 0:
                        rotacion_DD();
                        decrece=false;
                        break;

                    case 1:
                        rotacion_DD();
                        decrece=true;

                        break;
                }

            }else{

                if(this->raiz->fe == 0){ decrece = true;}
                else if(this->raiz->fe == 1){ decrece = false;}
            }

        }else{

            if(decreceDe){

                this->raiz->fe--; //si ha decrecido mi subarbol izquierdo aumento mi FE

                if(this->raiz->fe == -2){ // [HAY DESEQUILIBRIO , TOCA ROTACIÓN]

                    switch (this->raiz->iz.raiz->fe)
                    {
                        case -1:
                            rotacion_II();
                            decrece=true;
                            break;
                    
                        case 0:
                            rotacion_II();
                            decrece=false;
                            break;

                        case 1:
                            rotacion_ID();
                            decrece=true;
                            break;
                    }

                }else{

                    if(this->raiz->fe == 0){ decrece = true;}
                    else if(this->raiz->fe == -1){ decrece = false;}
                }
            }
        }
    }

    return borrado;
}


TPoro TAVLPoro::ObtenerMayorIzquierda(){

    TPoro poro;

    if(raiz){
        if(raiz->de.raiz != NULL){// aun quedan hijos derechos
            poro = raiz->de.ObtenerMayorIzquierda();
        }else{
            
            poro = raiz->item; // ya no hay mas hijos izquierdos
        }
    }

    return poro;
}




ostream & operator<<(ostream &os,const TAVLPoro &avlporo){

    os<< avlporo.Inorden();
    return os;
}