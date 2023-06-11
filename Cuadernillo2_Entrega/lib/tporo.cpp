#include "tporo.h"

//Forma mia

void TPoro::copiar(const TPoro &t){
        this->x=t.x;
        this->y=t.y;
        this->volumen = t.volumen;
        this->color = NULL;

        if(t.color != NULL){
            color = new char[strlen(t.color) + 1];
            strcpy(color,t.color);
        }
}


//Forma canónica

TPoro::TPoro(){
    x=0;
    y=0;
    volumen = 0;
    color = NULL;
}

TPoro::TPoro(int x, int y, double vol){
    this->x=x;
    this->y=y;
    this->volumen = vol;
    this->color = NULL;
}

TPoro::TPoro(int x, int y, double vol, char * c){
    this->x=x;
    this->y=y;
    this->volumen = vol;
    if(c != NULL){
        //Lo convierto en minúsculas
        char* temp = strdup(c);
        int i=0;
        while(temp[i] != '\0'){
            temp[i] = tolower(temp[i]);
            i++;
        }
        temp[i] = '\0';

        color = strdup(temp);
    }else{
        this->color = NULL;
    }
}

TPoro::TPoro(const TPoro &t){ copiar(t);}


TPoro::~TPoro(){
    x=0;
    y=0;
    volumen=0;
    if(color != NULL){delete [] color; color=NULL;}
}


//Métodos
int TPoro::PosicionX(){ return x; } //Devuelva la coordenada x de la posicion
int TPoro::PosicionY(){ return y; } //Devuelva la coordenada y de la posicion
double TPoro::Volumen(){ return volumen; } //Devuelve el volumen
char* TPoro::Color(){ return color; } //Devuelve el color

//Devuelve cierto si el poro está vacio
bool TPoro::EsVacio() const { return (x == 0 && y == 0 && volumen == 0 && color == NULL);}

void TPoro::Color(char * c){
    if(this->color != NULL){
        delete [] this->color; //destructor
        color = NULL; //para que no dé error si hacemos delete más de una vez
    }
    if(c != NULL){
        //Lo convierto en minúsculas
        char* temp = strdup(c);
        int i=0;
        while(temp[i] != '\0'){
            temp[i] = tolower(temp[i]);
            i++;
        }
        temp[i] = '\0';

        color = strdup(temp);
    }
}

void TPoro::Volumen(double v){ volumen = v;}
void TPoro::Posicion(int x_ , int y_){ x = x_;y = y_;}

bool TPoro::operator!=(const TPoro &t) const{ return !(*this==t);}

bool TPoro::operator==(const TPoro &t) const{ 

    //si la posicion y el volumen son iguales
    if(x==t.x && y==t.y && volumen==t.volumen){

        //si de alguno de los dos el color es NULL, devuelve false
        if((color == NULL && t.color != NULL) || (color != NULL && t.color == NULL)){
            return false;
        }

        //si ninguno es null
        if((color != NULL  && t.color != NULL)){
            //si tiene el mismo mensaje dentro
            if(strcmp(color, t.color) == 0){
                return true;
            }
        }

        //si ambos son null
        if(color == NULL  && t.color == NULL){
            return true;
        }
    }
    
    return false;
}

TPoro & TPoro::operator=(const TPoro &t){
    
    if(this != &t){
        (*this).~TPoro();
        copiar(t);
    }

    return *this;
} 


ostream & operator<<(ostream &os ,const TPoro &poro){

    if(!poro.EsVacio()){
        os.setf(ios::fixed);
        os.precision(2);
        os<<"("<<poro.x<<", "<<poro.y<<") "<<poro.volumen<<" ";
        if(poro.color != NULL){
            os<<poro.color;
        }else{
            os<<"-";
        }
    }else{
        os << "()";   
    }

    return os;
}

