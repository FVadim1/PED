#include <iostream>
using namespace std;

#include "../include/tvectorcalendario.h"

TVectorCalendario::TVectorCalendario(){
    this->tamano = 0;
    this->c = NULL;
}

TVectorCalendario::TVectorCalendario(int tam){
    if(tam <= 0){
        this->tamano = 0;
        this->c = NULL;
    }
    else{
        this->tamano = tam;
        this->c = new TCalendario [tamano];
        if(c == NULL){
            this->tamano = 0;
            return;
        }
    }
}

TVectorCalendario::TVectorCalendario(const TVectorCalendario & obj){
    this->tamano = obj.tamano;
    this->c = new TCalendario [tamano];

    if(c == NULL){
        this->tamano = 0;
        return;
    }
    for(int i = 1; i <= this->tamano; i++){
        c[i] = obj[i];
    }
    
}

TVectorCalendario::~TVectorCalendario(){
    this->tamano = 0;
    if(this->c != NULL){
        delete [] c;
        this->c = NULL;
    }
}

bool TVectorCalendario::bisiesto(int anyo){
    if(anyo % 4 == 0 && (anyo % 100 != 0 || anyo % 400 == 0))
        return true;
    return false; 
}

bool TVectorCalendario::comprobarFecha(int dia, int mes, int anyo){
    //Limites (dias negativos, +12 meses, +31 dias, <1900, mes-dias)
    if(dia > 0 && dia <= 31 && mes > 0 && mes <= 12 && anyo >= 1900){

        //Febrero bisiesto (max 29), sino (max 28)
        if(bisiesto(anyo) && mes==2 && dia > 29)
            return false; 
        
        else if(!bisiesto(anyo) && mes == 2 && dia > 28)
                return false;
        
        //Abril. junio, septiembre y noviembre (=30)
        if(mes == 4 || mes == 6 || mes == 9 || mes == 11){
            if(dia > 30)
                return false;
        }
        return true;
    }
    return false;
}

TVectorCalendario& TVectorCalendario::operator=(const TVectorCalendario &obj){
if (this ==&obj)
    {
        return *this;
        
    }else{
        (*this).~TVectorCalendario();
        this->tamano =obj.tamano;
        this->c=new TCalendario[tamano];
        for (int i = 0; i < tamano; i++){
            this->c[i]=obj[i+1];
        }
        return *this;
    }
}

bool TVectorCalendario::operator==(const TVectorCalendario &obj) const{
    if(this->tamano != obj.tamano)
        return false;
    else{
        for(int i = 0; i < this->tamano; i++){
            if(this->c[i] != obj.c[i])
                return false;
        }
    }
    return true;
}

bool TVectorCalendario::operator!=(const TVectorCalendario &obj) const{
    return !(*this == obj);
}

TCalendario& TVectorCalendario::operator[](int numero){
    if(numero >= 1 && numero <= this->tamano)
        return this->c[numero-1];
    return error;
}

TCalendario TVectorCalendario::operator[](int numero) const{
    if(numero >= 1 && numero <= this->tamano)
        return this->c[numero-1];
    return error;
}

int TVectorCalendario::Ocupadas(){
    int ocupadas = 0;
    for(int i = 0; i < this->tamano; i++)
        if(this->c[i] != this->error)
            ocupadas++;
    return ocupadas;
}

bool TVectorCalendario::ExisteCal(TCalendario &obj){

    for(int i = 0; i < this->tamano; i++){       
        if(obj == this->c[i]){
            return true;
        } 
    } 
    return false;
}

void TVectorCalendario::MostrarMensajes(int dia, int mes, int anyo){
    stringstream out;
    out << "[";
    
    if(comprobarFecha(dia,mes,anyo)){

        for(int i = 0; i<this->tamano; i++){

            if(c[i].Anyo() < anyo){
                continue;
            }
               
            else if(c[i].Anyo() == anyo && c[i].Mes() < mes){
                continue;
            }
               
            else if(c[i].Anyo() == anyo && c[i].Mes() == mes && c[i].Dia() < dia){
                continue;
            }
                
            else{
                out << c[i];
                if(i != this->tamano - 1)
                    out << ", ";
            }
        }
    }
    out << "]";
    cout << out.str();
}

bool TVectorCalendario::Redimensionar(int tam){
    if(tam <= 0)
        return false;
    if(tam == this->tamano)
        return false;

    TCalendario *aux = new TCalendario[tam];
    TCalendario *vacio = new TCalendario();

    //El vector resultante sera mayor
    if(tam > this->tamano){
        for(int i = 0; i < tam; i++){
            if(i < this->tamano)
                aux[i] = this->c[i];
            else aux[i] = (*vacio);
        } 

        (*this).~TVectorCalendario();   
        this->c = aux;
        this->tamano = tam;

        return true;  
    }
    else{
        for(int i = 0; i < tam; i++)
            aux[i] = this->c[i];

        (*this).~TVectorCalendario();   
        this->c = aux;
        this->tamano = tam;

        return true;  
    }
}

ostream& operator<<(ostream &s, const TVectorCalendario &obj){
    s << "[";
    for(int i = 1; i <= obj.tamano; i++){
        s << "(" << i <<") " << obj[i];
        if(i!= obj.tamano)
            s << ", "; 
    }
    s<< "]";

    return s;
}