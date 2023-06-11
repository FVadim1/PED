#include "tcomplejo.h"

//Constructor por defecto : PARTE REAL e IMAGINARIA inicializadas a 0
TComplejo::TComplejo(){
	re=0;
	im=0;
}

//Constructor a partir de la PARTE REAL
TComplejo::TComplejo(double r){
	re=r;
	im=0;	
}

//Constructor a partir de la PARTE REAL e IMAGINARIA
TComplejo::TComplejo(double r,double i){
	re=r;
	im=i;
}

//Constructor copia
TComplejo::TComplejo(const TComplejo &c){
	re=c.re;
	im=c.im;
}

//Destructor
TComplejo::~TComplejo(){
	re=0;
	im=0;
}

TComplejo TComplejo::operator+(TComplejo &c) const{
	
	TComplejo resultadoSuma;
	
	resultadoSuma.re = re+c.re;
	resultadoSuma.im = im+c.im;
	
	return resultadoSuma;
}

TComplejo TComplejo::operator-(TComplejo &c) const{

	TComplejo resultadoResta;
	
	resultadoResta.re = re-c.re;
	resultadoResta.im = im-c.im;
	
	return resultadoResta;
}

TComplejo TComplejo::operator*(TComplejo &c) const{

	TComplejo resultadoMult;

	resultadoMult.re = (re*c.re)-(im*c.im);
	resultadoMult.im = (re*c.im)+(im*c.re);

	return resultadoMult;	
}

TComplejo TComplejo::operator+(double suma) const{
	
	TComplejo resultadoSuma;
	
	resultadoSuma.re = re+suma;
	resultadoSuma.im = im;
	
	return resultadoSuma;	
}

TComplejo TComplejo::operator-(double resta) const{
	
	TComplejo resultadoResta;
	
	resultadoResta.re = re-resta;
	resultadoResta.im = im;
	
	return resultadoResta;
}

TComplejo TComplejo::operator*(double multiplicacion) const{
	
	TComplejo resultadoMult;

	resultadoMult.re = re*multiplicacion;
	resultadoMult.im = im*multiplicacion;

	return resultadoMult;
}

TComplejo operator+(double a,const TComplejo &c){
	
	TComplejo resultadoSuma;
	
	resultadoSuma.re = a+c.re;
	resultadoSuma.im = c.im;
	
	return resultadoSuma;
}

TComplejo operator-(double a,const TComplejo &c){

	TComplejo resultadoResta;

	resultadoResta.re = a-c.re;
	resultadoResta.im =-c.im;

	return resultadoResta;
}

TComplejo operator*(double a,const TComplejo &c){

	TComplejo resultadoMult;

	resultadoMult.re = a*c.re;
	resultadoMult.im = a*c.im;

	return resultadoMult;
}

TComplejo& TComplejo::operator=(const TComplejo &c){
	
	re=c.re;
	im=c.im;
	return *this;
}

//Devuelve true si ambos son iguales que le pasamos como parametro
bool TComplejo::operator==(const TComplejo &c) const{

    bool ambosIgual=false;

	if(re==c.re){
		if(im==c.im){ ambosIgual=true;}
	}

	return ambosIgual;
}

//Devuelve true si alguna es diferente del que le pasamos como parametro
bool TComplejo::operator!=(const TComplejo &c) const{
	
    bool algunaDiferente=false;

	if( (re!=c.re) || (im!=c.im) ){ algunaDiferente=true;}

	return algunaDiferente;
}

// Devuelve PARTE REAL
double TComplejo::Re() const{ return re;}

// Devuelve PARTE IMAGINARIA
double TComplejo::Im() const{ return im;}

// Modifica PARTE REAL
void TComplejo::Re(double r){ re=r;}

// Modifica PARTE IMAGINARIA
void TComplejo::Im(double i){ im=i;}

// Calcula el Argumento (en Radianes)
double TComplejo::Arg(void) const{
	
	double argumento;
	
	if(re==0 && im==0){ argumento=0;}
	else{ argumento=atan2(im, re);}
	
	return argumento;
}
// Calcula el Módulo
double TComplejo::Mod(void) const{ 

	double modulo = sqrt( pow(re,2.0) + pow(im,2.0) );
	return modulo; 

}

//Sobrecarga operador salida	
ostream &operator<<(ostream &os,const TComplejo &c){
    os<<"("<<c.re<<" "<<c.im<<")";
    return os;
}




