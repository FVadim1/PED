#ifndef _TComplejo
#define _TComplejo
#include <iostream>
#include <cmath>
using namespace std;

class TComplejo{
	private: 
		double re,im;
	public:
		//CONSTRUCTORES
		TComplejo();//Constructor por defecto : PARTE REAL e IMAGINARIA inicializadas a 0
		TComplejo(double);//Constructor a partir de la PARTE REAL
		TComplejo(double,double);//Constructor a partir de la PARTE REAL e IMAGINARIA
		TComplejo(const TComplejo&);//Constructor copia
		
		//DESTRUCTOR
		~TComplejo();
		
		//SOBRECARGAS ARITMETICAS
		TComplejo operator+(TComplejo&) const;
		TComplejo operator-(TComplejo&) const;
		TComplejo operator*(TComplejo&) const;
		TComplejo operator+(double) const;
		TComplejo operator-(double) const;
		TComplejo operator*(double) const;
		friend TComplejo operator+(double ,const TComplejo&);
		friend TComplejo operator-(double ,const TComplejo&);
		friend TComplejo operator*(double ,const TComplejo&);
		
		//SOBRECARGA ASIGNACION
		TComplejo& operator=(const TComplejo&);//Sobrecarga del operador asignación
		bool operator==(const TComplejo&) const; // IGUALDAD de números complejos
		bool operator!=(const TComplejo&) const; // DESIGUALDAD de números complejos
		
		//OTROS METODOS
		double Re() const;// Devuelve PARTE REAL
		double Im() const; // Devuelve PARTE IMAGINARIA
		void Re(double); // Modifica PARTE REAL
		void Im(double); // Modifica PARTE IMAGINARIA
		double Arg(void) const; // Calcula el Argumento (en Radianes)
		double Mod(void) const; // Calcula el Módulo
		
		//SOBRECARGA OPERADOR SALIDA
		friend ostream & operator<<(ostream &,const TComplejo &);		
};

#endif
