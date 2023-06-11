#include <tvectorporo.h>

void TVectorPoro::copiar(const TVectorPoro &t){

    dimension=t.dimension;
    error=t.error;
    datos = NULL;

    if(t.dimension > 0){
        datos = new TPoro[t.dimension];
        for(int i = 0; i< t.dimension; i++){
            datos[i] = t.datos[i];
        }
    }

} 

//Forma canónica
TVectorPoro::TVectorPoro(){
    dimension=0;
    datos=NULL;
}

TVectorPoro::TVectorPoro(int n){
    if(n<=0){ n=0; datos=NULL;}
    else{ dimension=n; datos = new TPoro[dimension];}
}

TVectorPoro::TVectorPoro(TVectorPoro &t){ copiar(t);}


TVectorPoro::~TVectorPoro(){
    dimension=0;
    if(datos != NULL){delete[] datos; datos=NULL;}
}
    

TVectorPoro & TVectorPoro::operator=(const TVectorPoro &t){

    if(this != &t){
        (*this).~TVectorPoro();
        copiar(t);
    }

    return *this;
}

//Métodos
bool TVectorPoro::operator==(TVectorPoro &t){

    if(dimension == t.dimension){

        for(int i= 0 ; i < dimension ; i++){
            if(this->datos[i] != t.datos[i]){ return false; }
        }
        
    }else{return false;}

    return true;
}


bool TVectorPoro::operator!=(TVectorPoro &t ){ return !(*this==t);}


TPoro & TVectorPoro::operator[](int posicion){ // a[posicion] = a

    if(posicion >= 1 && posicion <= dimension){ return datos[posicion-1];}
    return error;
}


TPoro TVectorPoro::operator[](int posicion) const { // a = a[posicion]

    if(posicion >= 1 && posicion <= dimension){ return datos[posicion-1];}
    return error;
} 


int TVectorPoro::Longitud(){ return dimension;}
int TVectorPoro::Cantidad(){ 
    int count = 0;

    for(int i=0 ; i < dimension ; i++){
        if(!datos[i].EsVacio()){ count++;}
    }

    return count;
}

/* SI la nueva dimension es menor o igual que 0 devuelve false
 Si la nueva dimension es la misma que la actual devuelve false
 Si la nueva dimension es mayor que la actual se aumenta el tamaño con poros vacios
 SI la nueva dimension es menor que la actual se borran poros empezando por el final */
bool TVectorPoro::Redimensionar(int nuevaDimension){ 
    
    //devuelve true si se ha redimensionado correctamente

    if(nuevaDimension > 0 && nuevaDimension != dimension){

        TPoro *nuevosDatos = new TPoro[nuevaDimension];

        if(nuevaDimension < dimension){
            for(int i = 0; i < nuevaDimension; i++){ 
                nuevosDatos[i] = datos[i]; 
            } //si aun no se ha llegado a superar la dimension antigua 
        }
        else{
            
            for(int i = 0; i < nuevaDimension; i++){

                if(i >= dimension){ 
                    nuevosDatos[i] = TPoro(); // si se llega a superar la dimension antigua
                }else{ 
                    nuevosDatos[i] = datos[i]; //si aun no se ha llegado a superar la dimension antigua
                } 
            }

        }

        if(datos != NULL){ delete[] datos; datos=NULL;}

        datos=nuevosDatos;
        dimension=nuevaDimension;

        return true;
    }


    return false;
    
}


ostream & operator<<(ostream &os, const TVectorPoro &t){

    os<< "[";
    for(int i = 0; i < t.dimension ; i++){
        os << i+1 << " " << t.datos[i];
        if( i < t.dimension - 1){
            os << " ";
        }

    }
    os<< "]";

    return os;
}
