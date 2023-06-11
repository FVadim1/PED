#include <iostream>
using namespace std;

#include "../include/tcalendario.h"

TCalendario::TCalendario(){
    this->dia = 1;
    this->mes = 1;
    this->anyo = 1900;
    mensaje = NULL;
}

TCalendario::TCalendario(int dia, int mes, int anyo, char * m){
    if(comprobarFecha(dia, mes, anyo)){
        this->dia = dia;
        this->mes = mes;
        this->anyo = anyo;

        if(m != NULL){
            this->mensaje = new char[strlen(m)+1];
            strcpy(this->mensaje, m);
        }
        else this->mensaje = NULL;
    }
    else{
        this->dia = 1;
        this->mes = 1;
        this->anyo = 1900;
        this->mensaje = NULL;
    }
}

TCalendario::TCalendario(const TCalendario &obj){
    if(comprobarFecha(obj.dia, obj.mes, obj.anyo)){
        this->dia = obj.dia;
        this->mes = obj.mes;
        this->anyo = obj.anyo;

        if(obj.mensaje != NULL){
            this->mensaje = new char[strlen(obj.mensaje)+1];
            strcpy(this->mensaje, obj.mensaje);
        }
        else this->mensaje = NULL;
    }
    else{
        this->dia = 1;
        this->mes = 1;
        this->anyo = 1900;
        this->mensaje = NULL;
    }
}

TCalendario::~TCalendario(){
    this->dia = 1;
    this->mes = 1;
    this->anyo = 1900;

    if(this->mensaje != NULL){
        delete [] this->mensaje;
    }
        
    this->mensaje = NULL;
}

bool TCalendario::bisiesto(int anyo){
    if(anyo % 4 == 0 && (anyo % 100 != 0 || anyo % 400 == 0))
        return true;
    return false; 
}

