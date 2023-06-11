#ifndef $TComplejo$
#define $TComplejo$
#include <iostream>
#include <cmath>
using namespace std;

class TComplejo
{
private:
	double re,im;
public:
	//constructores
	TComplejo();
	TComplejo(double);
	TComplejo(double,double);
	TComplejo(const TComplejo &);
	//destructor
	~TComplejo();
	//sobrecarga de los operadores aritmaticos
	TComplejo operator+(TComplejo &) const;
	TComplejo operator-(TComplejo &) const;
	TComplejo operator*(TComplejo &) const;
	TComplejo operator+(double)const;
	TComplejo operator-(double)const;
	TComplejo operator*(double)const;
	friend TComplejo operator+(double,const TComplejo &);
	friend TComplejo operator-(double,const TComplejo &);
	friend TComplejo operator*(double,const TComplejo &);
	//asignacon de numeros complejos
	TComplejo& operator=(const TComplejo &);
	bool operator==(const TComplejo &) const;
	bool operator!=(const TComplejo &) const;

	// añadidos.
	bool operator<(const TComplejo &de) const;
	bool operator>(const TComplejo &de) const;
	
	double Re() const;
	void Re(double);
	double Im() const;
	void Im(double);
	double Mod(void) const;
	double Arg(void) const;
	
	//operador salida
	friend ostream& operator<<(ostream &,const TComplejo &);
};


#endif
