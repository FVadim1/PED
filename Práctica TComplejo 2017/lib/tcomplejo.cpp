#include "tcomplejo.h"

//constructor por defecto
TComplejo::TComplejo()
{
	re=im=0;
}

//constructor a partir de la parte real
TComplejo::TComplejo(double real)
{
re=real;
im=0;
}

//constructor a partir de las dos partes
TComplejo::TComplejo(double real,double imaginaria)
{
re=real;
im=imaginaria;
}

//constructor de copia
TComplejo::TComplejo(const TComplejo &c)
{
re=c.re;
im=c.im;
}

//destructor
TComplejo::~TComplejo()
{
re=0;
im=0;
}

//operador suma dos complejos
TComplejo TComplejo::operator+(TComplejo &c) const
{

TComplejo suma;

suma.re=re+c.re;
suma.im=im+c.im;

return suma;

}


//operador resta de dos complejos
TComplejo TComplejo::operator-(TComplejo &c) const 
{
TComplejo resta;

resta.re=re-c.re;
resta.im=im-c.im;

return resta;

}

//operador producto de dos complejos
TComplejo TComplejo::operator*(TComplejo &c) const
{
TComplejo pro;
pro.re=(re*c.re)-(im*c.im);
pro.im=(re*c.im)+(im*c.re);

return pro;
}

//operador suma de un complejo y un double
TComplejo TComplejo::operator+(double sum) const  
{
TComplejo suma;

suma.re=re+sum;
suma.im=im;

return suma;
}

//operador resta de un complejo y un double
TComplejo TComplejo::operator-(double res) const
{
TComplejo resta;
resta.re=re-res;
resta.im=im;

return resta;
}

//operador producto de un complejo y un double
TComplejo TComplejo::operator*(double pro) const
{
TComplejo prod;

prod.re=re*pro;
prod.im=im*pro;


return prod;
}

//suma por la derecha
TComplejo operator+(double d,const TComplejo &c)
{

TComplejo suma;

suma.re=d+c.re;
suma.im=c.im;


return suma;
}


//resta por la dcha
TComplejo operator-(double d,const TComplejo &c)
{

TComplejo resta;

resta.re=d-c.re;
resta.im=-c.im;

return resta;
}

//producto por la dcha
TComplejo operator*(double d,const TComplejo &c)
{

TComplejo pro;

pro.re=d*c.re;
pro.im=c.im*d;

return pro;
}

//operador asignacion
TComplejo& TComplejo::operator=(const TComplejo &c)
{
re=c.re;
im=c.im;

return *this;

}

//operador comparacion
bool TComplejo::operator==(const TComplejo &c) const
{
	bool iguales=false;

	if(re==c.re)
		if(im==c.im)
			iguales=true;

	return iguales;
}

//oeprador desigualdad

bool TComplejo::operator!=(const TComplejo &c) const
{
bool desiguales=false;

	if((re!=c.re)||(im!=c.im))
		desiguales=true;

return desiguales;
}

//devuelve la parte real
double TComplejo::Re() const
{
return re;
}

//modifica la parte real
void TComplejo::Re(double real)
{
re=real;
}


//devuelve la parte imagimaria
double TComplejo::Im() const
{
return im;
}

//modifica la parte imaginaria
void TComplejo::Im(double imag)
{
im=imag;
}

// calcula el modulo
double TComplejo::Mod(void) const
{
return sqrt(pow(re,2.0)+pow(im,2.0));
}

//calcula el argumento en radianes
double TComplejo::Arg(void) const
{
double arc;
if(re==0 && im==0)
	arc=0;
else
	arc = atan2(im, re);

return arc;
}

bool TComplejo::operator>(const TComplejo &de) const{
	return Mod() > de.Mod() || 
	Mod() == de.Mod() && Re() > de.Re() || 
	Mod() == de.Mod() && Re() == de.Re() && Im() > de.Im();
}

bool TComplejo::operator<(const TComplejo &de) const{
	return *this != de && !(*this > de);
}


ostream &operator<<(ostream &o,const TComplejo &c){
	o<<"("<<c.re<<" "<<c.im<<")";
	return o;
}