bool TCalendario::comprobarFecha(int dia, int mes, int anyo){
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

bool TCalendario::ModFecha(int dia, int mes, int anyo){
    if(comprobarFecha(dia,mes,anyo)){
        this->dia = dia;
        this->mes = mes;
        this->anyo = anyo;

        return true;
    }
    return false;
}

bool TCalendario::ModMensaje(char * mensaje){
    bool modificado = false;

    if(mensaje == NULL){
        this->mensaje = NULL;
        modificado = true;
    }
    else{
        delete [] this->mensaje;
        this->mensaje = new char[strlen(mensaje)];
        strcpy(this->mensaje, mensaje);

        modificado = true;
    }
    return modificado;
}

TCalendario& TCalendario::operator=(const TCalendario &obj){
    if(this != &obj){   //Protección contra autoasignacion
        (*this).~TCalendario();
        this->dia = obj.dia;
        this->mes = obj.mes;
        this->anyo = obj.anyo;

        if(this->mensaje != NULL)
            delete this->mensaje;
        if(obj.mensaje == NULL)
            this->mensaje = NULL;
        else{
            this->mensaje = new char[strlen(obj.mensaje) + 1];
            strcpy(this->mensaje, obj.mensaje);
        } 
    }
    return *this;
}

TCalendario TCalendario::operator+(int cantDias){
    TCalendario tcalendario(*this);

    for(int i = 0; i < cantDias; i++){
        tcalendario++; 
    }

    return tcalendario;   
}

TCalendario TCalendario::operator-(int cantDias){
    TCalendario tcalendario(*this);
    
    for(int i = 0; i < cantDias; i++){   //Se podría optimizar poniendo 1/1/1900 como cond.parada
        tcalendario--;
    }

    if(!comprobarFecha(tcalendario.dia, tcalendario.mes, tcalendario.anyo)){
        tcalendario.~TCalendario();
    }

    return tcalendario;   
}

//Preincremento
TCalendario & TCalendario::operator++(){
    if(mes == 2){
        if(dia ==29 && bisiesto(anyo)){
                dia = 1;
                mes ++;             
        }else if(dia==28 && !bisiesto(anyo)){
                dia = 1;
                mes++;
        }
        else{
            dia++;
        }        
    }
    else if(mes == 12 ){
        if (dia == 31){
            dia = 1;
            anyo++;
            mes = 1;
            
        }else{
            dia++;
        }
    }
    else if(mes ==4|| mes ==6 || mes==9 || mes==11){
        if(dia==30){
            mes ++;
            dia=1;
        }
        else{
            dia ++;
        }
    }
    else if(mes ==1|| mes ==3 || mes==5 || mes==7 ||mes ==8 ||mes ==10 ){
        if(dia==31){
            dia=1;
            mes ++;
            
        }
        else{
            dia ++;
        }
    }
    return *this;
}

//Postincremento
TCalendario TCalendario::operator++(int cantDias){
    TCalendario tcalendario(*this);
    if(mes == 2){
        if(dia ==29 && bisiesto(anyo)){
                dia = 1;
                mes ++;             
        }else if(dia==28 && !bisiesto(anyo)){
                dia = 1;
                mes++;
        }
        else{
            dia++;
        }        
    }
    else if(mes == 12 ){
        if (dia == 31){
            dia = 1;
            anyo++;
            mes = 1;
            
        }else{
            dia++;
        }
    }
    else if(mes ==4|| mes ==6 || mes==9 || mes==11){
        if(dia==30){
            mes ++;
            dia=1;
        }
        else{
            dia ++;
        }
    }
    else if(mes ==1|| mes ==3 || mes==5 || mes==7 ||mes ==8 ||mes ==10 ){
        if(dia==31){
            dia=1;
            mes ++;
            
        }
        else{
            dia ++;
        }
    }
    return tcalendario;
}

//Preincremento
TCalendario & TCalendario::operator--(){
    dia--;
    if(dia == 0){
        mes--;
        if(mes == 0){
            mes = 12;
            anyo--;
        }
        if(mes == 2 && !bisiesto(this->anyo))
            dia = 28;
        else if(mes == 2 && bisiesto(this->anyo))
            dia = 29;
        else if(mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 ||
                mes == 10 || mes == 12)
            dia = 31;
        else dia = 30;
    }

    if(!comprobarFecha(this->dia, this->mes, this->anyo)){
        this->~TCalendario();
    }

    return *this;
}

//Postincremento
TCalendario TCalendario::operator--(int cantDias){
    TCalendario tcalendario(*this);
    dia--;
    if(dia == 0){
        mes--;
        if(mes == 0){
            mes = 12;
            anyo--;
        }
        if(mes == 2 && !bisiesto(this->anyo))
            dia = 28;
        else if(mes == 2 && bisiesto(this->anyo))
            dia = 29;
        else if(mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 ||
                mes == 10 || mes == 12)
            dia = 31;
        else dia = 30;
    }

    if(!comprobarFecha(this->dia, this->mes, this->anyo)){
        this->~TCalendario();
    }

    return tcalendario;
}

bool TCalendario::operator== (const TCalendario &obj){
    bool same = false;
    
    if(dia==obj.dia && mes==obj.mes && anyo==obj.anyo){
        if(this->mensaje == NULL && obj.mensaje == NULL){    
                same = true;
        }
        else if(this->mensaje == NULL || obj.mensaje == NULL)
                same = false;
        else if (strcmp(mensaje, obj.mensaje) == 0){
            same = true;
        }
    }
    return same;
}

bool TCalendario::operator!= (const TCalendario &obj){
    return !(*this==obj);
}

bool TCalendario::operator> (const TCalendario &obj){
    if(this->anyo > obj.anyo)
        return true;
    else if(this->anyo == obj.anyo && this->mes > obj.mes )
        return true;
    else if(this->anyo == obj.anyo && this->mes == obj.mes && this->dia > obj.dia)
        return true;
    else if((this->anyo == obj.anyo && this->mes == obj.mes && this->dia == obj.dia)
            && this->mensaje != obj.mensaje){
        if(this->mensaje == NULL)
            return false;
        else if(obj.mensaje == NULL)
            return true;
        else{
            if(strcmp(this->mensaje, obj.mensaje) == 0)
                return false;
            else if(strcmp(this->mensaje, obj.mensaje) > 0)
                return true;
            else return false;
        }
    }
    return false;
}

bool TCalendario::operator< (const TCalendario &obj){
    if((*this)==obj)
        return false;
    else return !(*this>obj);
}

bool TCalendario::EsVacio(){
    if(dia == 1  && mes == 1 && anyo == 1900 && mensaje == NULL)
        return true;
    return false;
}

ostream& operator<<(ostream &s, const TCalendario &obj){

    if(obj.dia < 10)
        s << "0" << obj.dia;
    else s << obj.dia;

    s << "/";

    if(obj.mes < 10)
        s << "0" << obj.mes;
    else s << obj.mes;

    s << "/";
    s << obj.anyo << " ";
    s << "\"";
    
    if(obj.mensaje != NULL)
        s << obj.mensaje;
    
    s << "\"";
    
    return s;
}